//
// Created by sami on 11.09.2021.
//

#ifndef SAMI_LANG_COMPILER_C___VERSION_DRIVER_HPP
#define SAMI_LANG_COMPILER_C___VERSION_DRIVER_HPP

#include <memory>
#include <string>
#include "file_scanner.hpp"
#include "../../../src/lexer/include/lexer.hpp"

namespace samilang {
    using namespace std;
    using namespace lexer;

    // main driver class for the entire compiler
    class Driver {
    public:
        explicit Driver(const string& file_name);
        void launch() const;

    private:
        unique_ptr<Lexer> Lex;

        static void handle(LexerExceptions err) ;
    };
}

#endif //SAMI_LANG_COMPILER_C___VERSION_DRIVER_HPP
