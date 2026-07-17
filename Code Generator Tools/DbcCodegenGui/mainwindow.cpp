// mainwindow.cpp
#include "mainwindow.h"
#include "dbcparser.h"
#include "codegen.h"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSplitter>
#include <QTableWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QEvent>
#include <QScreen>
#include <QGuiApplication>

using namespace dbc;

namespace {
// Tree columns
enum {
    COL_NAME = 0, COL_ID, COL_NODE, COL_TYPE, COL_BUS,
    COL_FWD, COL_FWDBUS, COL_FREQ, COL_MUX, TREE_COLS
};
// Signal table columns
enum {
    S_EN = 0, S_NAME, S_START, S_LEN, S_DBCTYPE, S_FACTOR, S_OFFSET, S_DPS,
    S_RTYPE, S_COLS
};

int busToIndex(Bus b) { return static_cast<int>(b); }
Bus indexToBus(int i) { return static_cast<Bus>(i); }

// Swallows wheel events on a widget unless it currently has focus, so scrolling
// the view does not accidentally change combo-box values on hover.
class WheelGuard : public QObject {
public:
    using QObject::QObject;
protected:
    bool eventFilter(QObject *o, QEvent *e) override {
        if (e->type() == QEvent::Wheel) {
            auto *w = qobject_cast<QWidget *>(o);
            if (w && !w->hasFocus()) return true; // eat it
        }
        return QObject::eventFilter(o, e);
    }
};
WheelGuard *wheelGuard() { static WheelGuard g; return &g; }

// Make a combo ignore hover-scroll: no wheel focus + wheel guard installed.
void guardCombo(QComboBox *c) {
    c->setFocusPolicy(Qt::StrongFocus);
    c->installEventFilter(wheelGuard());
}
} // namespace

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("DBC → C Code Generator");
    resize(1200, 760);

    auto *central = new QWidget(this);
    auto *root = new QVBoxLayout(central);

    // --- top bar ---
    auto *bar = new QHBoxLayout();
    auto *loadBtn = new QPushButton("Load DBC…", central);
    auto *exportBtn = new QPushButton("Export .c / .h / .txt…", central);
    auto *allRxBtn = new QPushButton("Set All Rx", central);
    auto *allTxBtn = new QPushButton("Set All Tx", central);
    auto *allBlankBtn = new QPushButton("Set All Blank", central);
    auto *enableAllBtn = new QPushButton("Enable All", central);
    auto *disableAllBtn = new QPushButton("Disable All", central);
    auto *allBusBtn = new QPushButton("Set All Bus…", central);
    m_fileLabel = new QLabel("No DBC loaded", central);
    m_fileLabel->setStyleSheet("color:#888;");
    bar->addWidget(loadBtn);
    bar->addWidget(exportBtn);
    bar->addSpacing(16);
    bar->addWidget(allRxBtn);
    bar->addWidget(allTxBtn);
    bar->addWidget(allBlankBtn);
    bar->addSpacing(16);
    bar->addWidget(enableAllBtn);
    bar->addWidget(disableAllBtn);
    bar->addSpacing(16);
    bar->addWidget(allBusBtn);
    bar->addSpacing(12);
    bar->addWidget(m_fileLabel, 1);
    root->addLayout(bar);

    // --- splitter: messages tree (top) + signal detail table (bottom) ---
    auto *split = new QSplitter(Qt::Vertical, central);

    m_tree = new QTreeWidget(split);
    m_tree->setColumnCount(TREE_COLS);
    m_tree->setHeaderLabels({"Message / Signal", "ID", "Node", "Type", "Bus",
                             "Forward", "Fwd Bus", "Tx Freq", "Mux Mode"});
    m_tree->setRootIsDecorated(true);
    m_tree->setAlternatingRowColors(true);
    m_tree->header()->setSectionResizeMode(COL_NAME, QHeaderView::Interactive);
    m_tree->setColumnWidth(COL_NAME, 260);
    split->addWidget(m_tree);

    auto *sigPanel = new QWidget(split);
    auto *sigLayout = new QVBoxLayout(sigPanel);
    sigLayout->setContentsMargins(0, 0, 0, 0);
    sigLayout->addWidget(new QLabel("Signals for selected message:", sigPanel));
    m_sigTable = new QTableWidget(sigPanel);
    m_sigTable->setColumnCount(S_COLS);
    m_sigTable->setHorizontalHeaderLabels({"On", "Signal", "Start", "Len",
                                           "DBC Type", "Factor", "Offset",
                                           "DPS", "Returned Type"});
    m_sigTable->horizontalHeader()->setStretchLastSection(true);
    m_sigTable->verticalHeader()->setVisible(false);
    sigLayout->addWidget(m_sigTable);
    split->addWidget(sigPanel);

    split->setStretchFactor(0, 3);
    split->setStretchFactor(1, 2);
    root->addWidget(split, 1);

    setCentralWidget(central);

    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::onLoadDbc);
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onExport);
    connect(allRxBtn, &QPushButton::clicked, this,
            [this] { setAllMessages(MsgType::Rx); });
    connect(allTxBtn, &QPushButton::clicked, this,
            [this] { setAllMessages(MsgType::Tx); });
    connect(allBlankBtn, &QPushButton::clicked, this,
            [this] { setAllMessages(MsgType::Blank); });
    connect(enableAllBtn, &QPushButton::clicked, this,
            [this] { setAllEnabled(true); });
    connect(disableAllBtn, &QPushButton::clicked, this,
            [this] { setAllEnabled(false); });
    connect(allBusBtn, &QPushButton::clicked, this, [this] {
        if (!m_hasDbc) return;
        const QStringList opts{"CAN 1", "CAN 2", "CAN 3"};
        bool ok = false;
        QString choice = QInputDialog::getItem(
            this, "Set All Bus", "Assign every message to bus:", opts, 0, false,
            &ok);
        if (ok && !choice.isEmpty())
            setAllBus(indexToBus(opts.indexOf(choice)));
    });
    connect(m_tree, &QTreeWidget::itemChanged, this, &MainWindow::onTreeItemChanged);
    // currentItemChanged fires for both mouse and keyboard navigation, so the
    // signal table always tracks the highlighted message.
    connect(m_tree, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem *cur, QTreeWidgetItem *) {
                if (!cur) return;
                QTreeWidgetItem *it = cur->parent() ? cur->parent() : cur;
                bool ok = false;
                int idx = it->data(COL_NAME, Qt::UserRole).toInt(&ok);
                if (ok) populateSignalTable(idx);
            });
    connect(m_sigTable, &QTableWidget::cellChanged, this, [this](int row, int col) {
        if (m_updating || m_sigTableMsg < 0) return;
        auto &msg = m_db.messages[m_sigTableMsg];
        if (row < 0 || row >= (int)msg.sigs.size()) return;
        auto &sig = msg.sigs[row];
        if (col == S_EN) {
            bool on = m_sigTable->item(row, S_EN)->checkState() == Qt::Checked;
            setSignalEnabled(m_sigTableMsg, row, on); // model+tree+parent
        } else if (col == S_DPS) {
            bool ok = false;
            int v = m_sigTable->item(row, S_DPS)->text().toInt(&ok);
            if (ok) sig.dps = qBound(0, v, 8);
        }
    });

    // Open centered on the primary screen.
    if (QScreen *scr = QGuiApplication::primaryScreen()) {
        const QRect avail = scr->availableGeometry();
        move(avail.center() - QPoint(width() / 2, height() / 2));
    }
}

