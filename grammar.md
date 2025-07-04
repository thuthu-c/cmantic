## GRAMMAR

### Pure

PROGRAM -> program NAME begin [ DECL {";" DECL}] end
DECL -> VAR_DECL 
        | PROC_DECL 
        | REC_DECL

VAR_DECL -> VAR name ":" TYPE [ ":=" EXP]
        | var NAME ":=" EXP
PROC_DECL -> procedure NAME "(" [PARAMFIELD_DECL {"," PARAMFIELD_DECL}] ")" [":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end
REC_DECL -> struct NAME "{" [ PARAMFIELD_DECL { ";" PARAMFIELD_DECL } ] "}"
PARAMFIELD_DECL -> NAME ":" TYPE
STMT_LIST -> [ STMT { ";" STMT} ]

EXP -> EXP LOG_OP EXP
        | not EXP
        | EXP REL_OP EXP
        | EXP ARITH_OP EXP
        | LITERAL
        | CALL_STMT
        | new NAME
        | VAR
        | REF_VAR
        | DEREF_VAR
        | "(" EXP ")"

REF_VAR → ref "(" VAR ")"
DEREF_VAR -> deref "(" VAR ")"
        | DEREF "(" DEREF_VAR ")"
VAR -> NAME 
        | EXP "." NAME
LOG_OP -> "&&" 
        | "||"

REL_OP -> "<"
        | "<="
        | ">"
        | ">="
        | "="
        | "<>"

ARITH_OP -> "+"
        | "-"
        | "*"
        | "/"
        | "^"

LITERAL -> FLOAT_LITERAL 
        | INT_LITERAL 
        | STRING_LITERAL 
        | BOOL_LITERAL 
        | null
BOOL_LITERAL -> true 
        | false
STMT → ASSIGN_STMT
        | IF_STMT
        | WHILE_STMT
        | RETURN_STMT
        | CALL_STMT
ASSIGN_STMT → VAR ”:=” EXP 
        | DEREF_VAR ”:=” EXP

IF_STMT → if EXP then STMT_LIST [ else STMT_LIST ] fi
            | unless EXP do STMT_LIST [ else STMT_LIST ] od
            | case EXP of CASE { "|" CASE } [ otherwise STMT_LIST ] esac
CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST

WHILE_STMT -> while EXP do STMT_LIST od
RETURN_STMT -> return [ EXP ]
CALL_STMT -> NAME "(" [ EXP { "," EXP } ] ")"
TYPE -> float 
        | int 
        | string 
        | bool 
        | NAME 
        | ref "(" TYPE ")"

### LEX FORMAT

```
PROGRAM -> program NAME begin [ DECL {";" DECK}] end
DECL -> VAR_DECL 
        | PROC_DECL 
        | REC_DECL
VAR_DECL -> var NAME RS_VAR_DECL
RS_VAR_DECL -> ":" TYPE [ := EXP] 
                | := EXP
PROC_DECL -> procedure NAME "(" [PARAMFIELD_DECL {"," PARAMFIELD_DECL}] ")" [":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end
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
ASSIGN_STMT → VAR ”:=” EXP 
        | DEREF_VAR ”:=” EXP
ASSIGN_OR_CALL_STMT -> DEREF_VAR ”:=” EXP
                        | EXP "." NAME ”:=” EXP
                        | NAME RS_ASSIGN_OR_CALL
RS_ASSIGN_OR_CALL -> ”:=” EXP
                        | "(" [ EXP { "," EXP } ] ")"
IF_STMT → if EXP then STMT_LIST [ else STMT_LIST ] fi
            | unless EXP do STMT_LIST [ else STMT_LIST ] od
            | case EXP of CASE { ";" CASE } [ otherwise STMT_LIST ] esac
CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST
WHILE_STMT -> while EXP do STMT_LIST od
RETURN_STMT -> return [ EXP ]
CALL_STMT -> NAME "(" [ EXP { "," EXP } ] ")"
TYPE → float 
        | int 
        | string 
        | bool 
        | NAME 
        | ref "(" TYPE ")"

```

### CRAZY FORMAT


```
PROGRAM -> program NAME begin DECLS end
DECLS -> DECL DECLS_  | ϵ
DECLS_ -> ";" DECLS | ϵ
DECL -> VAR_DECL | PROC_DECL | REC_DECL

VAR_DECL -> var NAME RS_VAR_DECL
RS_VAR_DECL -> ":" TYPE VAR_INIT | ":=" EXP
VAR_INIT -> ":=" EXP | ϵ

PROC_DECL -> procedure NAME "(" PARAMS ")" PROC_RET_DECL
PROC_RET_DECL -> ":" TYPE PROC_BODY | PROC_BODY
PROC_BODY -> begin DECLS_OPT STMT_LIST end
DECLS_OPT -> DECLS in | in | ϵ

REC_DECL -> struct NAME "{" REC_FIELDS "}"
REC_FIELDS -> PARAMFIELD_DECL ";" REC_FIELDS | PARAMFIELD_DECL | ϵ

PARAMFIELD_DECL -> NAME ":" TYPE
PARAMS -> PARAMFIELD_DECL "," PARAMS | PARAMFIELD_DECL | ϵ

STMT_LIST -> STMT ";" STMT_LIST | STMT | ϵ
STMT -> ASSIGN_OR_CALL_STMT 
        | IF_STMT 
        | WHILE_STMT 
        | RETURN_STMT

ASSIGN_OR_CALL_STMT -> DEREF_VAR ":=" EXP 
                     | EXP "." NAME ":=" EXP 
                     | NAME RS_ASSIGN_OR_CALL
RS_ASSIGN_OR_CALL -> ":=" EXP | "(" EXPS ")"
EXPS -> EXP EXPS_ | ϵ
EXPS_ -> "," EXPS | ϵ

IF_STMT -> if EXP then STMT_LIST ELSE_PART fi
         | unless EXP do STMT_LIST ELSE_PART od
         | case EXP of CASES CASE_DEFAULT esac

ELSE_PART -> else STMT_LIST | ϵ
CASES -> CASE ";" CASES | CASE
CASE -> INTERVALS ":" STMT_LIST
INTERVALS -> INTERVAL INTERVALS_
INTERVALS_ -> "," INTERVALS | ϵ
INTERVAL -> INT_LITERAL CASE_RANGE
CASE_RANGE -> ".." INT_LITERAL | ϵ
CASE_DEFAULT -> otherwise STMT_LIST | ϵ

WHILE_STMT -> while EXP do STMT_LIST od
RETURN_STMT -> return EXP_OP
EXP_OP -> EXP | ϵ

EXP -> AND_EXP EXP_
EXP_ -> "||" AND_EXP EXP_ | ϵ
AND_EXP -> NOT_EXP AND_EXP_
AND_EXP_ -> "&&" NOT_EXP AND_EXP_ | ϵ
NOT_EXP -> "not" REL_EXP | REL_EXP
REL_EXP -> ADD_EXP REL_EXP_
REL_EXP_ -> REL_OP ADD_EXP REL_EXP_ | ϵ
ADD_EXP -> MULT_EXP ADD_EXP_
ADD_EXP_ -> ADD_OP MULT_EXP ADD_EXP_ | ϵ
MULT_EXP -> POW_EXP MULT_EXP_
MULT_EXP_ -> MULT_OP POW_EXP MULT_EXP_ | ϵ
POW_EXP -> VALUE "^" POW_EXP | VALUE

VALUE -> LITERAL 
        | VAR_OR_CALL 
        | REF_VAR 
        | DEREF_VAR 
        | "new" NAME 
        | "(" EXP ")"

REF_VAR -> ref "(" VAR ")"
DEREF_VAR -> deref "(" DE_VAR ")"
DE_VAR -> VAR | DEREF_VAR

VAR -> NAME | EXP "." NAME

VAR_OR_CALL -> EXP "." NAME | NAME FUNC_CALL
FUNC_CALL -> "(" EXPS ")" | ϵ

REL_OP -> "<" | "<=" | ">" | ">=" | "=" | "<>"
ADD_OP -> "+" | "-"
MULT_OP -> "*" | "/"

LITERAL -> FLOAT_LITERAL 
         | INT_LITERAL 
         | STRING_LITERAL 
         | BOOL_LITERAL 
         | null

BOOL_LITERAL -> true | false

TYPE -> float | int | string | bool | NAME | ref "(" TYPE ")"

```

### Jsmachines format

```
        PROGRAM -> program NAME begin DECLS end
        DECLS -> DECL DECLS_  
        DECLS -> ''
        DECLS_ -> ";" DECLS 
        DECLS_ -> ''
        DECL -> VAR_DECL 
        DECL -> PROC_DECL 
        DECL -> REC_DECL

        VAR_DECL -> var NAME RS_VAR_DECL
        RS_VAR_DECL -> ":" TYPE VAR_INIT 
        RS_VAR_DECL -> ":=" EXP
        VAR_INIT -> ":=" EXP 
        VAR_INIT -> ''

        PROC_DECL -> procedure NAME "(" PARAMS ")" PROC_RET_DECL
        PROC_RET_DECL -> ":" TYPE PROC_BODY 
        PROC_RET_DECL -> PROC_BODY

        PROC_BODY -> begin DECLS_OPT STMT_LIST end
        DECLS_OPT -> DECL DECLS_ in 
        DECLS_OPT -> ''

        REC_DECL -> struct NAME "{" REC_FIELDS "}"
        REC_FIELDS -> PARAMFIELD_DECL REC_FIELDS_
        REC_FIELDS -> ''
        REC_FIELDS_ -> ";" REC_FIELDS 
        REC_FIELDS_ -> '' 

        PARAMFIELD_DECL -> NAME ":" TYPE
        PARAMS -> PARAMFIELD_DECL PARAMS_ 
        PARAMS -> ''
        PARAMS_ -> "," PARAMS
        PARAMS_ -> '' 

        STMT_LIST -> STMT ";" STMT_LIST_
        STMT_LIST -> STMT
        STMT_LIST -> ''
        STMT_LIST_ -> ";" STMT_LIST_ 
        STMT_LIST_ -> STMT

        EXP -> AND_EXP EXP_
        EXP_ -> "||" AND_EXP EXP_ 


        STMT -> ASSIGN_OR_CALL_STMT  
        STMT -> IF_STMT  
        STMT -> WHILE_STMT  
        STMT -> RETURN_STMT

        ASSIGN_OR_CALL_STMT -> DEREF_VAR ":=" EXP 
        ASSIGN_OR_CALL_STMT -> EXP "." NAME ":=" EXP 
        ASSIGN_OR_CALL_STMT -> NAME RS_ASSIGN_OR_CALL
        RS_ASSIGN_OR_CALL -> ":=" EXP 
        RS_ASSIGN_OR_CALL -> "(" EXPS ")"
        EXPS -> EXP EXPS_ 
        EXPS -> ''
        EXPS_ -> "," EXPS 
        EXPS_ -> ''

        IF_STMT -> if EXP then STMT_LIST ELSE_PART fi
        IF_STMT -> unless EXP do STMT_LIST ELSE_PART od
        IF_STMT -> case EXP of CASES CASE_DEFAULT esac

        ELSE_PART -> else STMT_LIST 
        ELSE_PART -> ''
        CASES -> CASE CASE_
        CASE_ -> ";" CASES
        CASE_ -> ''
        CASE -> INTERVALS ":" STMT_LIST
        INTERVALS -> INTERVAL INTERVALS_
        INTERVALS_ -> "," INTERVALS 
        INTERVALS_ -> ''
        INTERVAL -> INT_LITERAL CASE_RANGE
        CASE_RANGE -> ".." INT_LITERAL 
        CASE_RANGE -> ''
        CASE_DEFAULT -> otherwise STMT_LIST 
        CASE_DEFAULT -> ''

        WHILE_STMT -> while EXP do STMT_LIST od
        RETURN_STMT -> return EXP_OP
        EXP_OP -> EXP 
        EXP_OP -> ''

        EXP -> AND_EXP EXP_
        EXP_ -> "||" AND_EXP EXP_ 
        EXP_ -> ''
        AND_EXP -> NOT_EXP AND_EXP_
        AND_EXP_ -> "&&" NOT_EXP AND_EXP_ 
        AND_EXP_ -> ''
        NOT_EXP -> "not" REL_EXP 
        NOT_EXP -> REL_EXP
        REL_EXP -> ADD_EXP REL_EXP_
        REL_EXP_ -> REL_OP ADD_EXP REL_EXP_ 
        REL_EXP_ -> ''
        ADD_EXP -> MULT_EXP ADD_EXP_
        ADD_EXP_ -> ADD_OP MULT_EXP ADD_EXP_ 
        ADD_EXP_ -> ''
        MULT_EXP -> POW_EXP MULT_EXP_
        MULT_EXP_ -> MULT_OP POW_EXP MULT_EXP_ 
        MULT_EXP_ -> ''
        POW_EXP -> VALUE POW_EXP_
        POW_EXP_ -> "^" POW_EXP
        POW_EXP_ -> ''

        VALUE -> LITERAL 
        VALUE -> VAR_OR_CALL 
        VALUE -> REF_VAR 
        VALUE -> DEREF_VAR 
        VALUE -> "new" NAME 
        VALUE -> "(" EXP ")"

        REF_VAR -> ref "(" VAR ")"
        DEREF_VAR -> deref "(" VAR ")"
        DEREF_VAR -> deref "(" DEREF_VAR ")"

        VAR -> NAME 
        VAR -> EXP "." NAME

        VAR_OR_CALL -> REGISTER ATRIBUTE
        REGISTER -> "(" REGISTER ")"
        REGISTER -> NAME FUNC_CALL
        ATRIBUTE -> "." NAME ATRIBUTE
        ATRIBUTE -> ""
        FUNC_CALL -> "(" EXPS ")"
        FUNC_CALL ->  ''

        REL_OP -> "<" 
        REL_OP -> "<=" 
        REL_OP -> ">" 
        REL_OP -> ">=" 
        REL_OP -> "=" 
        REL_OP -> "<>"
        ADD_OP -> "+" 
        ADD_OP -> "-"
        MULT_OP -> "*" 
        MULT_OP -> "/"

        LITERAL -> FLOAT_LITERAL 
        LITERAL -> INT_LITERAL 
        LITERAL -> STRING_LITERAL 
        LITERAL -> BOOL_LITERAL 
        LITERAL -> null

        BOOL_LITERAL -> true 
        BOOL_LITERAL -> false

        TYPE -> float 
        TYPE -> int 
        TYPE -> string 
        TYPE -> bool 
        TYPE -> NAME 
        TYPE -> ref "(" TYPE ")"

```

### Princeton format

```
        PROGRAM ::= program NAME begin DECLS end
        DECLS ::= DECL DECLS_  
        DECLS ::= ''
        DECLS_ ::= ";" DECLS 
        DECLS_ ::= ''
        DECL ::= VAR_DECL 
        DECL ::= PROC_DECL 
        DECL ::= REC_DECL

        VAR_DECL ::= var NAME RS_VAR_DECL
        RS_VAR_DECL ::= ":" TYPE VAR_INIT 
        RS_VAR_DECL ::= ":=" EXP
        VAR_INIT ::= ":=" EXP 
        VAR_INIT ::= ''

        PROC_DECL ::= procedure NAME "(" PARAMS ")" PROC_RET_DECL
        PROC_RET_DECL ::= ":" TYPE PROC_BODY 
        PROC_RET_DECL ::= PROC_BODY

        PROC_BODY ::= begin DECLS_OPT STMT_LIST end
        DECLS_OPT ::= DECL DECLS_ in 
        DECLS_OPT ::= ''

        REC_DECL ::= struct NAME "{" REC_FIELDS "}"
        REC_FIELDS ::= PARAMFIELD_DECL REC_FIELDS_
        REC_FIELDS ::= ''
        REC_FIELDS_ ::= ";" REC_FIELDS 
        REC_FIELDS_ ::= '' 

        PARAMFIELD_DECL ::= NAME ":" TYPE
        PARAMS ::= PARAMFIELD_DECL PARAMS_ 
        PARAMS ::= ''
        PARAMS_ ::= "," PARAMS
        PARAMS_ ::= '' 

        STMT_LIST ::= STMT STMT_LIST_
        STMT_LIST ::= ''
        STMT_LIST_ ::= ";" STMT_LIST
        STMT_LIST_ ::= ''
        STMT ::= ASSIGN_OR_CALL_STMT  
        STMT ::= IF_STMT  
        STMT ::= WHILE_STMT  
        STMT ::= RETURN_STMT

        ASSIGN_OR_CALL_STMT ::= DEREF_VAR ":=" EXP 
        ASSIGN_OR_CALL_STMT ::= REGISTER ATRIBUTE ":=" EXP''

        EXPS ::= EXP EXPS_ 
        EXPS ::= ''
        EXPS_ ::= "," EXPS 
        EXPS_ ::= ''

        IF_STMT ::= if EXP then STMT_LIST ELSE_PART fi
        IF_STMT ::= unless EXP do STMT_LIST ELSE_PART od
        IF_STMT ::= case EXP of CASES CASE_DEFAULT esac

        ELSE_PART ::= else STMT_LIST 
        ELSE_PART ::= ''
        CASES ::= CASE CASE_
        CASE_ ::= CASES
        CASE_ ::= ''
        CASE ::= INTERVALS ":" STMT_LIST
        INTERVALS ::= INTERVAL INTERVALS_
        INTERVALS_ ::= "," INTERVALS 
        INTERVALS_ ::= ''
        INTERVAL ::= INT_LITERAL CASE_RANGE
        CASE_RANGE ::= ".." INT_LITERAL 
        CASE_RANGE ::= ''
        CASE_DEFAULT ::= otherwise STMT_LIST 
        CASE_DEFAULT ::= ''

        WHILE_STMT ::= while EXP do STMT_LIST od
        RETURN_STMT ::= return EXP

        EXP ::= AND_EXP EXP_
        EXP_ ::= "||" AND_EXP EXP_ 
        EXP_ ::= ''
        AND_EXP ::= NOT_EXP AND_EXP_
        AND_EXP_ ::= "&&" NOT_EXP AND_EXP_ 
        AND_EXP_ ::= ''
        NOT_EXP ::= "not" REL_EXP 
        NOT_EXP ::= REL_EXP
        REL_EXP ::= ADD_EXP REL_EXP_
        REL_EXP_ ::= REL_OP ADD_EXP REL_EXP_ 
        REL_EXP_ ::= ''
        ADD_EXP ::= MULT_EXP ADD_EXP_
        ADD_EXP_ ::= ADD_OP MULT_EXP ADD_EXP_ 
        ADD_EXP_ ::= ''
        MULT_EXP ::= POW_EXP MULT_EXP_
        MULT_EXP_ ::= MULT_OP POW_EXP MULT_EXP_ 
        MULT_EXP_ ::= ''
        POW_EXP ::= VALUE POW_EXP_
        POW_EXP_ ::= "^" POW_EXP
        POW_EXP_ ::= ''

        VALUE ::= LITERAL 
        VALUE ::= VAR_OR_CALL 
        VALUE ::= REF_VAR 
        VALUE ::= DEREF_VAR 
        VALUE ::= "new" NAME 
        VALUE ::= "(" EXP ")"

        REF_VAR ::= ref "(" VAR ")"
        DEREF_VAR ::= deref "(" DE_VAR ")"

        DE_VAR ::= VAR
        DE_VAR ::= DEREF_VAR

        VAR ::= NAME ATRIBUTE

        VAR_OR_CALL ::= REGISTER ATRIBUTE
        REGISTER ::= NAME FUNC_CALL
        ATRIBUTE ::= "." NAME ATRIBUTE
        ATRIBUTE ::= ""
        FUNC_CALL ::= "(" EXPS ")"
        FUNC_CALL ::=  ''

        REL_OP ::= "<" 
        REL_OP ::= "<=" 
        REL_OP ::= ">" 
        REL_OP ::= ">=" 
        REL_OP ::= "=" 
        REL_OP ::= "<>"
        ADD_OP ::= "+" 
        ADD_OP ::= "-"
        MULT_OP ::= "*" 
        MULT_OP ::= "/"

        LITERAL ::= FLOAT_LITERAL 
        LITERAL ::= INT_LITERAL 
        LITERAL ::= STRING_LITERAL 
        LITERAL ::= BOOL_LITERAL 
        LITERAL ::= null

        BOOL_LITERAL ::= true 
        BOOL_LITERAL ::= false

        TYPE ::= float 
        TYPE ::= int 
        TYPE ::= string 
        TYPE ::= bool 
        TYPE ::= NAME 
        TYPE ::= ref "(" TYPE ")"

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