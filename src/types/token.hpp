#ifndef TYPES_TOKEN_H
#define TYPES_TOKEN_H

#include <cstddef>
#include <string_view>
#include <vector>

enum struct TokenType {
    //Literals
    INTEGER, FLOAT, TRUE, FALSE, STRING, CHAR, IDENTIFIER,

    //Program Structure
    LPAREN, RPAREN, LBRACE, RBRACE, COMMA, SEMICOLON,

    //Typing
    COLON, ARROW,

    //Arithmetic Operators
    PLUS, MINUS, STAR, SLASH, PERCENT,

    //Comparison Operators
    GREATER, LESSER, EQUAL_EQUAL, BANG_EQUAL, GREATER_EQUAL, LESSER_EQUAL,

    //Logical Operators
    BANG, AND, OR,

    //Assignment Operators
    EQUAL, COLON_EQUAL, PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL, PERCENT_EQUAL,

    //Program Flow Keywords
    FUNCTION, RETURN, FOR, WHILE, LOOP, SWITCH, BOLD_ARROW, BREAK, CONTINUE, IF, ELSE,

    //Addressing and Arrays
    AMPERSAND, LBRACKET, RBRACKET,

    //Debug IO
    BUILTIN_READ, BUILTIN_WRITE,
};

struct Token {
    std::string_view lexeme;
    TokenType type;
    size_t line;
    size_t col;
};

std::string tokensToJsonString(std::vector<Token>&tokens, int indent=4);

#endif
