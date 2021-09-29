//
// Created by sami on 08.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP
#define SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP

#include <memory>
#include <string>
#include <vector>
#include "../../../src/utils/include/file_scanner.hpp"
#include "../../utils/include/exceptions.hpp"
#include "token.hpp"

namespace samilang::lexer {
    using namespace std;

    class Lexer {
    public:
        explicit Lexer(const string& file_name);
        void test() const;
        CustomException tokenize();

    private:
        unique_ptr<FileScanner> Reader;
        string src;
        vector<string> srcList;
        p_read code;
        toks tokenList;
        int comment_block_remainder;

        CustomException tokenizeLine(const string& line, const int& len, const int& num_line);

        // helper methods
        static str_err get_name(const string &line, const int &len, int &i, const int& num_line);
        static TokenType tag_name(const string& str);
        static str_err get_string(const string& line, const int& len, int& i, const int& num_line);
        static void remove_back_slash(string& str);
        static nr_err get_number(const string& line, const int& len, int& i, const int& num_line);
        static op_err get_operator(const string& line, const int& len, int& i, const int& num_line);
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP
