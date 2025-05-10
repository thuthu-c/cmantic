#pragma once

#include <unordered_map>
#include <string>

typedef enum
{
    A_EOF = 0,                  // 0 - End of file
    A_PROGRAM = -64,            // -64 - "program" keyword
    A_PROCEDURE = -63,          // -63 - "procedure" keyword
    A_BEGIN = -62,              // -62 - "begin" keyword
    A_END = -61,                // -61 - "end" keyword
    // BLOCO (Block statements)
    A_IF = -60,                 // -60 - "if" keyword
    A_THEN = -59,               // -59 - "then" keyword
    A_ELSE = -58,               // -58 - "else" keyword
    A_FI = -57,                 // -57 - "fi" keyword
    A_WHILE = -56,              // -56 - "while" keyword
    A_DO = -55,                 // -55 - "do" keyword
    A_OD = -54,                 // -54 - "od" keyword
    A_UNLESS = -53,             // -53 - "unless" keyword
    A_CASE = -52,               // -52 - "case" keyword
    A_OF = -51,                 // -51 - "of" keyword
    A_ESAC = -50,               // -50 - "esac" keyword
    A_OTHERWISE = -49,          // -49 - "otherwise" keyword
    A_RETURN = -48,             // -48 - "return" keyword
    // VÁRIAVEL-LIKE (Variable-like constructs)
    A_VAR = -47,                // -47 - "var" keyword
    A_IN = -46,                 // -46 - "in" keyword
    A_NOT = -45,                // -45 - "not" keyword
    A_NEW = -44,                // -44 - "new" keyword
    A_REF = -43,                // -43 - "ref" keyword
    A_DEREF = -42,              // -42 - "deref" keyword
    A_NULL = -41,               // -41 - "null" keyword
    A_STRUCT = -40,             // -40 - "struct" keyword
    A_BOOL = -39,               // -39 - "bool" keyword
    A_FLOAT = -38,              // -38 - "float" keyword
    A_INT = -37,                // -37 - "int" keyword
    A_STRING = -36,             // -36 - "string" keyword
    // LITERAIS (Literals)
    A_STRING_LITERAL = -35,     // -35 - String literal
    A_INA_LITERAL = -34,        // -34 - Integer literal
    A_FLOAA_LITERAL = -33,      // -33 - Float literal
    A_TRUE = -32,               // -32 - "true" boolean literal
    A_FALSE = -31,              // -31 - "false" boolean literal
    A_NAME = -30,               // -30 - Identifier (name)
    // COMENTÁRIOS (Comments)
    A_SINGLE_COMMENT = -29,     // -29 - Single-line comment
    A_MULTI_COMMENT = -28,      // -28 - Multi-line comment
    // SIMBOLOS (Symbols)
    A_SEMICOLON = -27,          // -27 - ";"
    A_COLON = -26,              // -26 - ":"
    A_COMMA = -25,              // -25 - ","
    A_ASSIGN = -24,             // -24 - ":="
    A_DOT = -23,                // -23 - "."
    A_LEFA_BRACKET = -22,       // -22 - "["
    A_RIGHA_BRACKET = -21,      // -21 - "]"
    A_LEFA_PARENTHESIS = -20,   // -20 - "("
    A_RIGHA_PARENTHESIS = -19,  // -19 - ")"
    A_LEFA_BRACES = -18,        // -18 - "{"
    A_RIGHA_BRACES = -17,       // -17 - "}"
    A_OR_LOGIC = -16,           // -16 - "||" (logical OR)
    A_AND_LOGIC = -15,          // -15 - "&&" (logical AND)
    A_LESS_THAN = -14,          // -14 - "<"
    A_LESS_THAN_EQUAL = -13,    // -13 - "<="
    A_GREATER_THAN = -12,       // -12 - ">"
    A_GREATER_THAN_EQUAL = -11, // -11 - ">="
    A_EQUAL = -10,              // -10 - "=="
    A_DIFFERENT = -9,           // -9 - "<>"
    A_PLUS = -8,                // -8 - "+"
    A_MINUS = -7,               // -7 - "-"
    A_MULTIPLY = -6,            // -6 - "*"
    A_DIVIDE = -5,              // -5 - "/"
    A_POWER = -4,               // -4 - "^"
    A_END_LINE = -3,            // -3 - End of line (newline)
    A_RANGE = -2,               // -2 - ".." (range operator)
} ATOMIC_SYMBOLS;


