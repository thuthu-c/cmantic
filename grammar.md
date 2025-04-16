## GRAMMAR

```
PROGRAM -> program NAME begin [ DECL {";" DECK}] end
DECL -> VAR_DECL 
        | PROC_DECL 
        | REC_DECL
VAR_DECL -> var NAME RS_VAR_DECL
RS_VAR_DECL -> ":" TYPE [ := EXP] 
                | := EXP
PROC_DECL -> procedure NAME "(" [PARAMFIELD_DECL {",PARAMFIELD_DECL}] ")" [":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end
REC_DECL -> struct NAME "{" [ PARAMFIELD_DECL { ";" PARAMFIELD_DECL } ] "}"
PARAMFIELD_DECL -> NAME ":" TYPE
STMT_LIST -> [ STMT { ";" STMT} ]

EXP -> AND_EXP EXP_
EXP_ -> ["||" AND_EXP EXP_]
AND_EXP -> NOT_EXP AND_EXP_
AND_EXP_ -> ["&&" NOT_EXP AND_EXP_]
NOT_EXP -> "not" REL_EXP 
            | REL_EXP
REL_EXP -> ADD_EXP REL_EXP_
REL_EXP_ -> [REL_OP ADD_EXP REL_EXP_]
ADD_EXP -> MULT_EXP ADD_EXP_
ADD_EXP_ -> [ADD_OP MULT_EXP ADD_EXP_]
MULT_EXP -> POW_EXP MULT_EXP_
MULT_EXP_ -> [MULT_OP POW_EXP MULT_EXP_]
POW_EXP -> VALUE "^" POW_EXP 
        | VALUE"
VALUE -> LITERAL 
        | VAR_OR_CALL 
        | REF_VAR 
        | DEREF_VAR 
        | "new" NAME 
        | "(" EXP ")"

REF_VAR → ref "(" VAR ")"
DEREF_VAR → deref "(" DE_VAR ")"
DE_VAR → VAR 
        | DEREF_VAR 

VAR → NAME 
    | EXP "." NAME

VAR_OR_CALL -> EXP "." NAME
                | NAME ["(" [ EXP { "," EXP } ] ")"]


REL_OP → ”<” 
        | ”<=” 
        | ”>” 
        | ”>=” 
        | ”=” 
        | ”<>”
ADD_OP → ”+” 
        | ”−”
MULT_OP -> "*" 
        | "/"
LITERAL → FLOAT_LITERAL 
        | INT_LITERAL 
        | STRING_LITERAL 
        | BOOL_LITERAL 
        | null
BOOL_LITERAL → true 
        | false
STMT → ASSIGN_OR_CALL_STMT
        | IF_STMT
        | WHILE_STMT
        | RETURN_STMT
<!-- ASSIGN_STMT → VAR ”:=” EXP 
                | DEREF_VAR ”:=” EXP -->
ASSIGN_OR_CALL_STMT -> DEREF_VAR ”:=” EXP
                        | EXP "." NAME ”:=” EXP
                        | NAME RS_ASSIGN_OR_CALL
RS_ASSIGN_OR_CALL -> ”:=” EXP
                        | "(" [ EXP { "," EXP } ] ")"
IF_STMT → if EXP then STMT_LIST [ else STMT_LIST ] fi
            | unless EXP do STMT_LIST [ else STMT_LIST ] od
            | case EXP of CASE { ";" CASE } "}" [ otherwise STMT_LIST ] esac
CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST
WHILE_STMT → while EXP do STMT_LIST od
RETURN_STMT → return [ EXP ]
<!-- CALL_STMT → NAME "(" [ EXP { "," EXP } ] ")" -->
TYPE → float 
        | int 
        | string 
        | bool 
        | NAME 
        | ref "(" TYPE ")"

```


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
1. Recursão à esquerda
```
A -> Aa | Ab | c | d 
=> 
A -> cA' | dA'
A' -> null | aA' | bA' 
```

2. Fatoração 
```
A -> ab | ac | d
=>
A -> aA' | d
A' -> b | c
```