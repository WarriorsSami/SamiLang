//
// Created by sami on 11.09.2021.
//

#include "../include/file_scanner.hpp"
#include "../include/exceptions.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    vector<string> FileScanner::getStringList() {
        vector<string> lines;
        try {
            string curr;
            while (getline(fin, curr))
                lines.emplace_back(curr);
        } catch (UnreadableFileException& e) {
            cerr << e.what();
        }
        return lines;
    }

    p_read FileScanner::readFile() {
        p_read res;
        try {
            string curr;
            while (getline(fin, curr)) {
                res.second.emplace_back(curr);
                res.first += curr;
            }
        } catch (UnreadableFileException& e) {
            cerr << e.what();
        }
        return res;
    }
}