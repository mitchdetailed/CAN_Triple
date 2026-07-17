// dbc.h - DBC data model + pure helpers (start-bit conversion, type inference,
// identifier sanitizing). No Qt dependency so it can be unit-tested standalone.
#ifndef DBC_H
#define DBC_H

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cctype>

namespace dbc {

enum class MsgType { Blank, Rx, Tx };
enum class Bus { CAN1, CAN2, CAN3 };
enum class MuxMode { Batch, Sequential };

inline const char *busEnum(Bus b) {
    switch (b) {
    case Bus::CAN1: return "CAN_1";
    case Bus::CAN2: return "CAN_2";
    case Bus::CAN3: return "CAN_3";
    }
    return "CAN_1";
}
inline const char *busLabel(Bus b) {
    switch (b) {
    case Bus::CAN1: return "CAN 1";
    case Bus::CAN2: return "CAN 2";
    case Bus::CAN3: return "CAN 3";
    }
    return "CAN 1";
}

// Transmit rates the firmware scheduler exposes (events_NHz).
inline const std::vector<int> &txFrequencies() {
    static const std::vector<int> f = {1, 2, 5, 10, 20, 50, 100, 200};
    return f;
}

// Candidate C types for the "Returned Data Type" dropdown.
inline const std::vector<std::string> &returnTypeOptions() {
    static const std::vector<std::string> t = {
        "bool",     "uint8_t", "uint16_t", "uint32_t",
        "int8_t",   "int16_t", "int32_t",  "float"};
    return t;
}

struct ValuePair {
    long value;
    std::string name; // raw label from VAL_
};

struct Signal {
    // --- parsed from DBC ---
    std::string name;
    uint16_t startBit = 0;   // raw DBC start bit (MSB for Motorola)
    uint8_t length = 0;
    bool bigEndian = false;  // @0 = big/Motorola, @1 = little/Intel
    bool isSigned = false;
    bool isFloat = false;    // IEEE-754 (via SIG_VALTYPE_)
    bool isDouble = false;
    double factor = 1.0;
    double offset = 0.0;
    double minVal = 0.0;
    double maxVal = 0.0;
    std::string unit;
    std::vector<std::string> receivers;

    bool isMultiplexer = false; // the "M" selector signal
    bool isMultiplexed = false; // "m<n>"
    int muxId = -1;

    std::vector<ValuePair> valueTable; // from VAL_

    // --- UI state ---
    bool enabled = true;
    std::string returnType;  // filled with a sensible default; user can override
    int dps = 3;             // decimal places for dbc_decode

    bool hasValueTable() const { return !valueTable.empty(); }
};

struct Message {
    std::string name;
    uint32_t id = 0;        // 11/29-bit id (extended flag stripped)
    bool extended = false;
    uint8_t dlc = 0;
    std::vector<std::string> senders;
    std::vector<Signal> sigs; // "signals" collides with Qt's signals macro

    // --- UI state ---
    bool checked = false;
    MsgType type = MsgType::Blank;
    Bus bus = Bus::CAN1;
    bool forward = false;
    Bus fwdBus = Bus::CAN2;
    int txFreq = 50;
    MuxMode muxMode = MuxMode::Batch;

    bool hasMux() const {
        for (const auto &s : sigs)
            if (s.isMultiplexer) return true;
        return false;
    }
};

struct Database {
    std::vector<std::string> nodes;
    std::vector<Message> messages;
};

// ------------------------------------------------------------------
// Pure helpers (ported 1:1 from the Python tool where behaviour must match)
// ------------------------------------------------------------------

// Motorola (big-endian) bit-position map, identical to the Python tool so the
// generated start bits match byte-for-byte.
inline const int *motorolaMap() {
    static const int m[64] = {
        7,  6,  5,  4,  3,  2,  1,  0,  15, 14, 13, 12, 11, 10, 9,  8,
        23, 22, 21, 20, 19, 18, 17, 16, 31, 30, 29, 28, 27, 26, 25, 24,
        39, 38, 37, 36, 35, 34, 33, 32, 47, 46, 45, 44, 43, 42, 41, 40,
        55, 54, 53, 52, 51, 50, 49, 48, 63, 62, 61, 60, 59, 58, 57, 56};
    return m;
}

// Convert a signal's DBC start bit to the LSB position the firmware's
// dbc_decode/dbc_encode expect. Matches get_dbc_start_bit() in the Python tool.
inline int firmwareStartBit(const Signal &s) {
    if (!s.bigEndian) return s.startBit; // little-endian passes through
    const int *map = motorolaMap();
    int idx = -1;
    for (int i = 0; i < 64; ++i)
        if (map[i] == s.startBit) { idx = i; break; }
    if (idx < 0 || idx + s.length - 1 >= 64) return s.startBit; // fallback
    return map[idx + s.length - 1];
}

// Sanitize an arbitrary DBC token into a valid C identifier fragment.
inline std::string sanitize(const std::string &in) {
    std::string out;
    for (char c : in) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_')
            out += c;
        else
            out += '_';
    }
    if (out.empty()) out = "_";
    if (std::isdigit(static_cast<unsigned char>(out[0]))) out = "_" + out;
    return out;
}

inline std::string toUpper(const std::string &in) {
    std::string out = in;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return out;
}

// Enum type name for a signal that carries a value table, e.g. "Gear_t".
inline std::string enumTypeName(const Signal &s) {
    return sanitize(s.name) + "_t";
}

// Enumerator constant, e.g. GEAR_NEUTRAL.
inline std::string enumConstName(const Signal &s, const std::string &label) {
    return toUpper(sanitize(s.name)) + "_" + toUpper(sanitize(label));
}

// Default "Returned Data Type" from range + scaling, matching the Python tool's
// get_signal_type() (with the signed raw_max fix).
inline std::string defaultReturnType(const Signal &s) {
    if (s.isFloat || s.isDouble) return "float";

    bool scaleInt = (s.factor == std::floor(s.factor));
    bool offsetInt = (s.offset == std::floor(s.offset));
    if (!scaleInt || !offsetInt) return "float";

    long rawMin, rawMax;
    if (s.isSigned) {
        rawMin = -(1L << (s.length - 1));
        rawMax = (1L << (s.length - 1)) - 1;
    } else {
        rawMin = 0;
        rawMax = (s.length >= 32) ? 0xFFFFFFFFL : ((1L << s.length) - 1);
    }

    long scale = static_cast<long>(s.factor);
    long off = static_cast<long>(s.offset);
    long physMin = rawMin * scale + off;
    long physMax = rawMax * scale + off;
    if (physMin > physMax) std::swap(physMin, physMax);

    if (physMin == 0 && physMax == 1) return "bool";

    if (physMin < 0) {
        if (physMin >= -128 && physMax <= 127) return "int8_t";
        if (physMin >= -32768 && physMax <= 32767) return "int16_t";
        return "int32_t";
    }
    if (physMax <= 255) return "uint8_t";
    if (physMax <= 65535) return "uint16_t";
    return "uint32_t";
}

// dbc_encode datatype enum for a (non-float) signal.
inline std::string encodeDatatype(const Signal &s) {
    if (s.isSigned) return "DBC_SIGNED";
    return "DBC_UNSIGNED";
}

// Format a double for C source without trailing ".0" noise but keeping floats.
inline std::string numLiteral(double v) {
    if (v == std::floor(v) && std::abs(v) < 1e15) {
        return std::to_string(static_cast<long long>(v));
    }
    std::string s = std::to_string(v);
    // trim trailing zeros
    while (s.size() > 1 && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s.pop_back();
    return s;
}

} // namespace dbc

#endif // DBC_H
