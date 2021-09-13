//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include "../include/lexer.hpp"
//#include "../include/token.hpp"
#include "token.cpp"

#define CURR(line) (line[i])
#define NEXT(line, i) (i + 1 < len ? line[i + 1] : 0)
#define PREV(line) (line.size() > 0 && i - 1 >= 0 ? line[i - 1] : 0)


namespace samilang::lexer {
    using namespace std;

    vector<string> TokenValues = {
            "INT",
            "FLOAT",
            "STR",
            "bare",

            "IDEN",

            "int",
            "bool",
            "float",
            "str",
            "invk",
            "model",
            "fntn",
            "group",
            "let",
            "follow",
            "grow",
            "self",
            "var",
            "val",
            "curr",
            "return",
            "gt",
            "st",
            "if",
            "else",
            "for",
            "in",
            "while",
            "continue",
            "break",
            "where",
            "true",
            "false",

            "=",
            "+=",
            "-=",
            "*=",
            "/=",
            "%=",
            "**=",
            "<<=",
            ">>=",
            "&=",
            "|=",
            "^=",

            "->",
            "=>",
            ":",
            "::",
            ";",
            ",",
            ".",

            "+",
            "-",
            "*",
            "/",
            "%",
            "**",
            ">",
            "<",
            ">=",
            "<=",

            "==",
            "!=",
            "&&",
            "||",
            "!",

            "&",
            "|",
            "^",
            "~",
            "<<",
            ">>",

            "(",
            ")",
            "{",
            "}",
            "[",
            "]",
            "<",
            ">",

            "::<",
            "::>",
            "@@",
            "/@",
            "@/",
            "SPC",
            "TAB",
            "NEWL",

            "<EOF>"
    };

    Lexer::Lexer(const string& file_name):
            Reader(make_unique<FileScanner>(file_name)),
            code(Reader->readFile()),
            comment_block_remainder(0) {
        tie(src, srcList) = code;
    }

    void Lexer::test() const {
        cout << tokenList.size() << "\n";
        for (const auto& item: tokenList)
            cout << item.tokenToStr() << "\n";
    }

    LexerExceptions Lexer::tokenize() {
        // tokenize the input string src
        for (int i = 0; i < srcList.size(); ++i) {
            const string& line = srcList[i];
            LexerExceptions res = tokenizeLine(line, static_cast<int>(line.size()), i + 1);
            if (res != E_OK) return res;
        }

        if (this->comment_block_remainder) return E_LEX_FAIL;
        return E_OK;
    }

    LexerExceptions Lexer::tokenizeLine(const string &line, const int &len, const int& num_line) {
        int i = 0;
        LexerExceptions res = E_OK;
        static int comment_block = 0;

        while (i < len) {
            // skip space
            if (isspace(CURR(line))) {
                ++i;
                continue;
            }

            // multiline comment begin
            if (CURR(line) == '/' && NEXT(line, i) == '@') {
                i += 2, ++comment_block;
                continue;
            }

            // multiline comment end
            if (CURR(line) == '@' && NEXT(line, i) == '/') {
                // exit with `lex error` if there is no comment_block opened
                if (!comment_block) {
                    res = E_LEX_FAIL;
                    break;
                }
                i += 2, --comment_block;
                continue;
            }

            // in a comment block at the moment
            if (comment_block) {
                ++i;
                continue;
            }

            // single line comment (just exit)
            if (CURR(line) == '@' && NEXT(line, i) == '@') {
                break;
            }

            int tmp_col = i + 1;

            // string encountered (identifier or keyword)
            if (isalpha(CURR(line))) {
                const string& str = get_name(line, len, i);
                TokenType kw_or_id = tag_name(str);
                tokenList.emplace_back(make_pair(num_line, tmp_col), kw_or_id, str);
                continue;
            }

            // literal string encountered
            if (CURR(line) == '\"' || CURR(line) == '\'') {
                // TODO
            }

            ++i;
        }

        this->comment_block_remainder = comment_block;
        return res;
    }

    string Lexer::get_name(const string &line, const int &len, int &i) {
        string buffer;
        while (isalpha(CURR(line)) && i < len) {
            buffer.push_back(CURR(line)), ++i;
        }
        return buffer;
    }

    TokenType Lexer::tag_name(const string &str) {
        if (str == TokenValues[TOK_KINT])
            return TOK_KINT;
        else if (str == TokenValues[TOK_KBOOL])
            return TOK_KBOOL;
        else if (str == TokenValues[TOK_BARE])
            return TOK_BARE;
        else if (str == TokenValues[TOK_KFLOAT])
            return TOK_KFLOAT;
        else if (str == TokenValues[TOK_KSTR])
            return TOK_KSTR;
        else if (str == TokenValues[TOK_INVK])
            return TOK_INVK;
        else if (str == TokenValues[TOK_MODEL])
            return TOK_MODEL;
        else if (str == TokenValues[TOK_FNTN])
            return TOK_FNTN;
        else if (str == TokenValues[TOK_GRP])
            return TOK_GRP;
        else if (str == TokenValues[TOK_LET])
            return TOK_LET;
        else if (str == TokenValues[TOK_FLW])
            return TOK_FLW;
        else if (str == TokenValues[TOK_GRW])
            return TOK_GRW;
        else if (str == TokenValues[TOK_SELF])
            return TOK_SELF;
        else if (str == TokenValues[TOK_VAR])
            return TOK_VAR;
        else if (str == TokenValues[TOK_VAL])
            return TOK_VAL;
        else if (str == TokenValues[TOK_CURR])
            return TOK_CURR;
        else if (str == TokenValues[TOK_RETURN])
            return TOK_RETURN;
        else if (str == TokenValues[TOK_GT])
            return TOK_GT;
        else if (str == TokenValues[TOK_ST])
            return TOK_ST;
        else if (str == TokenValues[TOK_IF])
            return TOK_IF;
        else if (str == TokenValues[TOK_ELSE])
            return TOK_ELSE;
        else if (str == TokenValues[TOK_FOR])
            return TOK_FOR;
        else if (str == TokenValues[TOK_IN])
            return TOK_IN;
        else if (str == TokenValues[TOK_WHILE])
            return TOK_WHILE;
        else if (str == TokenValues[TOK_CONTINUE])
            return TOK_CONTINUE;
        else if (str == TokenValues[TOK_BREAK])
            return TOK_BREAK;
        else if (str == TokenValues[TOK_WHERE])
            return TOK_WHERE;
        else if (str == TokenValues[TOK_TRUE])
            return TOK_TRUE;
        else if (str == TokenValues[TOK_FALSE])
            return TOK_FALSE;

        return TOK_IDEN;
    }
}