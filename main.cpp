#include <fstream>
#include <iostream>

#include "custom_lexer.hpp"
// #include "parser.tab.hh"
// #include "recursive_parser.hpp"
// #include "predictive_parser.hpp"

#define SYNTAX_ANALYZER 2 // 0 -> PREDICTIVE | 1 -> RECURSIVE | 2 -> ASCENDENT

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
    // PredictiveParser lexer(&file);
    // lexer.parse();

    # elif SYNTAX_ANALYZER == 1
    // RecursiveParser lexer(&file);
    // lexer.parse();
    // std::cout << token << std::endl;
    #elif SYNTAX_ANALYZER == 2
    CustomLexer lexer(&file);
    yy::parser parser(lexer);
    // parser.set_debug_level(1);
    return parser();
    #endif

    return 0;
}