int MainWindow::currentMessageIndex() const {
    auto *it = m_tree->currentItem();
    if (!it) return -1;
    if (it->parent()) it = it->parent(); // signal -> its message
    bool ok = false;
    int idx = it->data(COL_NAME, Qt::UserRole).toInt(&ok);
    return ok ? idx : -1;
}

void MainWindow::onLoadDbc() {
    QString path = QFileDialog::getOpenFileName(this, "Select DBC File", QString(),
                                                "DBC Files (*.dbc);;All Files (*)");
    if (path.isEmpty()) return;

    Database db;
    std::string err;
    if (!parseFile(path.toStdString(), db, err)) {
        QMessageBox::critical(this, "Parse error", QString::fromStdString(err));
        return;
    }
    m_db = std::move(db);
    m_dbcPath = path;
    m_hasDbc = true;
    m_fileLabel->setText(QFileInfo(path).fileName() +
                         QString("  (%1 messages)").arg(m_db.messages.size()));
    m_fileLabel->setStyleSheet("");
    buildTree();
    m_sigTable->setRowCount(0);
    m_sigTableMsg = -1;
}

static QComboBox *makeBusCombo(QWidget *parent) {
    auto *c = new QComboBox(parent);
    c->addItems({"CAN 1", "CAN 2", "CAN 3"});
    return c;
}

