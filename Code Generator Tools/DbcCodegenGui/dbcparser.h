// dbcparser.h - minimal, dependency-free DBC parser.
#ifndef DBCPARSER_H
#define DBCPARSER_H

#include "dbc.h"
#include <string>

namespace dbc {

// Parse DBC text. On failure returns false and fills `error`.
bool parseString(const std::string &text, Database &out, std::string &error);
bool parseFile(const std::string &path, Database &out, std::string &error);

} // namespace dbc

#endif // DBCPARSER_H
