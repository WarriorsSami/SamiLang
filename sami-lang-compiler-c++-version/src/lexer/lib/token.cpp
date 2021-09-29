//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <utility>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include "../include/token.hpp"

namespace samilang::lexer {
    using namespace std;

    inline Token::Token(
            pair<int64_t, int64_t> position,
            TokenType type,
            string  value
    ) : position(move(position)), type(type), value(move(value)) {}

    inline string Token::tokenTypeToStr() const {
        switch (this->type) {
            case TOK_INT:
                return "TOK_INT";
                
            case TOK_FLOAT:
                return "TOK_FLOAT";
                
            case TOK_STR:
                return "TOK_STR";
                
            case TOK_IDEN:
                return "TOK_IDEN";
                
            case TOK_INVK:
                return "TOK_INVK";
                
            case TOK_MODEL:
                return "TOK_MODEL";
                
            case TOK_FNTN:
                return "TOK_FNTN";
                
            case TOK_GRP:
                return "TOK_GRP";
                
            case TOK_LET:
                return "TOK_LET";
                
            case TOK_FLW:
                return "TOK_FLW";
                
            case TOK_GRW:
                return "TOK_GRW";
                
            case TOK_SELF:
                return "TOK_SELF";
                
            case TOK_VAR:
                return "TOK_VAR";
                
            case TOK_VAL:
                return "TOK_VAL";
                
            case TOK_CURR:
                return "TOK_CURR";
                
            case TOK_RETURN:
                return "TOK_RETURN";
                
            case TOK_GT:
                return "TOK_GT";
                
            case TOK_ST:
                return "TOK_ST";
                
            case TOK_IF:
                return "TOK_IF";
                
            case TOK_ELSE:
                return "TOK_ELSE";
                
            case TOK_FOR:
                return "TOK_FOR";
                
            case TOK_IN:
                return "TOK_IN";
                
            case TOK_WHILE:
                return "TOK_WHILE";
                
            case TOK_CONTINUE:
                return "TOK_CONTINUE";
                
            case TOK_BREAK:
                return "TOK_BREAK";
                
            case TOK_BARE:
                return "TOK_BARE";
                
            case TOK_TRUE:
                return "TOK_TRUE";
                
            case TOK_FALSE:
                return "TOK_FALSE";
                
            case TOK_ASSIGN:
                return "TOK_ASSIGN";
                
            case TOK_PLUS_ASSIGN:
                return "TOK_PLUS_ASSIGN";
                
            case TOK_MINUS_ASSIGN:
                return "TOK_MINUS_ASSIGN";
                
            case TOK_MUL_ASSIGN:
                return "TOK_MUL_ASSIGN";
                
            case TOK_DIV_ASSIGN:
                return "TOK_DIV_ASSIGN";
                
            case TOK_MOD_ASSIGN:
                return "TOK_MOD_ASSIGN";
                
            case TOK_PWR_ASSIGN:
                return "TOK_PWR_ASSIGN";
                
            case TOK_AND_ASSIGN:
                return "TOK_AND_ASSIGN";
                
            case TOK_OR_ASSIGN:
                return "TOK_OR_ASSIGN";
                
            case TOK_XOR_ASSIGN:
                return "TOK_XOR_ASSIGN";
                
            case TOK_SIMPLE_ARROW:
                return "TOK_SIMPLE_ARROW";
                
            case TOK_DOUBLE_ARROW:
                return "TOK_DOUBLE_ARROW";
                
            case TOK_COLON:
                return "TOK_COLON";
                
            case TOK_DOUBLE_COLON:
                return "TOK_DOUBLE_COLON";
                
            case TOK_SEMI_COLON:
                return "TOK_SEMI_COLON";
                
            case TOK_COMMA:
                return "TOK_COMMA";
                
            case TOK_DOT:
                return "TOK_DOT";
                
            case TOK_PLUS:
                return "TOK_PLUS";
                
            case TOK_MINUS:
                return "TOK_MINUS";
                
            case TOK_MUL:
                return "TOK_MUL";
                
            case TOK_DIV:
                return "TOK_DIV";
                
            case TOK_MOD:
                return "TOK_MOD";
                
            case TOK_PWR:
                return "TOK_PWR";
                
            case TOK_GREATER:
                return "TOK_GREATER";
                
            case TOK_LESS:
                return "TOK_LESS";
                
            case TOK_GREATER_EQ:
                return "TOK_GREATER_EQ";
                
            case TOK_LESS_EQ:
                return "TOK_LESS_EQ";
                
            case TOK_EQ:
                return "TOK_EQ";
                
            case TOK_NOT_EQ:
                return "TOK_NOT_EQ";
                
            case TOK_LAND:
                return "TOK_LAND";
                
            case TOK_LOR:
                return "TOK_LOR";
                
            case TOK_LNOT:
                return "TOK_LNOT";
                
            case TOK_AND:
                return "TOK_AND";
                
            case TOK_OR:
                return "TOK_OR";
                
            case TOK_XOR:
                return "TOK_XOR";
                
            case TOK_NOT:
                return "TOK_NOT";
                
            case TOK_SHL:
                return "TOK_SHL";
                
            case TOK_SHR:
                return "TOK_SHR";
                
            case TOK_LPARAN:
                return "TOK_LPARAN";
                
            case TOK_RPARAN:
                return "TOK_RPARAN";
                
            case TOK_LBRK:
                return "TOK_LBRK";
                
            case TOK_RBRK:
                return "TOK_RBRK";
                
            case TOK_LRBRK:
                return "TOK_LRBRK";
                
            case TOK_RRBRK:
                return "TOK_RBRK";
                
            case TOK_LINE_COMMENT:
                return "TOK_LINE_COMMENT";
                
            case TOK_LMLINE_COMMENT:
                return "TOK_LMLINE_COMMENT";
                
            case TOK_RMLINE_COMMENT:
                return "TOK_RMLINE_COMMENT";
                
            case TOK_INVALID:
                return "TOK_INVALID";
                
            case TOK_LAST:
                return "TOK_LAST";
                
            case TOK_KINT:
                return "TOK_KINT";
                
            case TOK_KBOOL:
                return "TOK_KBOOL";
                
            case TOK_KFLOAT:
                return "TOK_KFLOAT";
                
            case TOK_KSTR:
                return "TOK_KSTR";
                
            case TOK_SHL_ASSIGN:
                return "TOK_SHL_ASSIGN";
                
            case TOK_SHR_ASSIGN:
                return "TOK_SHR_ASSIGN";
                
            case TOK_SPC:
                return "TOK_SPC";
                
            case TOK_TAB:
                return "TOK_TAB";
                
            case TOK_NEWL:
                return "TOK_NEWL";
                
            case TOK_WHERE:
                return "TOK_WHERE";
                
            case TOK_CIN:
                return "TOK_CIN";
                
            case TOK_COUT:
                return "TOK_COUT";
                
            case TOK_INC:
                return "TOK_INC";
                
            case TOK_DEC:
                return "TOK_DEC";
                
        }
    }

