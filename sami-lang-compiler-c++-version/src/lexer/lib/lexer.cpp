//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include "../include/lexer.hpp"
//#include "../include/token.hpp"
#include "token.cpp"

#define CURR(line) (line[i])
#define NEXT(line, i) (i + 1 < len ? line[i + 1] : 0)
#define PREV(line) (!line.empty() && i - 1 >= 0 ? line[i - 1] : 0)


namespace samilang::lexer {
    using namespace std;

    vector<string> TokenValues = {
            "INT",
            "FLOAT",
            "STR",

            "IDEN",

            "int",
            "bool",
            "float",
            "str",
            "bare",
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
            if (isalpha(CURR(line)) || CURR(line) == '_') {
                const string& str = get_name(line, len, i);
                TokenType kw_or_id = tag_name(str);
                tokenList.emplace_back(make_pair(num_line, tmp_col), kw_or_id, str);
                continue;
            }

            // literal string encountered
            if (CURR(line) == '\"' || CURR(line) == '\'') {
                str_err str = get_string(line, len, i);
                if (str.second != E_OK) {
                    res = str.second;
                    break;
                }
                tokenList.emplace_back(make_pair(num_line, tmp_col), TOK_STR, str.first);
                continue;
            }

            ++i;
        }

        this->comment_block_remainder = comment_block;
        return res;
    }

    string Lexer::get_name(const string &line, const int &len, int &i) {
        string buffer;
        while ((isalnum(CURR(line)) || CURR(line) == '_') && i < len) {
            buffer.push_back(CURR(line)), ++i;
        }
        return buffer;
    }

    TokenType Lexer::tag_name(const string &str) {
        auto is_keyword = [str](const string &item) {
            return str == item;
        };
        auto first = find(begin(TokenValues), end(TokenValues), "int"),
             last = find(begin(TokenValues), end(TokenValues), "=");

        auto key = find_if(first, last, is_keyword);
        if (key == last) return TOK_IDEN;
        else return static_cast<TokenType>(distance(begin(TokenValues), key));
    }

    str_err Lexer::get_string(const string &line, const int &len, int &i) {
        string buffer;
        const char quote_type = CURR(line);
        // skip beginning quote
        ++i;
        while ((CURR(line) != quote_type || PREV(line) == '\\') && i < len) {
            buffer.push_back(CURR(line)), ++i;
        }
        if (CURR(line) != quote_type)
            return make_pair(buffer, E_LEX_FAIL);
        // skip ending quote
        ++i;
        //remove_back_slash(buffer);
        return make_pair(buffer, E_OK);
    }

    void Lexer::remove_back_slash(string &str) {
        auto last = end(str);
        vector<char> base = {'a', 'b', 'f', 'n', 'r', 't', 'v'},
                     esc  = {'\a', '\b', '\f', '\n', '\r', '\t', '\v'};
        for (auto it = begin(str); it != last; ++it) {
            if (*it == '\\') {
                it = str.erase(it);
                auto val = find(begin(base), end(base), *it);
                *it = esc[distance(begin(base), val)];
            }
        }
    }
}