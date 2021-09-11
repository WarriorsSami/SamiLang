//
// Created by sami on 08.09.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include "../include/lexer.hpp"

#define CURR(line) (line[i])
#define NEXT(line) (i + 1 < len ? line[i + 1] : 0)
#define PREV(line) (line.size() > 0 && i - 1 >= 0 ? line[i - 1] : 0)

#define EMPTY_CURR() (*it == "\n")

namespace samilang::lexer {
    using namespace std;

    Lexer::Lexer(const string& file_name):
        Reader(make_unique<FileScanner>(file_name)),
        code(Reader->readFile()) {
        tie(src, srcList) = code;
    }

    void Lexer::test() const {
        for (const auto& line: srcList)
            cout << line << "\n";
        cout << "-------------------------\n";
    }

    LexerExceptions Lexer::tokenize() {
        // remove all comments and empty lines
        removeEmptyLines();
        removeComments();

        // tokenize the input string src
        /*for (const auto& line: srcList) {
            LexerExceptions res = tokenizeLine(line, static_cast<int>(line.size()));
            if (res != E_OK) return res;
        }*/
        return E_OK;
    }

    // at this moment there are no comments left
    LexerExceptions Lexer::tokenizeLine(const string &line, const int &len) {
        LexerExceptions res = E_OK;
        return res;
    }

    LexerExceptions Lexer::removeComments() {

    }

    LexerExceptions Lexer::removeEmptyLines() {
        auto last = srcList.end();
        for (auto it = srcList.begin(); it != last; ++it) {
            if (EMPTY_CURR())
                srcList.erase(it);
        }
        return E_OK;
    }
}