    inline char *Token::tokenToStr() const {
        string token_type = tokenTypeToStr();
        char mask[] = "<type=`%s`, type_id=`%d`, value=`%s`, position=`%d[%d]`>";
        char *str = static_cast<char *>(calloc(token_type.size() + this->value.size() + strlen(mask) + 10,
                                               sizeof(char)));
        sprintf(str, mask,
                token_type.c_str(), this->type, this->value.c_str(), this->position.first, this->position.second);

        return str;
    }

    [[maybe_unused]] inline bool Token::isData() const {
        return (this->type >= TOK_INT && this->type <= TOK_IDEN) ||
               this->type == TOK_TRUE || this->type == TOK_FALSE;
    }

    [[maybe_unused]] inline bool Token::isAssignment() const {
        return this->type >= TOK_ASSIGN && this->type <= TOK_XOR_ASSIGN;
    }

    [[maybe_unused]] inline bool Token::isOperator() const {
        return this->type >= TOK_ASSIGN && this->type <= TOK_RRBRK;
    }

    inline bool Token::is(TokenType t) const {
        return this->type == t;
    }

    [[maybe_unused]] inline bool Token::isNot(TokenType t) const {
        return this->type != t;
    }

    template<typename... T>
    inline bool Token::isAny(TokenType t1, TokenType t2, T... targs) const {
        return is(t1) || isAny(t2, targs...);
    }
}