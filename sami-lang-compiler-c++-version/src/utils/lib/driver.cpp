//
// Created by sami on 11.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include "../include/driver.hpp"

namespace samilang {
    using namespace std;

    Driver::Driver(const string &file_name): Lex(make_unique<Lexer>(file_name)) {}

    void Driver::launch() const {
        LexerExceptions res = Lex->tokenize();
        handle(res);
        Lex->test();
    }

    void Driver::handle(LexerExceptions err) {
        switch(err) {
            case E_OK: {
                cout << "Lexical analysis has been completed successfully!\n";
            }
                break;
            case E_LEX_FAIL: {
                cout << "Lexical ERROR encountered!\n";
                exit(1);
            }
                break;
            case E_PARSE_FAIL: {
                cout << "Parsing ERROR encountered!\n";
                exit(1);
            }
                break;
        }
    }
}
