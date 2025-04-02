#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <vector>

#define MAX_TABLE_SIZE 11

typedef struct Symbol Symbol;

typedef struct SymbolTable SymbolTable;

typedef enum {
    PROCEDURE,
    RECORD,
    VARIABLE
} SymbolType;

const std::string symbolTypeNames[] = {"PROCEDURE", "RECORD", "VARIABLE"};

typedef enum {
    BOOL,
    FLOAT,
    INT,
    STRING,
    VOID,
    NOTPRIMITIVE
} PrimitiveType;

const std::string primitiveTypeNames[] = {"BOOL", "FLOAT", "INT", "STRING", "VOID", "NOTPRIMITIVE"};

typedef struct{
    std::string record_name;
    PrimitiveType p_type;
    int n_ref;
} VarType;

typedef struct {
    std::string name;
    VarType type;
} Parameter;

typedef struct {
    VarType return_type;
    std::vector<Parameter> params;
} Procedure;

typedef struct {
    VarType type;
} Variable;

typedef struct {
    std::string name;
    VarType type;
} Field;

typedef struct {
    std::vector<Field> fields;
    size_t n_fields;
} Record;

typedef union {
    Procedure _procedure;
    Record _record;
    Variable _variable;
} SymbolContent;

typedef struct Symbol {
    std::string name;
    SymbolType type;
    SymbolContent content;
    Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *symbols[MAX_TABLE_SIZE];
    SymbolTable *parent;
} SymbolTable;

unsigned int hash(const std::string key);

void insert_symbol(const std::string name);
// void insert_symbol(const std::string name, SymbolType type, SymbolContent content);
Symbol *lookup_symbol(const std::string name);

void insert_scope();
void remove_scope();

void free_table();

void print_table();

#endif