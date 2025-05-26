#include "symbol_table.hpp"

SymbolTable *curr_table = NULL;

unsigned int hash(const std::string key) {
    unsigned int hash = 5333;
    for(char letter: key){
        hash = ((hash << 5) + hash) + letter++; //  hash * 33 + letter
    }
    return hash;
}

void insert_symbol(const std::string name) {
    unsigned int index = hash(name) % MAX_TABLE_SIZE;
    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    new_symbol->name = name;
    new_symbol->type = UNDEFINED;
    
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
        unsigned int index = hash(name) % MAX_TABLE_SIZE;
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

std::string getSymbolTypeNames(Symbol * symbol){
    return symbolTypeNames[symbol->type];
}

std::string getVarTypeName(VarType varType){
    //TODO printar a "quantidade de referências" do tipo

    if(varType.p_type != NOTPRIMITIVE){
        return primitiveTypeNames[varType.p_type];
    }

    return varType.record_name;
}

std::string getParameterListString(Procedure procedure){
    //TODO
    return "TODO";
}

std::string getProcedureContent(Procedure procedure){
    // o retorno deve ser algo como [ReturnType = bla, Parameters = [bla, bla, bla]]
    return "[ReturnType = " + getVarTypeName(procedure.return_type) + 
           ", Parameters = [" + getParameterListString(procedure) + "]";
}

std::string getFieldsListString(Record record){
    //TODO
    return "TODO";
}

std::string getRecordContent(Record record){
    // o retorno deve ser algo como [Fields = [bla: bla, bla: bla, bla: bla]]
    return "[Fields = [" + getFieldsListString(record) + "]]";
}

std::string getVariableContent(Variable variable){
    // o retorno deve ser algo como [VarType = bla]
    return "[VarType = " + getVarTypeName(variable.type) + "]";
}



std::string getSymbolContent(Symbol * symbol){
    if(!symbol->type){
        return "null";
    }

    switch (symbol->type){
        case PROCEDURE:
            return getProcedureContent(symbol->content._procedure);
            break;
        case RECORD:
            return getRecordContent(symbol->content._record);
            break;
        case VARIABLE:
            return getVariableContent(symbol->content._variable);
            break;
        default:
            return "UNDEFINED";
    }
}

void printSymbolTypeAndContent(Symbol * symbol){
    std::cout << "[Name = " << symbol->name
              << ", [SymbolType = " << getSymbolTypeNames(symbol) 
              << ", SymbolContent = " << getSymbolContent(symbol) << "]]";
    // a função deve printar algo como [Name = bla, Info= [SymbolType = bla, SymbolContent = bla]]
}



void print_scope(const SymbolTable *scope){
    if(!scope){
        std::cout << "No scope found!\n";
        return;
    }

    if(scope->parent){
        print_scope(scope->parent);
        std::cout << "\u2191\n";
    }

    std::cout << "-\n";

    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        Symbol *symbol = scope->symbols[i];
        while (symbol) {
            printSymbolTypeAndContent(symbol);
            std::cout << " ->";
            symbol = symbol->next;
        }
        std::cout << "\u2205";
        std::cout << "\n";
    }

    std::cout << "-\n";
}

void print_table_() {
    print_scope(curr_table);
}