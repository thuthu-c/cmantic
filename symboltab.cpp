#include "symboltab.h"

SymbolTable *curr_table = NULL;

unsigned int hash(const std::string key) {
    unsigned int hash = 5333;
    for (char key_char : key) {
        hash = (hash * 33) + key_char;
    }
    // while (*key) {
    //     hash = (hash * 33) + *key++;
    // }
    return hash % MAX_TABLE_SIZE;
}

void insert_symbol(const std::string name) {
    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    new_symbol->name = name;
    
    new_symbol->next = curr_table->symbols[index];
    curr_table->symbols[index] = new_symbol;
}

// void insert_symbol(const char *name, SymbolType type, SymbolContent content) {
//     unsigned int index = hash(name);
//     Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
//     new_symbol->name = strdup(name);
//     new_symbol->type = type;
//     new_symbol->content = content;
//     new_symbol->next = curr_table->symbols[index];
//     curr_table->symbols[index] = new_symbol;
// }

Symbol *lookup_symbol(const std::string name) {
    SymbolTable *aux_table = curr_table;
    while (aux_table) {
        unsigned int index = hash(name);
        Symbol *symbol = aux_table->symbols[index];
        while (symbol) {
            if (symbol->name == name) {
                return symbol;
            }
            symbol = symbol->next;
        }
        aux_table = aux_table->parent;
    }
    return NULL;
}

void insert_scope() {
    SymbolTable *aux_table = (SymbolTable *)malloc(sizeof(SymbolTable));

    if (!aux_table) {
        printf("Erro: problema na alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        aux_table->symbols[i] = NULL;
    }
    aux_table->parent = curr_table;
    curr_table = aux_table;
}

void remove_scope() {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        Symbol *aux = curr_table->symbols[i];
        while (aux) {
            Symbol *temp = aux;
            aux = aux->next;
            free(temp);
        }
    }
    SymbolTable *parent_table = curr_table->parent;
    free(curr_table);
    curr_table = parent_table;
}

void free_table() {
    while (curr_table) {
        remove_scope();
    }
}

void print_table() {
    SymbolTable *aux_table = curr_table;
    while (aux_table) {
        for (int i = 0; i < MAX_TABLE_SIZE; i++) {
            Symbol *symbol = aux_table->symbols[i];
            while (symbol) {
                std::cout << "Symbol: " << symbol->name << " ";
                symbol = symbol->next;
            }
        }
        aux_table = aux_table->parent;
    }
    std::cout << std::endl;
}