#undef yyFlexLexer
#define yyFlexLexer MyFlexLexer
#include <FlexLexer.h>
#include <fstream>
#include <iostream>
#include "program_map.hpp"

# define SYNTAX_ANALYZER 1 // 0 -> PREDICTIVE | 1 -> RECURSIVE

int line_number = 0;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_teste>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    MyFlexLexer lexer(&file);

    int token;
    while ((token = lexer.yylex()) != 0) {
        #if SYNTAX_ANALYZER == 0
        std::cout << token << std::endl;
        # elif SYNTAX_ANALYZER == 1
        std::cout << token << std::endl;
        #endif
    }

    return 0;
}
