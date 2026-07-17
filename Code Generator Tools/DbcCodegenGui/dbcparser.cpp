// dbcparser.cpp - minimal DBC parser supporting the subset this tool needs:
//   BU_, BO_, SG_ (incl. multiplexing), VAL_, SIG_VALTYPE_, BA_ GenMsgCycleTime
#include "dbcparser.h"

#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <cmath>

namespace dbc {

namespace {

std::string trim(const std::string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::vector<std::string> splitWs(const std::string &s) {
    std::vector<std::string> out;
    std::istringstream iss(s);
    std::string tok;
    while (iss >> tok) out.push_back(tok);
    return out;
}

// Snap a cycle time in ms to the nearest supported Tx frequency.
int snapFrequency(double hz) {
    const auto &opts = txFrequencies();
    int best = opts.front();
    double bestErr = std::abs(hz - best);
    for (int f : opts) {
        double e = std::abs(hz - f);
        if (e < bestErr) { bestErr = e; best = f; }
    }
    return best;
}

} // namespace

bool parseString(const std::string &text, Database &out, std::string &error) {
    out = Database{};
    error.clear();

    std::map<uint32_t, size_t> idToIndex; // raw DBC id -> messages index

    // SG_ Name [M|m0] : start|len@order sign (factor,offset) [min|max] "unit" recv
    static const std::regex reSg(
        R"RE(^\s*SG_\s+(\w+)\s*(M|m\d+)?\s*:\s*(\d+)\|(\d+)@([01])([+-])\s*\(([^,]+),([^)]+)\)\s*\[([^|]*)\|([^\]]*)\]\s*"([^"]*)"\s*(.*)$)RE");
    static const std::regex reBo(
        R"RE(^\s*BO_\s+(\d+)\s+(\w+)\s*:\s*(\d+)\s+(\w+))RE");
    static const std::regex reBu(R"RE(^\s*BU_\s*:\s*(.*)$)RE");
    static const std::regex reValTypeF(
        R"RE(^\s*SIG_VALTYPE_\s+(\d+)\s+(\w+)\s*:\s*(\d+)\s*;?)RE");
    static const std::regex reVal(
        R"RE(^\s*VAL_\s+(\d+)\s+(\w+)\s+(.*);\s*$)RE");
    static const std::regex reCycle(
        R"RE(^\s*BA_\s+"GenMsgCycleTime"\s+BO_\s+(\d+)\s+(\d+))RE");
    static const std::regex reValPair(R"RE((-?\d+)\s+"([^"]*)")RE");

    std::istringstream stream(text);
    std::string line;
    Message *current = nullptr; // message currently accumulating SG_ lines

    while (std::getline(stream, line)) {
        // Strip CR so $-anchored regexes work on CRLF (Windows) DBC files.
        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::smatch m;

        if (std::regex_search(line, m, reBo)) {
            uint32_t rawId = static_cast<uint32_t>(std::stoul(m[1].str()));
            Message msg;
            msg.extended = (rawId & 0x80000000u) != 0;
            msg.id = rawId & 0x1FFFFFFFu;
            msg.name = m[2].str();
            msg.dlc = static_cast<uint8_t>(std::stoul(m[3].str()));
            std::string sender = m[4].str();
            if (sender != "Vector__XXX") msg.senders.push_back(sender);
            out.messages.push_back(std::move(msg));
            idToIndex[rawId] = out.messages.size() - 1;
            current = &out.messages.back();
            continue;
        }

        if (std::regex_search(line, m, reSg)) {
            if (!current) continue; // SG_ outside a BO_ block: skip
            Signal s;
            s.name = m[1].str();
            std::string mux = m[2].str();
            if (mux == "M") {
                s.isMultiplexer = true;
            } else if (!mux.empty() && mux[0] == 'm') {
                s.isMultiplexed = true;
                s.muxId = std::stoi(mux.substr(1));
            }
            s.startBit = static_cast<uint16_t>(std::stoul(m[3].str()));
            s.length = static_cast<uint8_t>(std::stoul(m[4].str()));
            s.bigEndian = (m[5].str() == "0"); // @0 = Motorola/big-endian
            s.isSigned = (m[6].str() == "-");
            s.factor = std::stod(m[7].str());
            s.offset = std::stod(m[8].str());
            try { s.minVal = std::stod(m[9].str()); } catch (...) { s.minVal = 0; }
            try { s.maxVal = std::stod(m[10].str()); } catch (...) { s.maxVal = 0; }
            s.unit = m[11].str();
            for (const auto &r : splitWs(m[12].str()))
                if (r != "Vector__XXX") s.receivers.push_back(r);
            s.returnType = defaultReturnType(s);
            s.enabled = true;
            current->sigs.push_back(std::move(s));
            continue;
        }

        if (std::regex_search(line, m, reBu)) {
            for (const auto &n : splitWs(m[1].str()))
                if (n != "Vector__XXX") out.nodes.push_back(n);
            continue;
        }

        if (std::regex_search(line, m, reValTypeF)) {
            uint32_t rawId = static_cast<uint32_t>(std::stoul(m[1].str()));
            std::string sig = m[2].str();
            int t = std::stoi(m[3].str());
            auto it = idToIndex.find(rawId);
            if (it != idToIndex.end()) {
                for (auto &s : out.messages[it->second].sigs) {
                    if (s.name == sig) {
                        if (t == 1) { s.isFloat = true; }
                        else if (t == 2) { s.isDouble = true; }
                        s.returnType = defaultReturnType(s);
                    }
                }
            }
            continue;
        }

        if (std::regex_search(line, m, reVal)) {
            uint32_t rawId = static_cast<uint32_t>(std::stoul(m[1].str()));
            std::string sig = m[2].str();
            std::string rest = m[3].str();
            auto it = idToIndex.find(rawId);
            if (it != idToIndex.end()) {
                for (auto &s : out.messages[it->second].sigs) {
                    if (s.name == sig) {
                        auto begin = std::sregex_iterator(rest.begin(), rest.end(), reValPair);
                        auto end = std::sregex_iterator();
                        for (auto i = begin; i != end; ++i) {
                            ValuePair vp;
                            vp.value = std::stol((*i)[1].str());
                            vp.name = (*i)[2].str();
                            s.valueTable.push_back(vp);
                        }
                    }
                }
            }
            continue;
        }

        if (std::regex_search(line, m, reCycle)) {
            uint32_t rawId = static_cast<uint32_t>(std::stoul(m[1].str()));
            double ms = std::stod(m[2].str());
            auto it = idToIndex.find(rawId);
            if (it != idToIndex.end() && ms > 0) {
                out.messages[it->second].txFreq = snapFrequency(1000.0 / ms);
            }
            continue;
        }
    }

    if (out.messages.empty()) {
        error = "No CAN messages (BO_) found in file.";
        return false;
    }
    return true;
}

bool parseFile(const std::string &path, Database &out, std::string &error) {
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        error = "Could not open file: " + path;
        return false;
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return parseString(ss.str(), out, error);
}

} // namespace dbc
