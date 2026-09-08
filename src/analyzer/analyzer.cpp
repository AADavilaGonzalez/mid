
#include <cstdlib>
#include <print>

#include "types/symbol_table.hpp"
#include "types/ast.hpp"

void analyzer(AST& ast, SymbolTable& st) {
    std::println(stderr, "Reached semantic analysis phase");
    std::println(stderr, "ERROR: phase not implemented, aborting program execution");
    std::exit(EXIT_FAILURE);
}
