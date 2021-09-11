//
// Created by sami on 11.09.2021.
//

#include "../include/file_scanner.hpp"
#include "../include/exceptions.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace samilang {
    using namespace std;

    FileScanner::FileScanner(const string &file_name) {
        try {
            fin.open(file_name, fstream::in);
            if (!fin.is_open())
                throw FileNotFoundException();
        } catch (FileNotFoundException& e) {
            cerr << e.what();
        }
    }

    string FileScanner::getString() {
        string src;
        try {
            stringstream buffer;
            buffer << fin.rdbuf();
            src = buffer.str();
            return src;
        } catch (UnreadableFileException& e) {
            cerr << e.what();
        }
        return src;
    }
}