static const std::unordered_map<int, std::string> ATOMIC_SYMBOLS_STRINGS = {
    {A_EOF, "A_EOF"},
    {A_PROGRAM, "A_PROGRAM"},
    {A_PROCEDURE, "A_PROCEDURE"},
    {A_BEGIN, "A_BEGIN"},
    {A_END, "A_END"},
    {A_IF, "A_IF"},
    {A_THEN, "A_THEN"},
    {A_ELSE, "A_ELSE"},
    {A_FI, "A_FI"},
    {A_WHILE, "A_WHILE"},
    {A_DO, "A_DO"},
    {A_OD, "A_OD"},
    {A_UNLESS, "A_UNLESS"},
    {A_CASE, "A_CASE"},
    {A_OF, "A_OF"},
    {A_ESAC, "A_ESAC"},
    {A_OTHERWISE, "A_OTHERWISE"},
    {A_RETURN, "A_RETURN"},
    {A_VAR, "A_VAR"},
    {A_IN, "A_IN"},
    {A_NOT, "A_NOT"},
    {A_NEW, "A_NEW"},
    {A_REF, "A_REF"},
    {A_DEREF, "A_DEREF"},
    {A_NULL, "A_NULL"},
    {A_STRUCT, "A_STRUCT"},
    {A_BOOL, "A_BOOL"},
    {A_FLOAT, "A_FLOAT"},
    {A_INT, "A_INT"},
    {A_STRING, "A_STRING"},
    {A_STRING_LITERAL, "A_STRING_LITERAL"},
    {A_INA_LITERAL, "A_INA_LITERAL"},
    {A_FLOAA_LITERAL, "A_FLOAA_LITERAL"},
    {A_TRUE, "A_TRUE"},
    {A_FALSE, "A_FALSE"},
    {A_NAME, "A_NAME"},
    {A_SINGLE_COMMENT, "A_SINGLE_COMMENT"},
    {A_MULTI_COMMENT, "A_MULTI_COMMENT"},
    {A_SEMICOLON, "A_SEMICOLON"},
    {A_COLON, "A_COLON"},
    {A_COMMA, "A_COMMA"},
    {A_ASSIGN, "A_ASSIGN"},
    {A_DOT, "A_DOT"},
    {A_LEFA_BRACKET, "A_LEFA_BRACKET"},
    {A_RIGHA_BRACKET, "A_RIGHA_BRACKET"},
    {A_LEFA_PARENTHESIS, "A_LEFA_PARENTHESIS"},
    {A_RIGHA_PARENTHESIS, "A_RIGHA_PARENTHESIS"},
    {A_LEFA_BRACES, "A_LEFA_BRACES"},
    {A_RIGHA_BRACES, "A_RIGHA_BRACES"},
    {A_OR_LOGIC, "A_OR_LOGIC"},
    {A_AND_LOGIC, "A_AND_LOGIC"},
    {A_LESS_THAN, "A_LESS_THAN"},
    {A_LESS_THAN_EQUAL, "A_LESS_THAN_EQUAL"},
    {A_GREATER_THAN, "A_GREATER_THAN"},
    {A_GREATER_THAN_EQUAL, "A_GREATER_THAN_EQUAL"},
    {A_EQUAL, "A_EQUAL"},
    {A_DIFFERENT, "A_DIFFERENT"},
    {A_PLUS, "A_PLUS"},
    {A_MINUS, "A_MINUS"},
    {A_MULTIPLY, "A_MULTIPLY"},
    {A_DIVIDE, "A_DIVIDE"},
    {A_POWER, "A_POWER"},
    {A_END_LINE, "A_END_LINE"},
    {A_RANGE, "A_RANGE"}
};

