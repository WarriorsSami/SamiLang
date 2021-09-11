//
// Created by sami on 11.09.2021.
//

#include <string>
#include <memory>
#include "../include/driver.hpp"

namespace samilang {
    using namespace std;

    Driver::Driver(const string &file_name): Lex(make_unique<Lexer>(file_name)) {}

    void Driver::launch() const {
        Lex->test();
        /*LexerExceptions res = */Lex->tokenize();
        //handle(res);
        Lex->test();
    }
}
