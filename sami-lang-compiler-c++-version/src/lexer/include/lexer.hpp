//
// Created by sami on 08.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP
#define SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP

#include <memory>
#include <string>
#include "../../../src/utils/include/file_scanner.hpp"

namespace samilang::lexer {
    using namespace std;

    class Lexer {
    public:
        explicit Lexer(const string& file_name);
        void test() const;

    private:
        unique_ptr<FileScanner> Reader;
        string src;
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_LEXER_HPP
