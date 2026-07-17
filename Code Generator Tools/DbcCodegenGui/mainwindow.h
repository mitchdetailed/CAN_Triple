// mainwindow.h - main window for the DBC -> C code generator GUI.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "dbc.h"

class QTreeWidget;
class QTreeWidgetItem;
class QTableWidget;
class QComboBox;
class QCheckBox;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onLoadDbc();
    void onExport();
    void onTreeItemChanged(QTreeWidgetItem *item, int column);
    void onTreeSelectionChanged();

private:
    // Per-message row widgets so we can enable/disable them by message type.
    struct RowWidgets {
        QTreeWidgetItem *item = nullptr;
        QComboBox *type = nullptr;
        QComboBox *bus = nullptr;
        QCheckBox *forward = nullptr;
        QComboBox *fwdBus = nullptr;
        QComboBox *freq = nullptr;
        QComboBox *mux = nullptr;
    };

    void buildTree();
    void populateSignalTable(int msgIndex);
    void refreshRowState(int msgIndex);
    void setSignalEnabled(int msgIndex, int sigIndex, bool on); // model+tree+table
    void syncMessageCheckState(int msgIndex); // parent tristate from children
    void setAllMessages(dbc::MsgType t);      // bulk set every message's type
    void setAllEnabled(bool on);              // check/uncheck all (keeps types)
    void setAllBus(dbc::Bus b);               // assign every message to one bus
    void rebuildFwdBusItems(int msgIndex);
    int currentMessageIndex() const; // message row for current selection, or -1

    dbc::Database m_db;
    QString m_dbcPath;
    bool m_hasDbc = false;
    bool m_updating = false; // re-entrancy guard for checkbox cascades

    QTreeWidget *m_tree = nullptr;
    QTableWidget *m_sigTable = nullptr;
    QLabel *m_fileLabel = nullptr;
    QMap<int, RowWidgets> m_rows; // message index -> widgets
    int m_sigTableMsg = -1;       // message currently shown in signal table
};

#endif // MAINWINDOW_H
