#include <iostream>
#include "symbol_table.hpp"

int main(){
    insert_scope();

    insert_symbol("Teste 1");
    insert_symbol("Teste 1");
    insert_symbol("Teste 1");
    insert_symbol("Teste 2");
    insert_symbol("Teste 2");

    insert_scope();

    insert_symbol("Teste 1");
    insert_symbol("Teste 2");
    insert_symbol("Teste 3");
    insert_symbol("Teste 4");
    insert_symbol("Teste 5");

    insert_scope();

    insert_symbol("Teste 1");
    insert_symbol("Teste 2");
    insert_symbol("Teste 3");
    insert_symbol("Teste 4");
    insert_symbol("Teste 5");

    insert_scope();

    insert_symbol("Teste 1");
    insert_symbol("Teste 2");
    insert_symbol("Teste 3");
    insert_symbol("Teste 4");
    insert_symbol("Teste 5");

    std::cout << "Tabela com todos os escopos:\n";
    print_table_();

    std::cout << "Tabela vazia:\n";
    free_table();
    print_table_();
}