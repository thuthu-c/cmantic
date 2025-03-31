#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 10

typedef enum {
    PROCEDURE,
    RECORD,
    VARIABLE
} SymbolType;

typedef struct {
    char *name;
    VarType type;
    bool is_const;
    bool is_ref;
} Parameter;

typedef struct {
    VarType return_type;
    Parameter *params;
} Procedure;

typedef struct {
    char *name;
    VarType type;
    VarValue value;
} Field;

typedef struct {
    Field *fields;
} Record;

typedef enum {
    BOOL,
    FLOAT,
    INT,
    STRING,
    OTHER
} VarType;

typedef union {
    bool _bool;
    double _float;
    int _int;
    char *_string;
} VarValue;

typedef struct {
    bool is_const;
    bool is_ref;
    VarType type;
    VarValue value;
} Variable;

typedef union {
    Procedure _procedure;
    Record _record;
    Variable _variable;
} SymbolContent;

typedef struct {
    char *name;
    SymbolType type;
    SymbolContent content;
    Symbol *next;
} Symbol;

typedef struct {
    Symbol *symbols[TABLE_SIZE];
    SymbolTable *parent;
} SymbolTable;

unsigned int hash(const char *key);

void insert_symbol(const char *name, SymbolType type, SymbolContent content);
Symbol *lookup_symbol(const char *name);

void insert_scope();
void remove_scope();

void free_table();

#endif