//
// Created by sami on 11.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP
#define SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP

#include <exception>
#include "../../lexer/include/token.hpp"

namespace samilang {
    using namespace std;

    using p_read = pair<string, vector<string>>;

    struct FileNotFoundException: exception {
        const char* what() const noexcept override {
            return "Cannot open the given file\n";
        }
    };

    struct UnreadableFileException: exception {
        const char* what() const noexcept override {
            return "Cannot read file's content\n";
        }
    };

    namespace lexer {
        enum LexerExceptions {
            E_OK,
            E_LEX_FAIL,
            E_PARSE_FAIL
        };

        using str_err = pair<string, LexerExceptions>;
        using nr_err = tuple<TokenType, string, LexerExceptions>;
    }
}

#endif //SAMI_LANG_COMPILER_C___VERSION_EXCEPTIONS_HPP
