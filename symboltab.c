#include "symboltab.h"

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
    new_symbol->name = strdup(name);
    
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
            if (strcmp(symbol->name, name) == 0) {
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
            free(temp->name);
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

// char* concatenate_string_list(const char *list[], size_t list_size) {
//     size_t size = 0;

//     for(int i = 0; i < list_size; ++i){
//         size += strlen(list[i]);
//     }

//     char result[size + 1];
    

//     int index = 0;
//     char* pointer;
//     for(int i = 0; i < list_size; ++i){
//         pointer = list[i];
//         while(*pointer){
//             result[index++]= *pointer++;
//         }
//     }

//     return result;
// }

void print_table() {
    SymbolTable *aux_table = curr_table;
    // printf("Table é nulo? %s\n", aux_table == NULL ? "Sim" : "Não");
    while (aux_table) {
        for (int i = 0; i < MAX_TABLE_SIZE; i++) {
            Symbol *symbol = aux_table->symbols[i];
            // printf("Symbol é nulo? %s\n", symbol == NULL ? "Sim" : "Não");
            while (symbol) {
                printf("Symbol: %s ", symbol->name);
                symbol = symbol->next;
            }
        }
        aux_table = aux_table->parent;
    }
    printf("\n");
}

// char* getSymbolTypeNames(Symbol * symbol){
//     if(!symbol->type){
//         return "null";
//     }
//     return symbolTypeNames[symbol->type];
// }

// char* getVarTypeName(VarType varType){
//     //TODO printar a "quantidade de referências" do tipo

//     if(varType.p_type != NOTPRIMITIVE){
//         return primitiveTypeNames[varType.p_type];
//     }

//     return varType.record_name;
// }

// // typedef union {
// //     Procedure _procedure;
// //     Record _record;
// //     Variable _variable;
// // } SymbolContent;

// char* getParameterListString(Procedure procedure){
//     //TODO
//     return "TODO";
// }

// char* getProcedureContent(Procedure procedure){

//     // TODO: usar o getParameterListString em vez de bla, bla, bla
//     char *strings[] = {
//         "[ReturnType = ", 
//         getVarTypeName(procedure.return_type),
//         ", Parameters = [",
//         "bla, bla, bla",
//         "]"
//     };
//     // o retorno deve ser algo como [ReturnType = bla, Parameters = [bla, bla, bla]]

    
//     return concatenate_string_list(strings, 5);
// }

// char* getFieldsListString(Record record){
//     //TODO
//     return "TODO";
// }

// char* getRecordContent(Record record){

//     // TODO: usar o getFieldsListString em vez de bla: bla, bla: bla, bla: bla
//     char *strings[] = {
//         "[Fields = [",
//         "bla: bla, bla: bla, bla: bla",
//         "]]"
//     };
//     // o retorno deve ser algo como [Fields = [bla: bla, bla: bla, bla: bla]]

    
//     return concatenate_string_list(strings, 3);
// }

// char* getVariableContent(Variable variable){

//     char *strings[] = {
//         "[VarType = ",
//         getVarTypeName(variable.type),
//         "]"
//     };
//     // o retorno deve ser algo como [VarType = bla]

//     return concatenate_string_list(strings, 3);
// }



// char* getSymbolContent(Symbol * symbol){
//     if(!symbol->type){
//         return "null";
//     }
//     switch (symbol->type){
//         case PROCEDURE:
//         return getProcedureContent(symbol->content._procedure);
//         break;

//         case RECORD:
//         return getRecordContent(symbol->content._record);
//         break;

//         case VARIABLE:
//         /* code */
//         break;
//     }
// }

// void printSymbolTypeAndContent(Symbol * symbol){
//     printf("[SymbolType = %s, SymbolContent = %s]", getSymbolTypeNames(symbol), getSymbolContent(symbol));
// }



// void print_scope(const SymbolTable *scope){
//     if(scope){
//         print_scope(scope->parent);
//         printf("\u2191\n");
//     }

//     printf("-");

//     for (int i = 0; i < MAX_TABLE_SIZE; i++) {
//         Symbol *symbol = scope->symbols[i];
//         while (symbol) {
//             printSymbolTypeAndContent(symbol);
//             printf(" ->");
//             symbol = symbol->next;
//         }
//         printf("\u2205");
//     }
}