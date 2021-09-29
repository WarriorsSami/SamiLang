//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "../include/lexer.hpp"
#include "token.cpp"

#define CURR(line) (line[i])
#define NEXT(line, i) (i + 1 < len ? line[i + 1] : 0)
#define PREV(line) (!line.empty() && i - 1 >= 0 ? line[i - 1] : 0)
#define SET_OP_BREAK(token) \
        op_type = token;    \
        break

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
            "++",
            "--",
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

    CustomException Lexer::tokenize() {
        // tokenize the input string src
        for (int i = 0; i < srcList.size(); ++i) {
            const string& line = srcList[i];
            CustomException res = tokenizeLine(line, static_cast<int>(line.size()), i + 1);
            if (res.err_code != E_OK) return res;
        }

        if (this->comment_block_remainder) return {E_LEX_FAIL, (int)srcList.size(),
                                                   string(to_string(this->comment_block_remainder))
                                                   + " comment blocks not closed found!"};
        return {E_OK, -1, "Everything is OK!"};
    }

    CustomException Lexer::tokenizeLine(const string &line, const int &len, const int& num_line) {
        int i = 0;
        CustomException res = {E_OK, -1, "Everything is OK!"};
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
                    res = {E_LEX_FAIL, num_line, "No matching `init comment block character` found "
                                          "for the current `exit comment block character` at column "
                                          + to_string(i + 1) + "!"};
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
                auto [str, err] = get_name(line, len, i, num_line);
                if (err.err_code != E_OK) {
                    res = err;
                    break;
                }
                TokenType kw_or_id = tag_name(str);
                tokenList.emplace_back(make_pair(num_line, tmp_col), kw_or_id, str);
                continue;
            }

            // literal string encountered
            if (CURR(line) == '\"' || CURR(line) == '\'') {
                auto [str, err] = get_string(line, len, i, num_line);
                if (err.err_code != E_OK) {
                    res = err;
                    break;
                }
                tokenList.emplace_back(make_pair(num_line, tmp_col), TOK_STR, str);
                continue;
            }

            // literal number encountered
            if (isdigit(CURR(line))) {
                auto [nr_type, nr, err] = get_number(line, len, i, num_line);
                if (err.err_code != E_OK) {
                    res = err;
                    break;
                }
                tokenList.emplace_back(make_pair(num_line, tmp_col), nr_type, nr);
                continue;
            }

            // operator encountered
            auto [op_type, err] = get_operator(line, len, i, num_line);
            if (op_type < 0) {
                res = err;
                break;
            }
            tokenList.emplace_back(make_pair(num_line, tmp_col), op_type, TokenValues[op_type]);
        }

        this->comment_block_remainder = comment_block;
        return res;
    }

    str_err Lexer::get_name(const string &line, const int &len, int &i, const int& num_line) {
        string buffer;
        while ((isalnum(CURR(line)) || CURR(line) == '_') && i < len) {
            buffer.push_back(CURR(line)), ++i;
        }
        if (buffer.empty())
            return make_pair(buffer, CustomException(E_PARSE_FAIL, num_line,
                                                     "Empty identifier/keyword found at column "
                                                     + to_string(i + 1) + "!"));
        return make_pair(buffer, CustomException(E_OK, -1, "Everything is OK!"));
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

    str_err Lexer::get_string(const string &line, const int &len, int &i, const int& num_line) {
        string buffer;
        const char quote_type = CURR(line);
        // skip beginning quote
        ++i;
        while ((CURR(line) != quote_type || PREV(line) == '\\') && i < len) {
            buffer.push_back(CURR(line)), ++i;
        }
        if (CURR(line) != quote_type)
            return make_pair(buffer,
                             CustomException(E_LEX_FAIL, num_line, "No ending quote found for string "
                                                                   "literal at column " + to_string(i + 1) + "!"));
        if (buffer.empty())
            return make_pair(buffer, CustomException(E_PARSE_FAIL, num_line, "Empty string literal found a"
                                                                             "t column " + to_string(i + 1) + "!"));
        // skip ending quote
        ++i;
        remove_back_slash(buffer);
        return make_pair(buffer, CustomException(E_OK, -1, "Everything is OK!"));
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

    nr_err Lexer::get_number(const string &line, const int &len, int &i, const int& num_line) {
        string buffer;
        TokenType num_type = TOK_INT;
        bool read_base = false;
        int starting_index = i,
            base = 10,
            dot_encountered = -1;

        while (i < len) {
            const char curr = CURR(line),
                       next = NEXT(line, i);

            switch(curr) {
            case 'x': case 'X': {
                if (read_base) {
                    base = 16;
                    read_base = false;
                    break;
                }
                goto fail;
            }
            case 'f': case 'F':
            case 'e': case 'E':
            case 'd': case 'D':
            case 'c': case 'C':
            case 'b': case 'B': {
                if (read_base) {
                    if (curr == 'b' || curr == 'B') {
                        base = 2;
                        read_base = false;
                        break;
                    } else {
                        goto fail;
                    }
                }
            }
            case 'a': case 'A': {
                if (base == 16) break;
                goto fail;
            }
            case '9': case '8': {
                if (base > 8) break;
                goto fail;
            }
            case '7': case '6':
            case '5': case '4':
            case '3': case '2': {
                if (base > 2) break;
                goto fail;
            }
            case '1': {
                read_base = false;
                break;
            }
            case '0': {
                if (i == starting_index) {
                    base = 8;
                    read_base = true;
                    break;
                }
                read_base = false;
                break;
            }
            case '.': {
                /// dot encountered when base is different than 10
                if (!read_base && base != 10) {
                    return make_tuple(num_type, buffer,
                                      CustomException(E_PARSE_FAIL, num_line,
                                                      "Dot encountered when base is different than 10 ("
                                                      + to_string(base) + ") at column " + to_string(i + 1) + "!"));
                /// float number (may be)
                } else if (dot_encountered == -1) {
                    if ('0' <= next && next <= '9') {
                        dot_encountered = i;
                        num_type = TOK_FLOAT;
                    } else {
                        return make_tuple(num_type, buffer,
                                          CustomException(E_OK, -1, "Everything is OK!"));
                    }
                /// dot encountered multiple times when base is 10
                } else {
                    return make_tuple(num_type, buffer,
                                      CustomException(E_PARSE_FAIL, num_line,
                                                      "Dot encountered multiple times when base is 10: "
                                                      "now at column " + to_string(i + 1) +
                                                      " and first at column "+ to_string(dot_encountered) + "!"));
                }
                read_base = false;
                base = 10;
                break;
            }
            default:
                fail: {
                    if (isalnum(curr)) {
                        return make_tuple(num_type, buffer,
                                          CustomException(E_PARSE_FAIL, num_line,
                                                          string("Invalid character encountered "
                                                                 "in numeric literal when base is (")
                                                                 + to_string(base) + "): " + curr +
                                                                 " at column " + to_string(i + 1) + "!"));
                    } else {
                        return make_tuple(num_type, buffer,
                                          CustomException(E_OK, -1, "Everything is OK!"));
                    }
                }
            }

            buffer.push_back(curr), ++i;
        }
        if (buffer.empty())
            return make_tuple(num_type, buffer,
                              CustomException(E_PARSE_FAIL, num_line,
                                              "Empty numeric literal found at column " + to_string(i + 1) + "!"));
        return make_tuple(num_type, buffer,
                          CustomException(E_OK, -1, "Everything is OK!"));
    }

    // TODO
    op_err Lexer::get_operator(const string &line, const int &len, int &i, const int& num_line) {
        int op_type = -1;
        CustomException err = {E_OK, -1, "Everything is OK!"};
        switch(CURR(line)) {
            case '+': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_PLUS_ASSIGN);
                    }
                    if (NEXT(line, i) == '+') {
                        ++i;
                        SET_OP_BREAK(TOK_INC);
                    }
                }
                SET_OP_BREAK(TOK_PLUS);
            }
            case '-': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_MINUS_ASSIGN);
                    }
                    if (NEXT(line, i) == '-') {
                        ++i;
                        SET_OP_BREAK(TOK_DEC);
                    }
                    if (NEXT(line, i) == '>') {
                        ++i;
                        SET_OP_BREAK(TOK_SIMPLE_ARROW);
                    }
                }
                SET_OP_BREAK(TOK_MINUS);
            }
            case '*': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_MUL_ASSIGN);
                    }
                    if (NEXT(line, i) == '*') {
                        ++i;
                        if (i < len - 1) {
                            if (NEXT(line, i) == '=') {
                                ++i;
                                SET_OP_BREAK(TOK_PWR_ASSIGN);
                            }
                        }
                        SET_OP_BREAK(TOK_PWR);
                    }
                }
                SET_OP_BREAK(TOK_MUL);
            }
            case '/': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_DIV_ASSIGN);
                    }
                }
                SET_OP_BREAK(TOK_DIV);
            }
            case '%': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_MOD_ASSIGN);
                    }
                }
                SET_OP_BREAK(TOK_MOD);
            }
            case '&': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_AND_ASSIGN);
                    }
                    if (NEXT(line, i) == '&') {
                        ++i;
                        SET_OP_BREAK(TOK_LAND);
                    }
                }
                SET_OP_BREAK(TOK_AND);
            }
            case '|': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_OR_ASSIGN);
                    }
                    if (NEXT(line, i) == '|') {
                        ++i;
                        SET_OP_BREAK(TOK_LOR);
                    }
                }
                SET_OP_BREAK(TOK_OR);
            }
            case '^': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_XOR_ASSIGN);
                    }
                }
                SET_OP_BREAK(TOK_XOR);
            }
            case '!': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_NOT_EQ);
                    }
                }
                SET_OP_BREAK(TOK_LNOT);
            }
            case '<': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_LESS_EQ);
                    }
                    if (NEXT(line, i) == '<') {
                        ++i;
                        if (i < len - 1) {
                            if (NEXT(line, i) == '=') {
                                ++i;
                                SET_OP_BREAK(TOK_SHL_ASSIGN);
                            }
                        }
                        SET_OP_BREAK(TOK_SHL);
                    }
                }
                SET_OP_BREAK(TOK_LESS);
            }
            case '>': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_GREATER_EQ);
                    }
                    if (NEXT(line, i) == '>') {
                        ++i;
                        if (i < len - 1) {
                            if (NEXT(line, i) == '=') {
                                ++i;
                                SET_OP_BREAK(TOK_SHR_ASSIGN);
                            }
                        }
                        SET_OP_BREAK(TOK_SHR);
                    }
                }
                SET_OP_BREAK(TOK_GREATER);
            }
            case '=': {
                if (i < len - 1) {
                    if (NEXT(line, i) == '=') {
                        ++i;
                        SET_OP_BREAK(TOK_EQ);
                    }
                    if (NEXT(line, i) == '>') {
                        ++i;
                        SET_OP_BREAK(TOK_DOUBLE_ARROW);
                    }
                }
                SET_OP_BREAK(TOK_ASSIGN);
            }
            case ':': {
                if (i < len - 1) {
                    if (NEXT(line, i) == ':') {
                        ++i;
                        if (i < len - 1) {
                            if (NEXT(line, i) == '>') {
                                ++i;
                                SET_OP_BREAK(TOK_COUT);
                            }
                            if (NEXT(line, i) == '<') {
                                ++i;
                                SET_OP_BREAK(TOK_CIN);
                            }
                        }
                        SET_OP_BREAK(TOK_DOUBLE_COLON);
                    }
                }
                SET_OP_BREAK(TOK_COLON);
            }
            case '~': {
                SET_OP_BREAK(TOK_NOT);
            }
            case ';': {
                SET_OP_BREAK(TOK_SEMI_COLON);
            }
            case ',': {
                SET_OP_BREAK(TOK_COMMA);
            }
            case '.': {
                SET_OP_BREAK(TOK_DOT);
            }
            case '(': {
                SET_OP_BREAK(TOK_LPARAN);
            }
            case ')': {
                SET_OP_BREAK(TOK_RPARAN);
            }
            case '[': {
                SET_OP_BREAK(TOK_LRBRK);
            }
            case ']': {
                SET_OP_BREAK(TOK_RRBRK);
            }
            case '{': {
                SET_OP_BREAK(TOK_LBRK);
            }
            case '}': {
                SET_OP_BREAK(TOK_RBRK);
            }
            case ' ': {
                SET_OP_BREAK(TOK_SPC);
            }
            case '\t': {
                SET_OP_BREAK(TOK_TAB);
            }
            case '\n': {
                SET_OP_BREAK(TOK_NEWL);
            }
            default: {
                op_type = -1;
                err = {E_LEX_FAIL, num_line, "Invalid operator found at column " + to_string(i) + "!"};
            }
        }

        ++i;
        return make_pair(static_cast<TokenType>(op_type), err);
    }
}