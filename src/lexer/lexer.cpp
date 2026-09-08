
#include <optional>
#include <cstddef>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <print>
#include <format>

#include "types/symbol_table.hpp"
#include "types/token.hpp"

using enum TokenType;

static inline TokenType lookupKeyword(std::string_view identifier) {

    static const std::unordered_map<std::string_view, TokenType> keywords = {
        {"fn", FUNCTION}, {"return", RETURN},
        {"for", FOR}, {"while", WHILE}, {"loop", LOOP},
        {"switch", SWITCH}, {"break", BREAK}, {"continue", CONTINUE},
        {"if", IF}, {"else", ELSE},
        {"__read__", BUILTIN_READ}, {"__write__", BUILTIN_WRITE},
        {"true", TRUE}, {"false", FALSE},
    };

    auto it = keywords.find(identifier);
    return (it != keywords.end()) ? it->second : IDENTIFIER;
}

static inline bool isEscape(char c) {
    auto escape_chars = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '0'};
    for (char ec : escape_chars) {
        if (ec == c) { return true; }
    }
    return false;
}

static inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static inline bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || c == '_';
}

static inline bool isAlphaNum(char c) {
    return isDigit(c) || isAlpha(c);
}

std::vector<Token> lexer(const std::string_view source, SymbolTable& st) {

    size_t start = 0, current = 0;
    struct pos_t { size_t line, col; }
        pos_start,              //points to character consumed at start of iteration
        pos_curr = { 1, 1 };    //points to character yet to be consumed == peek()
    std::vector<Token> tokens;

    auto error = [](std::string_view msg, pos_t pos) {
        std::println(
            stderr, "Lexer Error[line:{}, col:{}]: {}",
            pos.line, pos.col, msg
        );
    };

    auto current_str = [&]() -> std::string_view {
        return source.substr(start, current-start);
    };

    auto newLine = [&]() { ++pos_curr.line; pos_curr.col = 1; };

    auto isAtEnd = [&]() -> bool { return current >= source.length(); };
 
    auto advance = [&]() -> char {
        if(isAtEnd()) { return '\0'; }
        ++pos_curr.col;
        return source[current++];
    };

    auto peek = [&](size_t i = 0) -> char {
        if(current + i>= source.length()) { return '\0'; }
        return source[current + i];
    };

    auto match = [&](char c) -> bool {
        if (isAtEnd() || source[current] != c) { return false; }
        ++pos_curr.col;
        ++current;
        return true;
    };

    auto seek = [&](char c) {
         while (peek() != c && !isAtEnd()) {
            if (advance() == '\n') { newLine(); }
         }
    };

    auto addToken = [&](TokenType t) {
        tokens.emplace_back(
            current_str(), t, pos_start.line, pos_start.col
        );
    };

    auto character = [&]() -> std::optional<TokenType> {
        if (peek() == '\\') {
            advance();
            if(!isEscape(peek()) && peek() != '\'') {
                auto msg = std::format("Unknown escape sequence '\\{}'", peek());
                error(msg, pos_curr);
                seek('\'');
                advance();
                return std::nullopt;
            }
        }

        if (peek(1) == '\'') {
            advance();
            advance();
            return CHAR;                     
        }
        
        seek('\'');
        advance();
        if (isAtEnd()) {
            error("Missing terminating ' character", pos_start);
        } else {
            error("Multi-character character constant", pos_start);  
        }
        return std::nullopt;
    };

    auto string = [&]() -> std::optional<TokenType> {
        while (peek() != '"' && !isAtEnd()) {
            char c = advance();
            if (c == '\n') { newLine(); }
            //If escape, discard next character whatever it is
            else if (c == '\\' && !isAtEnd()) {
                if (advance() == '\n') { newLine(); }
            }
        }
        if (isAtEnd()) {
            error("Unterminated string", pos_start);
            return std::nullopt;
        } else {
            advance();
            return STRING;
        }
    };

    auto number = [&]() -> std::optional<TokenType> {
        while (isDigit(peek())) { advance(); }
        if (peek() == '.') {
            advance();
            while(isDigit(peek())) { advance(); }
            return FLOAT;
        }
        else { return INTEGER; }
    };

    auto identifier = [&]() -> std::optional<TokenType> {
        while(isAlphaNum(peek())) { advance(); }
        return lookupKeyword(current_str());
    };

    while (!isAtEnd()) {
        start = current;
        pos_start = pos_curr;
        char c = advance();

        std::optional<TokenType> type = std::nullopt;

        switch (c) {
            case '(': type = LPAREN; break;
            case ')': type = RPAREN; break;
            case '{': type = LBRACE; break;
            case '}': type = RBRACE; break;
            case '[': type = LBRACKET; break;
            case ']': type = RBRACKET; break;
            case ',': type = COMMA; break;
            case ';': type = SEMICOLON; break;
            case ':':
                if (match('=')) { type = COLON_EQUAL; }
                else { type = COLON; }
                break; 
            case '+':
                if (match('=')) { type = PLUS_EQUAL; }
                else { type = PLUS; }
                break;
            case '-':
                if (match('=')) { type = MINUS_EQUAL; }
                else if (match('>')) { type = ARROW; }
                else { type = MINUS; }
                break; 
            case '*':
                if (match('=')) { type = STAR_EQUAL; }
                else { type = STAR; }
                break;
            case '/':
                if (match('/')) { seek('\n'); }
                else if (match('=')) { type = SLASH_EQUAL; }
                else { type = SLASH; }
                break;
            case '%':
                if (match('=')) { type = PERCENT_EQUAL; }
                else { type = PERCENT; }
                break;
            case '>':
                if (match('=')) { type = GREATER_EQUAL; }
                else { type = GREATER; }
                break;
            case '<':
                if (match('=')) { type = LESSER_EQUAL; }
                else { type = LESSER; }
                break;
            case '!':
                if (match('=')) { type = BANG_EQUAL; }
                else { type = BANG; }
                break;
            case '&':
                if (match('&')) { type = AND; }
                else { type = AMPERSAND; }
                break;
            case '|':
                if (match('|')) { type = OR; }
                else {
                    error("'|' is not a valid token. Did you mean '||'?", pos_start);
                }
                break;
            case '=':
                if (match('=')) { type = EQUAL_EQUAL; }
                else if (match('>')) { type = BOLD_ARROW; }
                else { type = EQUAL; }
                break;
            case '.':
                if (isDigit(peek())) {
                    advance();
                    while (isDigit(peek())) { advance(); }
                    type = FLOAT;
                } else {
                    error("'.' not part of a decimal literal", pos_start);
                }
                break;
            case ' ': case '\r': case '\t': break;
            case '\n': newLine(); break;
            case '\'': type = character(); break;
            case '"': type = string(); break;
            default:
                if (isDigit(c)) { type = number(); }
                else if (isAlpha(c)) { type = identifier(); }
                else {
                    auto msg = std::format("Unexpected character '{}'", c);
                    error(msg, pos_start);
                }
        }
        if (type) { addToken(*type); }
    }

    return tokens;
}
