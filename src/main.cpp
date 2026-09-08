
#include <cstdlib>
#include <fstream>
#include <print>

#include "CLIUtils/CLI11.hpp"

struct Options {
    std::string input;
    std::string output = "a.out";
    bool lex = false;
    bool parse = false;
    bool analyze = false;
};

Options parseArgs(int argc, char** argv) {
    Options opts;
    CLI::App app{"Program Options"};

    app.add_option("input", opts.input, "Input source file")
        ->required();
    app.add_option("-o,--output", opts.output, "Name of output file")
        ->capture_default_str();
    app.add_flag("-l,--lex", opts.lex, "Stop after lexing phase, output Token Stream");
    app.add_flag("-p,--parse", opts.parse, "Stop after parsing phase, output AST");
    app.add_flag("-a,--analyze", opts.analyze, "Stop after analysis phase, output Annotated AST");

    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        std::exit(app.exit(e));
    }

    return opts;
}

std::string readFileIntoString(std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::println(stderr,
            "Input file '{}' could not be opened for reading",
            filename);
        std::exit(EXIT_FAILURE);
    }
    auto content = std::string(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
    file.close();
    return content;
}

void writeStringToFile(std::string& filename, std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::println(stderr,
            "Output file '{}' could not be opened for writing",
            filename);
        std::exit(EXIT_FAILURE);
    }
    file << content;
    file.close();
}

#include "types/symbol_table.hpp"
#include "types/token.hpp"
#include "types/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "analyzer/analyzer.hpp"

int main(int argc, char** argv) {
    Options opts = parseArgs(argc, argv);

    std::string source = readFileIntoString(opts.input);
    SymbolTable st;
    std::vector<Token> tokens = lexer(source, st);
    if (opts.lex) {
        auto json = tokensToJsonString(tokens, 4);
        writeStringToFile(opts.output, json);
        println("Lexer output writen succesfuly to {}", opts.output);
        return EXIT_SUCCESS;
    }
    AST ast = parser(tokens, st);
    analyzer(ast, st);
    return EXIT_SUCCESS;
}
