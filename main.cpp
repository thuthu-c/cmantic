#include <fstream>
#include <iostream>

#include "recursive_parser.hpp"
#include "predictive_parser.hpp"

#define SYNTAX_ANALYZER 0 // 0 -> PREDICTIVE | 1 -> RECURSIVE

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

    #if SYNTAX_ANALYZER == 0
    PredictiveParser lexer(&file);
    lexer.parse();

    # elif SYNTAX_ANALYZER == 1
    RecursiveParser lexer(&file);
    lexer.parse();
    // std::cout << token << std::endl;
    #endif

    return 0;
}
