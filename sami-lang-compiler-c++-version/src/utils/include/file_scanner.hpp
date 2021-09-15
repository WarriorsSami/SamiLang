//
// Created by sami on 11.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP
#define SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP

#include <fstream>
#include <string>
#include <vector>
#include "exceptions.hpp"

namespace samilang {
    using namespace std;
    using namespace lexer;
    using p_read = pair<string, vector<string>>;
    using str_err = pair<string, LexerExceptions>;

    // class for reading content of files as string and
    // retrieving the output to the lexer
    class FileScanner {
    public:
        explicit FileScanner(const string& file_name);
        string getString();
        vector<string> getStringList();
        p_read readFile();

    private:
        ifstream fin;
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP
