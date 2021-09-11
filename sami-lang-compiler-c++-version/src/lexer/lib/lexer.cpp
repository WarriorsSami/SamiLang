//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include "../include/lexer.hpp"
#include "../../../src/utils/include/file_scanner.hpp"

namespace samilang::lexer {
    using namespace std;

    Lexer::Lexer(const string& file_name):
        Reader(make_unique<FileScanner>(file_name)),
        src(Reader->getString()) {}

    void Lexer::test() const {
        cout << src << "\n";
    }
}