void MainWindow::buildTree() {
    m_updating = true;
    m_tree->clear();
    m_rows.clear();

    for (int i = 0; i < (int)m_db.messages.size(); ++i) {
        auto &m = m_db.messages[i];
        auto *item = new QTreeWidgetItem(m_tree);
        item->setData(COL_NAME, Qt::UserRole, i);
        item->setText(COL_NAME, QString::fromStdString(m.name));
        item->setText(COL_ID, QString("0x%1").arg(m.id, 0, 16).toUpper());
        item->setText(COL_NODE,
                      m.senders.empty()
                          ? QString()
                          : QString::fromStdString(m.senders.front()));
        // No AutoTristate: we manage the parent's check state manually so that
        // toggling one child signal doesn't cascade back over the others.
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(COL_NAME, Qt::Unchecked);
        m.checked = false;

        RowWidgets rw;
        rw.item = item;
        rw.type = new QComboBox(m_tree);
        rw.type->addItems({"Blank", "Rx", "Tx"});
        rw.bus = makeBusCombo(m_tree);
        rw.forward = new QCheckBox(m_tree);
        rw.fwdBus = makeBusCombo(m_tree);
        rw.freq = new QComboBox(m_tree);
        for (int f : txFrequencies()) rw.freq->addItem(QString("%1 Hz").arg(f));
        rw.freq->setCurrentIndex(5); // default 50 Hz
        rw.mux = new QComboBox(m_tree);
        rw.mux->addItems({"Batch", "Sequential"});

        for (QComboBox *c : {rw.type, rw.bus, rw.fwdBus, rw.freq, rw.mux})
            guardCombo(c);

        m_tree->setItemWidget(item, COL_TYPE, rw.type);
        m_tree->setItemWidget(item, COL_BUS, rw.bus);
        // wrap the checkbox so it centers nicely
        m_tree->setItemWidget(item, COL_FWD, rw.forward);
        m_tree->setItemWidget(item, COL_FWDBUS, rw.fwdBus);
        m_tree->setItemWidget(item, COL_FREQ, rw.freq);
        m_tree->setItemWidget(item, COL_MUX, rw.mux);
        m_rows[i] = rw;

        // children = signals (start disabled to match the unchecked message)
        for (int j = 0; j < (int)m.sigs.size(); ++j) {
            m.sigs[j].enabled = false;
            auto *sitem = new QTreeWidgetItem(item);
            sitem->setData(COL_NAME, Qt::UserRole, i);
            sitem->setData(COL_NAME, Qt::UserRole + 1, j);
            sitem->setText(COL_NAME, QString::fromStdString(m.sigs[j].name));
            sitem->setFlags(sitem->flags() | Qt::ItemIsUserCheckable);
            sitem->setCheckState(COL_NAME, Qt::Unchecked);
        }

        // --- wire per-message widgets ---
        connect(rw.type, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this, i](int idx) {
                    m_db.messages[i].type = static_cast<MsgType>(idx);
                    refreshRowState(i);
                });
        connect(rw.bus, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this, i](int idx) {
                    m_db.messages[i].bus = indexToBus(idx);
                    rebuildFwdBusItems(i);
                });
        connect(rw.forward, &QCheckBox::toggled, this, [this, i](bool on) {
            m_db.messages[i].forward = on;
            refreshRowState(i);
        });
        connect(rw.fwdBus, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this, i](int) {
                    auto *c = m_rows[i].fwdBus;
                    m_db.messages[i].fwdBus =
                        indexToBus(c->currentData().toInt());
                });
        connect(rw.freq, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this, i](int idx) {
                    m_db.messages[i].txFreq = txFrequencies()[idx];
                });
        connect(rw.mux, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this, i](int idx) {
                    m_db.messages[i].muxMode = static_cast<MuxMode>(idx);
                });

        rebuildFwdBusItems(i);
        refreshRowState(i);
    }
    m_updating = false;

    m_tree->expandAll();
    m_tree->resizeColumnToContents(COL_NAME);
    if (m_tree->topLevelItemCount() > 0)
        m_tree->setCurrentItem(m_tree->topLevelItem(0)); // populates signal table
}

