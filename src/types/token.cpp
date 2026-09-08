
#include <string_view>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "token.hpp"

constexpr std::string_view stringifyTokenType(TokenType t) {
    using enum TokenType;
    switch (t) {
        case INTEGER:       return "INTEGER";
        case FLOAT:         return "FLOAT";
        case TRUE:          return "TRUE";
        case FALSE:         return "FALSE";
        case STRING:        return "STRING";
        case CHAR:          return "CHAR";
        case IDENTIFIER:    return "IDENTIFIER";
        case LPAREN:        return "LPAREN";
        case RPAREN:        return "RPAREN";
        case LBRACE:        return "LBRACE";
        case RBRACE:        return "RBRACE";
        case COMMA:         return "COMMA";
        case SEMICOLON:     return "SEMICOLON";
        case COLON:         return "COLON";
        case ARROW:         return "ARROW";
        case PLUS:          return "PLUS";
        case MINUS:         return "MINUS";
        case STAR:          return "STAR";
        case SLASH:         return "SLASH";
        case PERCENT:       return "PERCENT";
        case GREATER:       return "GREATER";
        case LESSER:        return "LESSER";
        case EQUAL_EQUAL:   return "EQUAL_EQUAL";
        case BANG_EQUAL:    return "BANG_EQUAL";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESSER_EQUAL:  return "LESSER_EQUAL";
        case BANG:          return "BANG";
        case AND:           return "AND";
        case OR:            return "OR";
        case EQUAL:         return "EQUAL";
        case COLON_EQUAL:   return "COLON_EQUAL";
        case PLUS_EQUAL:    return "PLUS_EQUAL";
        case MINUS_EQUAL:   return "MINUS_EQUAL";
        case STAR_EQUAL:    return "STAR_EQUAL";
        case SLASH_EQUAL:   return "SLASH_EQUAL";
        case PERCENT_EQUAL: return "PERCENT_EQUAL";
        case FUNCTION:      return "FUNCTION";
        case RETURN:        return "RETURN";
        case FOR:           return "FOR";
        case WHILE:         return "WHILE";
        case LOOP:          return "LOOP";
        case SWITCH:        return "SWITCH";
        case BOLD_ARROW:    return "BOLD_ARROW";
        case BREAK:         return "BREAK";
        case CONTINUE:      return "CONTINUE";
        case IF:            return "IF";
        case ELSE:          return "ELSE";
        case AMPERSAND:     return "AMPERSAND";
        case LBRACKET:      return "LBRACKET";
        case RBRACKET:      return "RBRACKET";
        case BUILTIN_READ:  return "BUILTIN_READ";
        case BUILTIN_WRITE: return "BUILTIN_WRITE"; 
    }
}

std::string tokensToJsonString(std::vector<Token>&tokens, int indent) {
    json arr = json::array();
    for (const auto& t : tokens) {
        arr.push_back({
            {"lexeme",  t.lexeme},
            {"type",    stringifyTokenType(t.type)},
            {"line",    t.line},
            {"col",     t.col}
        }); 
    }
    return arr.dump(indent);
}
