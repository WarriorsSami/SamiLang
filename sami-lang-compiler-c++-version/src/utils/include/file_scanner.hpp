//
// Created by sami on 11.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP
#define SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP

#include <fstream>
#include <string>

namespace samilang {
    using namespace std;

    // class for reading content of files as string and
    // retrieving the output to the lexer
    class FileScanner {
    public:
        explicit FileScanner(const string& file_name);
        string getString();

    private:
        ifstream fin;
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_FILE_SCANNER_HPP
