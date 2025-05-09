cmake_minimum_required(VERSION 3.12)

project(LexerExample CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)

# Gere scanner C++ com Flex
FLEX_TARGET(MyScanner dictionary.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.hpp)

add_executable(lexer
    ${FLEX_MyScanner_OUTPUTS}
    symboltab.cpp
    main.cpp            # <-- adicionado aqui
)

target_include_directories(lexer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
