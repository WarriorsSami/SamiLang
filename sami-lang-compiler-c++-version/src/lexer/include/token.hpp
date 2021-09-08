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
        TOK_BOOL,
        TOK_FLOAT,
        TOK_STR,

        // identifier
        TOK_IDEN,

        // keywords
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
        TOK_BARE,
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
        TOK_PIPE,
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
        TOK_LTILDE,
        TOK_RTILDE,

        // others
        TOK_AMPERSAND,
        TOK_LINE_COMMENT,
        TOK_LMLINE_COMMENT,
        TOK_RMLINE_COMMENT,

        TOK_INVALID,

        TOK_LAST
    };

    // values for tokens
    extern vector<string_view> TokenStrings(TOK_LAST);

    // Token struct
    class Token {
    public:

        // class management
        Token(pair<int64_t, int64_t> position, TokenType type, string_view value);

        const pair<int64_t, int64_t> &getPosition() const;

        const int64_t &getLine() const;

        const int64_t &getColumn() const;

        TokenType getType() const;

        const string_view &getValue() const;

        void setPosition(const pair<int64_t, int64_t> &position);

        void setLine(const int64_t &line);

        void setColumn(const int64_t& column);

        void setType(TokenType type);

        void setValue(const string_view &value);


        // fundamental functionality
        string_view tokenTypeToStr();

    private:
        pair<int64_t, int64_t> position;
        TokenType type;
        string_view value;
    };

    using toks = vector<Token>;
}

#endif //SAMI_LANG_COMPILER_C___VERSION_TOKEN_HPP
