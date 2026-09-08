
#include <cstdlib>
#include <print>
#include <vector>

#include "types/symbol_table.hpp"
#include "types/token.hpp"
#include "types/ast.hpp"

AST parser(std::vector<Token> tokens, SymbolTable& st) { 
    std::println(stderr, "Reached syntactic analysis phase");
    std::println(stderr, "ERROR: phase not implemented, aborting program execution");
    std::exit(EXIT_FAILURE);
}