// Fwd-bus options exclude the message's own (received) bus.
void MainWindow::rebuildFwdBusItems(int i) {
    auto &m = m_db.messages[i];
    auto *c = m_rows[i].fwdBus;
    QSignalBlocker block(c);
    c->clear();
    for (int b = 0; b < 3; ++b) {
        if (b == busToIndex(m.bus)) continue;
        c->addItem(QString("CAN %1").arg(b + 1), b);
    }
    // ensure model's fwdBus is valid (not equal to bus)
    if (m.fwdBus == m.bus) {
        m.fwdBus = indexToBus(c->itemData(0).toInt());
    }
    // select the model's current fwdBus
    for (int k = 0; k < c->count(); ++k)
        if (c->itemData(k).toInt() == busToIndex(m.fwdBus)) {
            c->setCurrentIndex(k);
            break;
        }
}

void MainWindow::refreshRowState(int i) {
    auto &m = m_db.messages[i];
    auto &rw = m_rows[i];
    bool isRx = (m.type == MsgType::Rx);
    bool isTx = (m.type == MsgType::Tx);
    rw.bus->setEnabled(m.type != MsgType::Blank);
    rw.forward->setEnabled(isRx);
    rw.fwdBus->setEnabled(isRx && m.forward);
    rw.freq->setEnabled(isTx);
    rw.mux->setEnabled(isTx && m.hasMux());
}

// Apply an enabled state to a signal and mirror it into the tree child, the
// signal table (if shown) and the parent message's tristate. Runs under the
// re-entrancy guard so the mirrored writes don't re-trigger handlers.
void MainWindow::setSignalEnabled(int msgIndex, int sigIndex, bool on) {
    auto &m = m_db.messages[msgIndex];
    if (sigIndex < 0 || sigIndex >= (int)m.sigs.size()) return;
    m.sigs[sigIndex].enabled = on;

    m_updating = true;
    auto *mItem = m_rows[msgIndex].item;
    if (sigIndex < mItem->childCount())
        mItem->child(sigIndex)->setCheckState(COL_NAME,
                                              on ? Qt::Checked : Qt::Unchecked);
    if (msgIndex == m_sigTableMsg && sigIndex < m_sigTable->rowCount())
        if (auto *cell = m_sigTable->item(sigIndex, S_EN))
            cell->setCheckState(on ? Qt::Checked : Qt::Unchecked);
    m_updating = false;

    syncMessageCheckState(msgIndex);
}

// Set the message's checkbox to checked / partial / unchecked from its signals.
void MainWindow::syncMessageCheckState(int msgIndex) {
    auto &m = m_db.messages[msgIndex];
    int n = (int)m.sigs.size(), on = 0;
    for (const auto &s : m.sigs) if (s.enabled) ++on;
    Qt::CheckState st = (on == 0) ? Qt::Unchecked
                        : (on == n) ? Qt::Checked
                                    : Qt::PartiallyChecked;
    m.checked = (on > 0);
    m_updating = true;
    m_rows[msgIndex].item->setCheckState(COL_NAME, st);
    m_updating = false;
}

