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
        LexerExceptions tokenize();

    private:
        unique_ptr<FileScanner> Reader;
        string src;
        vector<string> srcList;
        p_read code;
        toks tokenList;
        int comment_block_remainder;

        LexerExceptions tokenizeLine(const string& line, const int& len, const int& num_line);

        // helper methods
        static string get_name(const string& line, const int& len, int& i);
        static TokenType tag_name(const string& str);
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP
