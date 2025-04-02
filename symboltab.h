#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <string>

#define MAX_TABLE_SIZE 10

typedef struct Symbol Symbol;

typedef struct SymbolTable SymbolTable;

typedef enum {
    PROCEDURE,
    RECORD,
    VARIABLE
} SymbolType;

typedef enum {
    BOOL,
    FLOAT,
    INT,
    STRING,
    REFERENCE,
    OTHER
} VarType;

typedef struct {
    std::string name;
    VarType type;
    bool is_const;
    bool is_ref;
} Parameter;

typedef struct {
    VarType return_type;
    Parameter *params;
} Procedure;

typedef struct {
    VarType type;
    // VarValue value;
} Variable;

typedef union {
    bool _bool;
    double _float;
    int _int;
    char *_string;
    Variable _ref;
} VarValue;

typedef struct {
    std::string name;
    VarType type;
    VarValue value;
} Field;

typedef struct {
    Field *fields;
} Record;

typedef union {
    Procedure _procedure;
    Record _record;
    Variable _variable;
} SymbolContent;

typedef struct Symbol {
    std::string name;
    // SymbolType type;
    // SymbolContent content;
    Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *symbols[MAX_TABLE_SIZE];
    SymbolTable *parent;
} SymbolTable;

unsigned int hash(const char *key);

void insert_symbol(const std::string name);
// void insert_symbol(const std::string name;, SymbolType type, SymbolContent content);
Symbol *lookup_symbol(const std::string name);

void insert_scope();
void remove_scope();

void free_table();

void print_table();

#endif