// Bulk-set every message to a type. Rx/Tx also checks the message and enables
// all its signals; Blank unchecks everything (nothing to export).
void MainWindow::setAllMessages(MsgType t) {
    if (!m_hasDbc) return;
    const bool active = (t != MsgType::Blank);
    m_updating = true;
    for (int i = 0; i < (int)m_db.messages.size(); ++i) {
        auto &m = m_db.messages[i];
        auto &rw = m_rows[i];
        m.type = t;
        rw.type->setCurrentIndex(static_cast<int>(t));
        m.checked = active;
        rw.item->setCheckState(COL_NAME, active ? Qt::Checked : Qt::Unchecked);
        for (int j = 0; j < (int)m.sigs.size(); ++j) {
            m.sigs[j].enabled = active;
            if (j < rw.item->childCount())
                rw.item->child(j)->setCheckState(
                    COL_NAME, active ? Qt::Checked : Qt::Unchecked);
        }
        refreshRowState(i);
    }
    m_updating = false;
    if (m_sigTableMsg >= 0) populateSignalTable(m_sigTableMsg);
}

// Assign every message to one bus and refresh the forward-bus options (which
// exclude each message's own bus).
void MainWindow::setAllBus(Bus b) {
    if (!m_hasDbc) return;
    for (int i = 0; i < (int)m_db.messages.size(); ++i) {
        m_db.messages[i].bus = b;
        QSignalBlocker block(m_rows[i].bus);
        m_rows[i].bus->setCurrentIndex(busToIndex(b));
        rebuildFwdBusItems(i);
    }
}

// Check (enable) or uncheck (disable) every message and signal, leaving each
// message's Rx/Tx/Blank type as-is.
void MainWindow::setAllEnabled(bool on) {
    if (!m_hasDbc) return;
    m_updating = true;
    for (int i = 0; i < (int)m_db.messages.size(); ++i) {
        auto &m = m_db.messages[i];
        auto &rw = m_rows[i];
        m.checked = on;
        rw.item->setCheckState(COL_NAME, on ? Qt::Checked : Qt::Unchecked);
        for (int j = 0; j < (int)m.sigs.size(); ++j) {
            m.sigs[j].enabled = on;
            if (j < rw.item->childCount())
                rw.item->child(j)->setCheckState(
                    COL_NAME, on ? Qt::Checked : Qt::Unchecked);
        }
    }
    m_updating = false;
    if (m_sigTableMsg >= 0) populateSignalTable(m_sigTableMsg);
}

void MainWindow::onTreeItemChanged(QTreeWidgetItem *item, int column) {
    if (m_updating || column != COL_NAME) return;

    if (!item->parent()) {
        // Message toggled directly by the user: cascade to every signal.
        int idx = item->data(COL_NAME, Qt::UserRole).toInt();
        bool checked = item->checkState(COL_NAME) == Qt::Checked;
        m_db.messages[idx].checked = checked;
        m_updating = true;
        for (int c = 0; c < item->childCount(); ++c) {
            item->child(c)->setCheckState(COL_NAME,
                                          checked ? Qt::Checked : Qt::Unchecked);
            m_db.messages[idx].sigs[c].enabled = checked;
        }
        if (idx == m_sigTableMsg) {
            for (int r = 0; r < m_sigTable->rowCount(); ++r)
                if (auto *cell = m_sigTable->item(r, S_EN))
                    cell->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
        }
        m_updating = false;
    } else {
        // Single signal toggled: update it and recompute the parent tristate.
        int msgIdx = item->data(COL_NAME, Qt::UserRole).toInt();
        int sigIdx = item->data(COL_NAME, Qt::UserRole + 1).toInt();
        setSignalEnabled(msgIdx, sigIdx,
                         item->checkState(COL_NAME) == Qt::Checked);
    }
}

void MainWindow::onTreeSelectionChanged() {
    int idx = currentMessageIndex();
    if (idx >= 0) populateSignalTable(idx);
}

