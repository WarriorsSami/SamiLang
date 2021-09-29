//
// Created by sami on 11.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP
#define SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP

#include <exception>
#include <cstring>
#include <utility>
#include "../../lexer/include/token.hpp"

namespace samilang {
    using namespace std;

    using p_read = pair<string, vector<string>>;

    struct FileNotFoundException: exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "Cannot open the given file\n";
        }
    };

    struct UnreadableFileException: exception {
        [[nodiscard]] const char* what() const noexcept override {
            return "Cannot read file's content\n";
        }
    };

    namespace lexer {
        enum LexerExceptions {
            E_OK,
            E_LEX_FAIL,
            E_PARSE_FAIL
        };
    }

    struct CustomException {
        int err_code, err_line;
        string err_text;

        CustomException(const int& code, const int& line, string  text):
            err_code(code), err_line(line), err_text(std::move(text)) {}

        [[nodiscard]] char* displayError() const {
            char mask[] = "<ERROR_STATUS>: {\n"
                          "     code: %d,\n"
                          "     line: %d,\n"
                          "     message: %s\n"
                          "}";
            char *str = static_cast<char *>(calloc(strlen(mask) + err_text.size() + 10, sizeof(char)));
            sprintf(str, mask, err_code, err_line, err_text.c_str());
            return str;
        }
    };

    using str_err = pair<string, CustomException>;
    using nr_err = tuple<lexer::TokenType, string, CustomException>;
    using op_err = pair<lexer::TokenType, CustomException>;
}

#endif //SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP
