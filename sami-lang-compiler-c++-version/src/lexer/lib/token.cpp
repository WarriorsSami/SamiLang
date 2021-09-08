//
// Created by sami on 08.09.2021.
//

#include <utility>
#include <string>
#include "../include/token.hpp"

// Getters for Token class
const std::pair<long, long> &samilang::lexer::Token::getPosition() const {
    return position;
}

const long &samilang::lexer::Token::getLine() const {
    return position.first;
}

const long &samilang::lexer::Token::getColumn() const {
    return position.second;
}

samilang::lexer::TokenType samilang::lexer::Token::getType() const {
    return type;
}

const std::string &samilang::lexer::Token::getValue() const {
    return value;
}


// Setters for Token class
void samilang::lexer::Token::setPosition(const std::pair<int64_t, int64_t> &position) {
    this->position = position;
}

void samilang::lexer::Token::setLine(const int64_t &line) {
    this->position.first = line;
}

void samilang::lexer::Token::setColumn(const int64_t &column) {
    this->position.second = column;
}

void samilang::lexer::Token::setType(samilang::lexer::TokenType type) {
    this->type = type;
}

void samilang::lexer::Token::setValue(const std::string &value) {
    this->value = value;
}

samilang::lexer::Token::Token(
        std::pair<int64_t, int64_t> position,
        samilang::lexer::TokenType type,
        std::string value
): position(std::move(position)), type(type), value(std::move(value)) {}

std::string samilang::lexer::Token::tokenTypeToStr() {
    switch(this->type) {

        case TOK_INT: return "TOK_INT";
            break;
        case TOK_BOOL: return "TOK_BOOL";
            break;
        case TOK_FLOAT: return "TOK_FLOAT";
            break;
        case TOK_STR: return "TOK_STR";
            break;
        case TOK_IDEN: return "TOK_IDEN";
            break;
        case TOK_INVK: return "TOK_INVK";
            break;
        case TOK_MODEL: return "TOK_MODEL";
            break;
        case TOK_FNTN: return "TOK_FNTN";
            break;
        case TOK_GRP: return "TOK_GRP";
            break;
        case TOK_LET: return "TOK_LET";
            break;
        case TOK_FLW: return "TOK_FLW";
            break;
        case TOK_GRW: return "TOK_GRW";
            break;
        case TOK_SELF: return "TOK_SELF";
            break;
        case TOK_VAR: return "TOK_VAR";
            break;
        case TOK_VAL: return "TOK_VAL";
            break;
        case TOK_CURR: return "TOK_CURR";
            break;
        case TOK_RETURN: return "TOK_RETURN";
            break;
        case TOK_GT: return "TOK_GT";
            break;
        case TOK_ST: return "TOK_ST";
            break;
        case TOK_IF: return "TOK_IF";
            break;
        case TOK_ELSE: return "TOK_ELSE";
            break;
        case TOK_FOR: return "TOK_FOR";
            break;
        case TOK_IN: return "TOK_IN";
            break;
        case TOK_WHILE: return "TOK_WHILE";
            break;
        case TOK_CONTINUE: return "TOK_CONTINUE";
            break;
        case TOK_BREAK: return "TOK_BREAK";
            break;
        case TOK_BARE: return "TOK_BARE";
            break;
        case TOK_TRUE: return "TOK_TRUE";
            break;
        case TOK_FALSE: return "TOK_FALSE";
            break;
        case TOK_ASSIGN: return "TOK_ASSIGN";
            break;
        case TOK_PLUS_ASSIGN: return "TOK_PLUS_ASSIGN";
            break;
        case TOK_MINUS_ASSIGN: return "TOK_MINUS_ASSIGN";
            break;
        case TOK_MUL_ASSIGN: return "TOK_MUL_ASSIGN";
            break;
        case TOK_DIV_ASSIGN: return "TOK_DIV_ASSIGN";
            break;
        case TOK_MOD_ASSIGN: return "TOK_MOD_ASSIGN";
            break;
        case TOK_PWR_ASSIGN: return "TOK_PWR_ASSIGN";
            break;
        case TOK_AND_ASSIGN: return "TOK_AND_ASSIGN";
            break;
        case TOK_OR_ASSIGN: return "TOK_OR_ASSIGN";
            break;
        case TOK_XOR_ASSIGN: return "TOK_XOR_ASSIGN";
            break;
        case TOK_SIMPLE_ARROW: return "TOK_SIMPLE_ARROW";
            break;
        case TOK_DOUBLE_ARROW: return "TOK_DOUBLE_ARROW";
            break;
        case TOK_COLON: return "TOK_COLON";
            break;
        case TOK_DOUBLE_COLON: return "TOK_DOUBLE_COLON";
            break;
        case TOK_SEMI_COLON: return "TOK_SEMI_COLON";
            break;
        case TOK_COMMA: return "TOK_COMMA";
            break;
        case TOK_PIPE: return "TOK_PIPE";
            break;
        case TOK_DOT: return "TOK_DOT";
            break;
        case TOK_PLUS: return "TOK_PLUS";
            break;
        case TOK_MINUS: return "TOK_MINUS";
            break;
        case TOK_MUL: return "TOK_MUL";
            break;
        case TOK_DIV: return "TOK_DIV";
            break;
        case TOK_MOD: return "TOK_MOD";
            break;
        case TOK_PWR: return "TOK_PWR";
            break;
        case TOK_GREATER: return "TOK_GREATER";
            break;
        case TOK_LESS: return "TOK_LESS";
            break;
        case TOK_GREATER_EQ: return "TOK_GREATER_EQ";
            break;
        case TOK_LESS_EQ: return "TOK_LESS_EQ";
            break;
        case TOK_EQ: return "TOK_EQ";
            break;
        case TOK_NOT_EQ: return "TOK_NOT_EQ";
            break;
        case TOK_LAND: return "TOK_LAND";
            break;
        case TOK_LOR: return "TOK_LOR";
            break;
        case TOK_LNOT: return "TOK_LNOT";
            break;
        case TOK_AND: return "TOK_AND";
            break;
        case TOK_OR: return "TOK_OR";
            break;
        case TOK_XOR: return "TOK_XOR";
            break;
        case TOK_NOT: return "TOK_NOT";
            break;
        case TOK_SHL: return "TOK_SHL";
            break;
        case TOK_SHR: return "TOK_SHR";
            break;
        case TOK_LPARAN: return "TOK_LPARAN";
            break;
        case TOK_RPARAN: return "TOK_RPARAN";
            break;
        case TOK_LBRK: return "TOK_LBRK";
            break;
        case TOK_RBRK: return "TOK_RBRK";
            break;
        case TOK_LRBRK: return "TOK_LRBRK";
            break;
        case TOK_RRBRK: return "TOK_RBRK";
            break;
        case TOK_LARR: return "TOK_LARR";
            break;
        case TOK_RARR: return "TOK_RARR";
            break;
        case TOK_LTILDE: return "TOK_LTILDE";
            break;
        case TOK_RTILDE: return "TOK_RTILDE";
            break;
        case TOK_AMPERSAND: return "TOK_AMPERSAND";
            break;
        case TOK_LINE_COMMENT: return "TOK_LINE_COMMENT";
            break;
        case TOK_LMLINE_COMMENT: return "TOK_LMLINE_COMMENT";
            break;
        case TOK_RMLINE_COMMENT: return "TOK_RMLINE_COMMENT";
            break;
        case TOK_INVALID: return "TOK_INVALID";
            break;
        case TOK_LAST: return "TOK_LAST";
            break;
    }

    return "Not a valid token";
}