void MainWindow::populateSignalTable(int msgIndex) {
    m_updating = true;
    m_sigTableMsg = msgIndex;
    auto &m = m_db.messages[msgIndex];
    m_sigTable->setRowCount((int)m.sigs.size());

    for (int r = 0; r < (int)m.sigs.size(); ++r) {
        auto &s = m.sigs[r];

        auto *en = new QTableWidgetItem();
        en->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        en->setCheckState(s.enabled ? Qt::Checked : Qt::Unchecked);
        m_sigTable->setItem(r, S_EN, en);

        auto ro = [&](const QString &txt) {
            auto *it = new QTableWidgetItem(txt);
            it->setFlags(Qt::ItemIsEnabled); // read-only
            return it;
        };
        QString muxTag = s.isMultiplexer ? "  [M]"
                         : s.isMultiplexed
                             ? QString("  [m%1]").arg(s.muxId)
                             : QString();
        m_sigTable->setItem(r, S_NAME,
                            ro(QString::fromStdString(s.name) + muxTag));
        m_sigTable->setItem(r, S_START, ro(QString::number(s.startBit)));
        m_sigTable->setItem(r, S_LEN, ro(QString::number(s.length)));
        QString dt = s.isDouble ? "double" : s.isFloat ? "float"
                     : s.isSigned                      ? "signed"
                                                       : "unsigned";
        dt += s.bigEndian ? " / BE" : " / LE";
        m_sigTable->setItem(r, S_DBCTYPE, ro(dt));
        m_sigTable->setItem(r, S_FACTOR,
                            ro(QString::fromStdString(numLiteral(s.factor))));
        m_sigTable->setItem(r, S_OFFSET,
                            ro(QString::fromStdString(numLiteral(s.offset))));

        auto *dps = new QTableWidgetItem(QString::number(s.dps));
        m_sigTable->setItem(r, S_DPS, dps);

        // Returned type: enum (fixed) when the signal has a value table,
        // otherwise an editable dropdown seeded with the inferred default.
        if (s.hasValueTable()) {
            m_sigTable->setItem(
                r, S_RTYPE, ro(QString::fromStdString(enumTypeName(s)) + " (enum)"));
        } else {
            auto *combo = new QComboBox(m_sigTable);
            for (const auto &t : returnTypeOptions())
                combo->addItem(QString::fromStdString(t));
            guardCombo(combo);
            int sel = combo->findText(QString::fromStdString(s.returnType));
            combo->setCurrentIndex(sel >= 0 ? sel : 0);
            connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    this, [this, msgIndex, r](int) {
                        auto *c = qobject_cast<QComboBox *>(
                            m_sigTable->cellWidget(r, S_RTYPE));
                        if (c)
                            m_db.messages[msgIndex].sigs[r].returnType =
                                c->currentText().toStdString();
                    });
            m_sigTable->setCellWidget(r, S_RTYPE, combo);
        }
    }
    m_sigTable->resizeColumnsToContents();
    m_sigTable->horizontalHeader()->setStretchLastSection(true);
    m_updating = false;
}

void MainWindow::onExport() {
    if (!m_hasDbc) {
        QMessageBox::information(this, "Export", "Load a DBC file first.");
        return;
    }
    bool anySelected = false;
    for (const auto &m : m_db.messages)
        if (m.checked && m.type != MsgType::Blank) { anySelected = true; break; }
    if (!anySelected) {
        QMessageBox::information(
            this, "Export",
            "No messages are checked and set to Rx or Tx. Nothing to generate.");
        return;
    }

    QString base = QFileInfo(m_dbcPath).completeBaseName();
    QString suggested =
        QFileInfo(m_dbcPath).absolutePath() + "/" + base + ".c";
    QString chosen = QFileDialog::getSaveFileName(
        this, "Export generated .c (matching .h and _instructions.txt written too)",
        suggested, "C Source (*.c)");
    if (chosen.isEmpty()) return;

    QFileInfo fi(chosen);
    QString outBase = fi.completeBaseName();
    QString dir = fi.absolutePath();

    GeneratedFiles g = generate(m_db, outBase.toStdString());

    auto writeFile = [&](const QString &name, const std::string &content) -> bool {
        QFile f(dir + "/" + name);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
        QTextStream ts(&f);
        ts << QString::fromStdString(content);
        return true;
    };

    QString hName = outBase + ".h";
    QString cName = outBase + ".c";
    QString tName = outBase + "_instructions.txt";
    bool ok = writeFile(hName, g.header) && writeFile(cName, g.source) &&
              writeFile(tName, g.instructions);

    if (!ok) {
        QMessageBox::critical(this, "Export failed",
                              "Could not write output files to " + dir);
        return;
    }
    QMessageBox::information(
        this, "Export complete",
        QString("Wrote:\n  %1\n  %2\n  %3\n\nin %4")
            .arg(cName, hName, tName, dir));
}
