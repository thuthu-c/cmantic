#ifndef _PROGRAM_MAP_
#define _PROGRAM_MAP_

typedef enum
{
    T_EOF,                  // 0 - End of file
    T_PROGRAM,              // 1 - "program" keyword
    T_PROCEDURE,            // 2 - "procedure" keyword
    T_BEGIN,                // 3 - "begin" keyword
    T_END,                  // 4 - "end" keyword
    // BLOCO (Block statements)
    T_IF,                   // 5 - "if" keyword
    T_THEN,                 // 6 - "then" keyword
    T_ELSE,                 // 7 - "else" keyword
    T_FI,                   // 8 - "fi" keyword
    T_WHILE,                // 9 - "while" keyword
    T_DO,                   // 10 - "do" keyword
    T_OD,                   // 11 - "od" keyword
    T_UNLESS,               // 12 - "unless" keyword
    T_CASE,                 // 13 - "case" keyword
    T_OF,                   // 14 - "of" keyword
    T_ESAC,                 // 15 - "esac" keyword
    T_OTHERWISE,            // 16 - "otherwise" keyword
    T_RETURN,               // 17 - "return" keyword
    // VÁRIAVEL-LIKE (Variable-like constructs)
    T_VAR,                  // 18 - "var" keyword
    T_IN,                   // 19 - "in" keyword
    T_NOT,                  // 20 - "not" keyword
    T_NEW,                  // 21 - "new" keyword
    T_REF,                  // 22 - "ref" keyword
    T_DEREF,                // 23 - "deref" keyword
    T_NULL,                 // 24 - "null" keyword
    T_STRUCT,               // 25 - "struct" keyword
    T_BOOL,                 // 26 - "bool" keyword
    T_FLOAT,                // 27 - "float" keyword
    T_INT,                  // 28 - "int" keyword
    T_STRING,               // 29 - "string" keyword
    // LITERAIS (Literals)
    T_STRING_LITERAL,       // 30 - String literal
    T_INT_LITERAL,          // 31 - Integer literal
    T_FLOAT_LITERAL,        // 32 - Float literal
    T_TRUE,                 // 33 - "true" boolean literal
    T_FALSE,                // 34 - "false" boolean literal
    T_NAME,                 // 35 - Identifier (name)
    // COMENTÁRIOS (Comments)
    T_SINGLE_COMMENT,       // 36 - Single-line comment
    T_MULTI_COMMENT,        // 37 - Multi-line comment
    // SIMBOLOS (Symbols)
    T_SEMICOLON,            // 38 - ";"
    T_COLON,                // 39 - ":"
    T_COMMA,                // 40 - ","
    T_ASSIGN,               // 41 - ":="
    T_DOT,                  // 42 - "."
    T_LEFT_BRACKET,         // 43 - "["
    T_RIGHT_BRACKET,        // 44 - "]"
    T_LEFT_PARENTHESIS,     // 45 - "("
    T_RIGHT_PARENTHESIS,    // 46 - ")"
    T_LEFT_BRACES,          // 47 - "{"
    T_RIGHT_BRACES,         // 48 - "}"
    T_OR_LOGIC,             // 49 - "or" (logical OR)
    T_AND_LOGIC,            // 50 - "and" (logical AND)
    T_LESS_THAN,            // 51 - "<"
    T_LESS_THAN_EQUAL,      // 52 - "<="
    T_GREATER_THAN,         // 53 - ">"
    T_GREATER_THAN_EQUAL,   // 54 - ">="
    T_EQUAL,                // 55 - "=="
    T_DIFFERENT,            // 56 - "<>"
    T_PLUS,                 // 57 - "+"
    T_MINUS,                // 58 - "-"
    T_MULTIPLY,             // 59 - "*"
    T_DIVIDE,               // 60 - "/"
    T_POWER,                // 61 - "^"
    T_END_LINE,             // 62 - End of line (newline)
    T_RANGE,                // 63 - ".." (range operator)
} ATOMIC_SYMBOLS;



#endif