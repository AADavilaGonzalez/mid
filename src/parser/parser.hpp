#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <vector>

#include "types/symbol_table.hpp"
#include "types/token.hpp"
#include "types/ast.hpp"

AST parser(std::vector<Token> tokens, SymbolTable& st);

#endif
