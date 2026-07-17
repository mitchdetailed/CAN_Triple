// codegen.h - turns a Database (with UI selections) into .c / .h / .txt strings.
#ifndef CODEGEN_H
#define CODEGEN_H

#include "dbc.h"
#include <string>

namespace dbc {

struct GeneratedFiles {
    std::string header;       // <module>.h
    std::string source;       // <module>.c
    std::string instructions; // <module>_instructions.txt
};

// moduleBase: bare name derived from the DBC filename (e.g. "vehicle").
GeneratedFiles generate(const Database &db, const std::string &moduleBase);

} // namespace dbc

#endif // CODEGEN_H
