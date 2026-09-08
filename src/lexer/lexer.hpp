#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <string_view>
#include <vector>

#include "types/symbol_table.hpp"
#include "types/token.hpp"

std::vector<Token> lexer(std::string_view source, SymbolTable& st);

#endif
