//
// Created by sami on 08.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_TOKEN_HPP
#define SAMI_LANG_COMPILER_C___VERSION_TOKEN_HPP

#include <string>
#include <vector>

namespace samilang::lexer {
    using namespace std;

    // Token types
    enum TokenType {
        // data types
        TOK_INT,
        TOK_FLOAT,
        TOK_STR,
        TOK_BARE,

        // identifier
        TOK_IDEN,

        // keywords
        TOK_KINT,
        TOK_KBOOL,
        TOK_KFLOAT,
        TOK_KSTR,
        TOK_INVK,
        TOK_MODEL,
        TOK_FNTN,
        TOK_GRP,
        TOK_LET,
        TOK_FLW,
        TOK_GRW,
        TOK_SELF,
        TOK_VAR,
        TOK_VAL,
        TOK_CURR,
        TOK_RETURN,
        TOK_GT,
        TOK_ST,
        TOK_IF,
        TOK_ELSE,
        TOK_FOR,
        TOK_IN,
        TOK_WHILE,
        TOK_CONTINUE,
        TOK_BREAK,
        TOK_WHERE,
        TOK_TRUE,
        TOK_FALSE,

        // operators

        // assignment
        TOK_ASSIGN,
        TOK_PLUS_ASSIGN,
        TOK_MINUS_ASSIGN,
        TOK_MUL_ASSIGN,
        TOK_DIV_ASSIGN,
        TOK_MOD_ASSIGN,
        TOK_PWR_ASSIGN,
        TOK_SHL_ASSIGN,
        TOK_SHR_ASSIGN,
        TOK_AND_ASSIGN,
        TOK_OR_ASSIGN,
        TOK_XOR_ASSIGN,

        // separators
        TOK_SIMPLE_ARROW,
        TOK_DOUBLE_ARROW,
        TOK_COLON,
        TOK_DOUBLE_COLON,
        TOK_SEMI_COLON,
        TOK_COMMA,
        TOK_DOT,

        // arithmetic
        TOK_PLUS,
        TOK_MINUS,
        TOK_MUL,
        TOK_DIV,
        TOK_MOD,
        TOK_PWR,
        TOK_GREATER,
        TOK_LESS,
        TOK_GREATER_EQ,
        TOK_LESS_EQ,

        // logic
        TOK_EQ,
        TOK_NOT_EQ,
        TOK_LAND,
        TOK_LOR,
        TOK_LNOT,

        // bitwise
        TOK_AND,
        TOK_OR,
        TOK_XOR,
        TOK_NOT,
        TOK_SHL,
        TOK_SHR,

        // brackets
        TOK_LPARAN,
        TOK_RPARAN,
        TOK_LBRK,
        TOK_RBRK,
        TOK_LRBRK,
        TOK_RRBRK,
        TOK_LARR,
        TOK_RARR,

        // others
        TOK_CIN,
        TOK_COUT,
        TOK_LINE_COMMENT,
        TOK_LMLINE_COMMENT,
        TOK_RMLINE_COMMENT,
        TOK_SPC,
        TOK_TAB,
        TOK_NEWL,

        TOK_LAST,

        TOK_INVALID
    };

    // Token struct
    class Token {
    public:

        // class management
        explicit Token(pair<int64_t, int64_t> position, TokenType type, string  value);
        friend class Lexer;

        // fundamental functionality
        string tokenTypeToStr() const;
        char* tokenToStr() const;

        bool isData() const;
        bool isAssignment() const;
        bool isOperator() const;
        bool is(TokenType t) const;
        bool isNot(TokenType t) const;

        template<typename ...T>
        bool isAny(TokenType t1, TokenType t2, T... targs) const;

    private:
        pair<int64_t, int64_t> position;
        TokenType type;
        string value;
    };

    using toks = vector<Token>;
}

#endif //SAMI_LANG_COMPILER_C___VERSION_TOKEN_HPP
