## GRAMMAR

PROGRAM -> program NAME begin [ DECL {";" DECK}] end
DECL -> VAR_DECL | PROC_DECL | REC_DECL
VAR_DECL -> var NAME ":" TYPE [ := EXP] | var NAME := EXP
PROC_DECL -> procedure NAME "(" [PARAMFIELD_DECL {",PARAMFIELD_DECL}] ")" |[":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end
REC_DECL -> struct NAME "{" [ PARAMFIELD_DECL { ";" PARAMFIELD_DECL } ] "}"
PARAMFIELD_DECL -> NAME ":" TYPE
STMT_LIST -> [ STMT { ";" STMT} ]

EXP -> EXP "||" AND_EXP | AND_EXP
AND_EXP -> AND_EXP "&&" NOT_EXP | NOT_EXP
NOT_EXP -> "not" REL_EXP | REL_EXP
REL_EXP -> REL_EXP REL_OP ADD_EXP | ADD_EXP
ADD_EXP -> ADD_EXP ADD_OP MULT_EXP | MULT_EXP
MULT_EXP -> MULT_EXP MULT_OP POW_EXP | POW_EXP
POW_EXP -> VALUE "^" POW_EXP | VALUE"
VALUE -> LITERAL | CALL_STMT | VAR | REF_VAR | DEREF_VAR | "new" NAME | "(" EXP ")"

REF_VAR → ref "(" VAR ")"
DEREF_VAR → deref "(" VAR ")" | deref "(" DEREF_VAR ")"
VAR → NAME | EXP "." NAME
REL_OP → ”<” | ”<=” | ”>” | ”>=” | ”=” | ”<>”
ADD_OP → ”+” | ”−”
MULT_OP -> "*" | "/"
LITERAL → FLOAT_LITERAL | INT_LITERAL | STRING_LITERAL | BOOL_LITERAL | null
BOOL_LITERAL → true | false
STMT → ASSIGN_STMT
        | IF_STMT
        | WHILE_STMT
        | RETURN_STMT
        | CALL_STMT
ASSIGN_STMT → VAR ”:=” EXP | DEREF_VAR ”:=” EXP
IF_STMT → if EXP then STMT_LIST [ else STMT_LIST ] fi
WHILE_STMT → while EXP do STMT_LIST od
RETURN_STMT → return [ EXP ]
CALL_STMT → NAME "(" [ EXP { "," EXP } ] ")"
TYPE → float | int | string | bool | NAME | ref "(" TYPE ")"

## LL1 GRAMMAR

## RULES

~~Por que ingles e português no mesmo arquivo?não sei~~

1. Duas regras de produção iguais não podem iniciar com o mesmos token não terminal (recursivamente ou não)
    Ex: A -> Aa | Ab | c pode iniciar a partir das três regras 
2. Duas regras de produção iguais não podem produzir o vazio
    Ex: A -> null | a
        A -> null | b
3. Não ser recursivo à esquerda
    Ex: A -> A + F
        F -> F * S
        S -> n

## TRANSFORMATIONS
1. 
```
A -> Aa | Ab | c | d 
=> 
A -> cA' | dA'
A' -> null | aA' | bA' 
```