typedef enum
{
    P_PROGRAM = 1,           // 1 - "program"
    P_DECLS,                 // 2 - "decls"
    P_DECL,                  // 3 - "decl"
    P_DECLS_,                // 4 - "decls_"
    P_VAR_DECL,              // 5 - "var_decl"
    P_PROC_DECL,             // 6 - "proc_decl"
    P_REC_DECL,              // 7 - "rec_decl"
    P_RS_VAR_DECL,           // 8 - "rs_var_decl"
    P_TYPE,                  // 9 - "type"
    P_VAR_INIT,              // 10 - "var_init"
    P_EXP,                   // 11 - "exp"
    P_PARAMS,                // 12 - "params"
    P_PROC_REA_DECL,         // 13 - "proc_reA_decl"
    P_PROC_BODY,             // 14 - "proc_body"
    P_DECLS_OPT,             // 15 - "decls_opt"
    P_STMA_LIST,             // 16 - "stmA_list"
    P_REC_FIELDS,            // 17 - "rec_fields"
    P_PARAMFIELD_DECL,       // 18 - "paramfield_decl"
    P_REC_FIELDS_,           // 19 - "rec_fields_"
    P_PARAMS_,               // 20 - "params_"
    P_STMT,                  // 21 - "stmt"
    P_STMA_LISA_,            // 22 - "stmA_lisA_"
    P_ASSIGN_OR_CALL_STMT,   // 23 - "assign_or_call_stmt"
    P_IF_STMT,               // 24 - "if_stmt"
    P_WHILE_STMT,            // 25 - "while_stmt"
    P_RETURN_STMT,           // 26 - "return_stmt"
    P_REGISTER,              // 27 - "register"
    P_ATRIBUTE,              // 28 - "atrubute"
    P_DEREF_VAR,             // 29 - "deref_var"
    P_EXPS,                  // 30 - "exps"
    P_EXPS_,                 // 31 - "exps_"
    P_ELSE_PART,             // 32 - "else_part"
    P_CASES,                 // 33 - "cases"
    P_CASE_DEFAULT,          // 34 - "case_default"
    P_CASE,                  // 35 - "case"
    P_CASE_,                 // 36 - "case_"
    P_INTERVALS,             // 37 - "intervals"
    P_INTERVAL,              // 38 - "interval"
    P_INTERVALS_,            // 39 - "intervals_"
    P_CASE_RANGE,            // 40 - "case_range"
    P_AND_EXP,               // 41 - "and_exp"
    P_EXP_,                  // 42 - "exp_"
    P_NOA_EXP,               // 43 - "noA_exp"
    P_AND_EXP_,              // 44 - "and_exp_"
    P_REL_EXP,               // 45 - "rel_exp"
    P_ADD_EXP,               // 46 - "add_exp"
    P_REL_EXP_,              // 47 - "rel_exp_"
    P_REL_OP,                // 48 - "rel_op"
    P_MULA_EXP,              // 49 - "mulA_exp"
    P_ADD_EXP_,              // 50 - "add_exp_"
    P_ADD_OP,                // 51 - "add_op"
    P_POW_EXP,               // 52 - "pow_exp"
    P_MULA_EXP_,             // 53 - "mulA_exp_"
    P_MULA_OP,               // 54 - "mulA_op"
    P_VALUE,                 // 55 - "value"
    P_POW_EXP_,              // 56 - "pow_exp_"
    P_VAR_OR_CALL,           // 57 - "var_or_call"
    P_LITERAL,               // 58 - "literal"
    P_REF_VAR,               // 59 - "ref_var"
    P_VAR,                   // 60 - "var"
    P_DE_VAR,                // 61 - "de_var"
    P_FUNC_CALL,             // 62 - "func_call"
    P_BOOL_LITERAL,          // 63 - "bool_literal"
} PRODUCTION_SYMBOLS;

