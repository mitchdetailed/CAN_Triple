// codegen.cpp - emit firmware-ready C from the selected DBC messages/signals.
#include "codegen.h"

#include <sstream>
#include <set>
#include <map>
#include <algorithm>

namespace dbc {

namespace {

std::string capitalize(const std::string &s) {
    if (s.empty()) return s;
    std::string out = s;
    out[0] = static_cast<char>(std::toupper((unsigned char)out[0]));
    return out;
}
std::string lower(const std::string &s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return out;
}

// Hex string for a CAN id, e.g. 0x123.
std::string hexId(uint32_t id) {
    std::ostringstream ss;
    ss << "0x" << std::uppercase << std::hex << id;
    return ss.str();
}

bool isActive(const Message &m) {
    return m.checked && (m.type == MsgType::Rx || m.type == MsgType::Tx);
}

// Field type used in the storage struct for a signal.
std::string fieldType(const Signal &s) {
    if (s.hasValueTable()) return enumTypeName(s);
    return s.returnType.empty() ? defaultReturnType(s) : s.returnType;
}

std::string decodeCast(const std::string &type) {
    return (type == "float") ? "" : "(" + type + ")";
}

// Emit a single dbc_decode / dbc_decode_IEEE754 expression (no assignment).
std::string decodeExpr(const Signal &s) {
    std::ostringstream e;
    int start = firmwareStartBit(s);
    const char *big = s.bigEndian ? "true" : "false";
    if (s.isFloat || s.isDouble) {
        const char *isDouble = s.isDouble ? "true" : "false";
        e << "dbc_decode_IEEE754(Message.data, " << isDouble << ", " << big << ", "
          << start << ", " << (int)s.length << ", " << numLiteral(s.factor) << ", "
          << numLiteral(s.offset) << ", " << s.dps << ")";
    } else {
        const char *sign = s.isSigned ? "true" : "false";
        e << "dbc_decode(Message.data, " << sign << ", " << big << ", " << start
          << ", " << (int)s.length << ", " << numLiteral(s.factor) << ", "
          << numLiteral(s.offset) << ", " << s.dps << ")";
    }
    return e.str();
}

// Emit a dbc_encode / dbc_encode_ieee754 statement for `valueExpr`.
std::string encodeStmt(const Signal &s, const std::string &bufExpr, int dlc,
                       const std::string &valueExpr) {
    std::ostringstream e;
    int start = firmwareStartBit(s);
    const char *big = s.bigEndian ? "true" : "false";
    if (s.isFloat || s.isDouble) {
        const char *isFloat = s.isDouble ? "false" : "true";
        e << "dbc_encode_ieee754(" << bufExpr << ", " << dlc << ", " << isFloat
          << ", " << big << ", " << valueExpr << ", " << start << ", "
          << (int)s.length << ");";
    } else {
        e << "dbc_encode(" << bufExpr << ", " << dlc << ", " << encodeDatatype(s)
          << ", " << big << ", " << valueExpr << ", " << start << ", "
          << (int)s.length << ", " << numLiteral(s.factor) << ", "
          << numLiteral(s.offset) << ");";
    }
    return e.str();
}

} // namespace

GeneratedFiles generate(const Database &db, const std::string &moduleBase) {
    const std::string base = sanitize(moduleBase.empty() ? "can_module" : moduleBase);
    const std::string prefix = lower(base);           // function prefix
    const std::string inst = capitalize(base);        // struct instance / type prefix
    const std::string structType = inst + "_Data_t";
    const std::string guard = toUpper(base) + "_H";

    // ---- Collect struct fields (deduped) and enum types across active msgs ----
    std::vector<std::pair<std::string, std::string>> fields; // name, type (ordered)
    std::map<std::string, std::string> fieldTypes;           // name -> type
    std::vector<const Signal *> enumSignals;                 // signals w/ value tables
    std::set<std::string> enumTypesSeen;
    int maxTxDlc = 8;
    bool anyTx = false;

    auto addField = [&](const Signal &s) {
        std::string n = sanitize(s.name);
        std::string t = fieldType(s);
        auto it = fieldTypes.find(n);
        if (it == fieldTypes.end()) {
            fieldTypes[n] = t;
            fields.emplace_back(n, t);
        } else if (it->second != t) {
            // conflicting types for same name: widen numeric to float, keep enums
            if (it->second.rfind("_t") == std::string::npos &&
                t.rfind("_t") == std::string::npos) {
                it->second = "float";
                for (auto &f : fields)
                    if (f.first == n) f.second = "float";
            }
        }
        if (s.hasValueTable()) {
            std::string et = enumTypeName(s);
            if (!enumTypesSeen.count(et)) {
                enumTypesSeen.insert(et);
                enumSignals.push_back(&s);
            }
        }
    };

    for (const auto &m : db.messages) {
        if (!isActive(m)) continue;
        if (m.type == MsgType::Tx) {
            anyTx = true;
            maxTxDlc = std::max<int>(maxTxDlc, m.dlc);
        }
        for (const auto &s : m.sigs) {
            // Always keep a multiplexer selector for active mux messages (needed
            // to switch on receive / stamp on transmit).
            bool keep = s.enabled || (s.isMultiplexer && m.hasMux());
            if (keep) addField(s);
        }
    }

    // ---- Which Tx frequencies are actually used ----
    std::set<int> usedFreqs;
    for (const auto &m : db.messages)
        if (isActive(m) && m.type == MsgType::Tx) usedFreqs.insert(m.txFreq);

    // ================= HEADER =================
    std::ostringstream h;
    h << "#ifndef " << guard << "\n#define " << guard << "\n\n";
    h << "#include \"backend_functions.h\"\n#include <stdbool.h>\n#include <stdint.h>\n\n";

    if (!enumSignals.empty()) {
        h << "/* ---- Value-table enums ---- */\n";
        for (const Signal *s : enumSignals) {
            h << "typedef enum {\n";
            for (size_t i = 0; i < s->valueTable.size(); ++i) {
                const auto &vp = s->valueTable[i];
                h << "    " << enumConstName(*s, vp.name) << " = " << vp.value;
                h << (i + 1 < s->valueTable.size() ? ",\n" : "\n");
            }
            h << "} " << enumTypeName(*s) << ";\n\n";
        }
    }

    h << "/* ---- Decoded / encoded signal storage ---- */\ntypedef struct {\n";
    if (anyTx)
        h << "    uint8_t Message[" << maxTxDlc << "]; // TX assembly buffer\n";
    for (const auto &f : fields)
        h << "    " << f.second << " " << f.first << ";\n";
    h << "} " << structType << ";\n\n";
    h << "extern " << structType << " " << inst << ";\n\n";

    h << "void " << prefix << "_CAN_Receive(CAN_Message Message);\n";
    h << "void " << prefix << "_Events_Startup(void);\n";
    for (int f : usedFreqs)
        h << "void " << prefix << "_Events_" << f << "Hz(void);\n";
    h << "\n#endif /* " << guard << " */\n";

    // ================= SOURCE =================
    std::ostringstream c;
    c << "#include \"" << prefix << ".h\"\n#include <string.h>\n\n";
    c << structType << " " << inst << " = {0};\n\n";
    c << "void " << prefix << "_Events_Startup(void) {\n"
      << "    // Called once at boot. Seed default values here if needed.\n}\n\n";

    // ---- Receive ----
    c << "void " << prefix << "_CAN_Receive(CAN_Message Message) {\n";
    c << "    switch (Message.arbitration_id) {\n";
    for (const auto &m : db.messages) {
        if (!isActive(m) || m.type != MsgType::Rx) continue;
        c << "    case " << hexId(m.id) << ": { // " << m.name << "  (Rx on "
          << busLabel(m.bus) << ")\n";

        // common (non-mux) enabled signals + the selector
        const Signal *selector = nullptr;
        for (const auto &s : m.sigs) {
            if (s.isMultiplexer) { selector = &s; continue; }
            if (s.isMultiplexed) continue;
            if (!s.enabled) continue;
            std::string t = fieldType(s);
            c << "        " << inst << "." << sanitize(s.name) << " = "
              << decodeCast(t) << decodeExpr(s) << ";\n";
        }

        if (m.hasMux() && selector) {
            std::string selName = sanitize(selector->name);
            std::string selT = fieldType(*selector);
            c << "        " << inst << "." << selName << " = "
              << decodeCast(selT) << decodeExpr(*selector) << ";\n";
            // group signals by mux id
            std::map<int, std::vector<const Signal *>> groups;
            for (const auto &s : m.sigs)
                if (s.isMultiplexed && s.enabled) groups[s.muxId].push_back(&s);
            c << "        switch ((int)" << inst << "." << selName << ") {\n";
            for (const auto &g : groups) {
                c << "        case " << hexId((uint32_t)g.first) << ":\n";
                for (const Signal *s : g.second) {
                    std::string t = fieldType(*s);
                    c << "            " << inst << "." << sanitize(s->name) << " = "
                      << decodeCast(t) << decodeExpr(*s) << ";\n";
                }
                c << "            break;\n";
            }
            c << "        default: break;\n        }\n";
        }

        if (m.forward && m.fwdBus != m.bus) {
            c << "        // Forward received frame onto " << busLabel(m.fwdBus) << "\n";
            c << "        send_FDmessage(" << busEnum(m.fwdBus)
              << ", Message.is_extended_id, Message.arbitration_id, "
              << "Message.data_length, Message.data, Message.brs);\n";
        }
        c << "        break;\n    }\n";
    }
    c << "    default: break;\n    }\n}\n";

    // ---- Transmit, bucketed by frequency ----
    auto emitPlainTx = [&](std::ostringstream &o, const Message &m) {
        o << "    // " << m.name << " (" << hexId(m.id) << ")\n";
        o << "    memset(" << inst << ".Message, 0, sizeof(" << inst << ".Message));\n";
        for (const auto &s : m.sigs) {
            if (!s.enabled || s.isMultiplexer || s.isMultiplexed) continue;
            o << "    " << encodeStmt(s, inst + ".Message", m.dlc,
                                      inst + "." + sanitize(s.name))
              << "\n";
        }
        if (m.dlc > 8)
            o << "    send_FDmessage(" << busEnum(m.bus) << ", "
              << (m.extended ? "true" : "false") << ", " << hexId(m.id) << ", "
              << (int)m.dlc << ", " << inst << ".Message, false);\n";
        else
            o << "    send_message(" << busEnum(m.bus) << ", "
              << (m.extended ? "true" : "false") << ", " << hexId(m.id) << ", "
              << (int)m.dlc << ", " << inst << ".Message);\n";
    };

    auto emitMuxGroup = [&](std::ostringstream &o, const Message &m,
                            const Signal *selector, int muxId,
                            const std::vector<const Signal *> &group,
                            const std::string &indent) {
        o << indent << "memset(" << inst << ".Message, 0, sizeof(" << inst
          << ".Message));\n";
        if (selector)
            o << indent
              << encodeStmt(*selector, inst + ".Message", m.dlc, std::to_string(muxId))
              << " // mux selector = " << muxId << "\n";
        for (const auto &s : m.sigs) { // common (non-mux) signals
            if (!s.enabled || s.isMultiplexer || s.isMultiplexed) continue;
            o << indent << encodeStmt(s, inst + ".Message", m.dlc,
                                      inst + "." + sanitize(s.name))
              << "\n";
        }
        for (const Signal *s : group)
            o << indent << encodeStmt(*s, inst + ".Message", m.dlc,
                                      inst + "." + sanitize(s->name))
              << "\n";
        if (m.dlc > 8)
            o << indent << "send_FDmessage(" << busEnum(m.bus) << ", "
              << (m.extended ? "true" : "false") << ", " << hexId(m.id) << ", "
              << (int)m.dlc << ", " << inst << ".Message, false);\n";
        else
            o << indent << "send_message(" << busEnum(m.bus) << ", "
              << (m.extended ? "true" : "false") << ", " << hexId(m.id) << ", "
              << (int)m.dlc << ", " << inst << ".Message);\n";
    };

    auto emitMuxTx = [&](std::ostringstream &o, const Message &m) {
        const Signal *selector = nullptr;
        for (const auto &s : m.sigs)
            if (s.isMultiplexer) selector = &s;
        std::map<int, std::vector<const Signal *>> groups;
        for (const auto &s : m.sigs)
            if (s.isMultiplexed && s.enabled) groups[s.muxId].push_back(&s);
        if (groups.empty()) return;

        o << "    // " << m.name << " (" << hexId(m.id) << ") - multiplexed, "
          << (m.muxMode == MuxMode::Batch ? "batch" : "sequential") << "\n";

        if (m.muxMode == MuxMode::Batch) {
            for (const auto &g : groups)
                emitMuxGroup(o, m, selector, g.first, g.second, "    ");
        } else {
            std::string idxVar = sanitize(m.name) + "_mux_idx";
            o << "    static uint8_t " << idxVar << " = 0;\n";
            o << "    switch (" << idxVar << ") {\n";
            int caseIdx = 0;
            for (const auto &g : groups) {
                o << "    case " << caseIdx++ << ":\n";
                emitMuxGroup(o, m, selector, g.first, g.second, "        ");
                o << "        break;\n";
            }
            o << "    default: break;\n    }\n";
            o << "    " << idxVar << " = (" << idxVar << " + 1) % " << groups.size()
              << ";\n";
        }
    };

    for (int freq : usedFreqs) {
        c << "\nvoid " << prefix << "_Events_" << freq << "Hz(void) {\n";
        for (const auto &m : db.messages) {
            if (!isActive(m) || m.type != MsgType::Tx || m.txFreq != freq) continue;
            if (m.hasMux())
                emitMuxTx(c, m);
            else
                emitPlainTx(c, m);
        }
        c << "}\n";
    }

    // ================= INSTRUCTIONS =================
    std::ostringstream t;
    t << "==================================================================\n";
    t << " " << base << " - generated CAN interface (integration guide)\n";
    t << "==================================================================\n\n";
    t << "Files:\n";
    t << "  " << prefix << ".h   - struct, enums and function prototypes\n";
    t << "  " << prefix << ".c   - decode/encode/forward implementation\n\n";
    t << "1. Copy " << prefix << ".h into the 'include' folder of the project.\n";
    t << "   Copy " << prefix << ".c into the 'src' folder of the project.\n";
    t << "   Then add:  #include \"" << prefix << ".h\"  to user_code.c\n\n";
    t << "2. Receiving: in onReceive(CAN_Message Message) call:\n";
    t << "       " << prefix << "_CAN_Receive(Message);\n";
    t << "   Decoded values then live in the global struct '" << inst << "'.\n\n";
    t << "3. Transmitting: call each generated rate function from the matching\n";
    t << "   events_NHz() handler in user_code.c:\n";
    if (usedFreqs.empty())
        t << "       (no Tx messages selected)\n";
    for (int f : usedFreqs)
        t << "       events_" << f << "Hz():  " << prefix << "_Events_" << f
          << "Hz();\n";
    t << "   Set the signal fields on '" << inst << "' before the tick, e.g.\n";
    t << "       " << inst << ".SomeSignal = 123;\n\n";
    t << "4. One-time setup (optional): call " << prefix
      << "_Events_Startup() from events_Startup().\n\n";

    if (!enumSignals.empty()) {
        t << "Value-table enums (use these names when reading/writing those signals):\n";
        for (const Signal *s : enumSignals) {
            t << "  " << enumTypeName(*s) << ":  ";
            for (size_t i = 0; i < s->valueTable.size(); ++i)
                t << enumConstName(*s, s->valueTable[i].name)
                  << (i + 1 < s->valueTable.size() ? ", " : "");
            t << "\n";
        }
        t << "\n";
    }

    t << "Selected messages:\n";
    for (const auto &m : db.messages) {
        if (!isActive(m)) continue;
        t << "  " << hexId(m.id) << "  " << m.name << "  ["
          << (m.type == MsgType::Rx ? "Rx" : "Tx") << " on " << busLabel(m.bus)
          << "]";
        if (m.type == MsgType::Tx) t << "  @ " << m.txFreq << " Hz";
        if (m.type == MsgType::Rx && m.forward)
            t << "  -> forward to " << busLabel(m.fwdBus);
        if (m.type == MsgType::Tx && m.hasMux())
            t << "  (mux: " << (m.muxMode == MuxMode::Batch ? "batch" : "sequential")
              << ")";
        t << "\n";
    }

    return {h.str(), c.str(), t.str()};
}

} // namespace dbc
