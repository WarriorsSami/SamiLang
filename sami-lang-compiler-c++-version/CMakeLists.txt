cmake_minimum_required(VERSION 3.20)
project(sami_lang_compiler_c___version)

set(CMAKE_CXX_STANDARD 20)

add_executable(sami_lang_compiler_c___version main.cpp src/lexer/include/token.hpp src/lexer/lib/token.cpp src/lexer/include/lexer.hpp src/lexer/lib/lexer.cpp src/utils/lib/file_scanner.cpp src/utils/include/file_scanner.hpp src/utils/lib/driver.cpp src/utils/include/driver.hpp src/utils/include/exceptions.hpp)