// std::map<int, std::string> symbol_map = {
//     {-63, "id"},
//     {-62, "bool"},
//     {-61, "string"},
//     {-60, "int"},
//     {-59, "float"},
//     {-58, "false"},
//     {-57, "true"},
//     {-56, "null"},
//     {-55, "STRING_LITERAL"},
//     {-54, "FLOAT_LITERAL"},
//     {-53, "/"},
//     {-52, "*"},
//     {-51, "-"},
//     {-50, "+"},
//     {-49, "<>"},
//     {-48, "="},
//     {-47, ">="},
//     {-46, ">"},
//     {-45, "<="},
//     {-44, "<"},
//     {-43, ""},
//     {-42, "."},
//     {-41, "deref"},
//     {-40, "ref"},
//     {-39, "new"},
//     {-38, "^"},
//     {-37, "not"},
//     {-36, "&&"},
//     {-35, "||"},
//     {-34, "return"},
//     {-33, "while"},
//     {-32, "otherwise"},
//     {-31, ".."},
//     {-30, "INT_LITERAL"},
//     {-29, "else"},
//     {-28, "esac"},
//     {-27, "of"},
//     {-26, "case"},
//     {-25, "od"},
//     {-24, "do"},
//     {-23, "unless"},
//     {-22, "fi"},
//     {-21, "then"},
//     {-20, "if"},
//     {-19, "EXP''"},
//     {-18, ","},
//     {-17, "}"},
//     {-16, "{"},
//     {-15, "struct"},
//     {-14, "in"},
//     {-13, ")"},
//     {-12, "("},
//     {-11, "procedure"},
//     {-10, ":="},
//     {-9, ":"},
//     {-8, "var"},
//     {-7, ";"},
//     {-6, "end"},
//     {-5, "begin"},
//     {-4, "NAME"},
//     {-2, "$"},
//     {-1, "ε"},
//     {1, "program"},
//     {2, "PROGRAM"},
//     {3, "DECLS"},
//     {4, "DECL"},
//     {5, "DECLS_"},
//     {6, "VAR_DECL"},
//     {7, "PROC_DECL"},
//     {8, "REC_DECL"},
//     {9, "RS_VAR_DECL"},
//     {10, "TYPE"},
//     {11, "VAR_INIT"},
//     {12, "EXP"},
//     {13, "PARAMS"},
//     {14, "PROC_RET_DECL"},
//     {15, "PROC_BODY"},
//     {16, "DECLS_OPT"},
//     {17, "STMT_LIST"},
//     {18, "REC_FIELDS"},
//     {19, "PARAMFIELD_DECL"},
//     {20, "REC_FIELDS_"},
//     {21, "PARAMS_"},
//     {22, "STMT"},
//     {23, "STMT_LIST_"},
//     {24, "ASSIGN_OR_CALL_STMT"},
//     {25, "IF_STMT"},
//     {26, "WHILE_STMT"},
//     {27, "RETURN_STMT"},
//     {28, "REGISTER"},
//     {29, "ATRIBUTE"},
//     {30, "DEREF_VAR"},
//     {31, "EXPS"},
//     {32, "EXPS_"},
//     {33, "ELSE_PART"},
//     {34, "CASES"},
//     {35, "CASE_DEFAULT"},
//     {36, "CASE"},
//     {37, "CASE_"},
//     {38, "INTERVALS"},
//     {39, "INTERVAL"},
//     {40, "INTERVALS_"},
//     {41, "CASE_RANGE"},
//     {42, "AND_EXP"},
//     {43, "EXP_"},
//     {44, "NOT_EXP"},
//     {45, "AND_EXP_"},
//     {46, "REL_EXP"},
//     {47, "ADD_EXP"},
//     {48, "REL_EXP_"},
//     {49, "REL_OP"},
//     {50, "MULT_EXP"},
//     {51, "ADD_EXP_"},
//     {52, "ADD_OP"},
//     {53, "POW_EXP"},
//     {54, "MULT_EXP_"},
//     {55, "MULT_OP"},
//     {56, "VALUE"},
//     {57, "POW_EXP_"},
//     {58, "VAR_OR_CALL"},
//     {59, "LITERAL"},
//     {60, "REF_VAR"},
//     {61, "VAR"},
//     {62, "DE_VAR"},
//     {63, "FUNC_CALL"},
//     {64, "BOOL_LITERAL"},
// };
