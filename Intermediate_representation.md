# Esquema de geração de código intermediario

PROGRAM → program NAME begin [ DECL {";" DECL}] end

DECL → VAR_DECL 
DECL → PROC_DECL 
DECL → REC_DECL

VAR_DECL → VAR name ":" TYPE [ ":=" EXP]
VAR_DECL → var NAME ":=" EXP

PROC_DECL → procedure NAME "(" [PARAMFIELD_DECL {"," PARAMFIELD_DECL}] ")" [":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end

REC_DECL → struct NAME "{" [ PARAMFIELD_DECL { ";" PARAMFIELD_DECL } ] "}"

PARAMFIELD_DECL → NAME ":" TYPE

STMT_LIST → [ STMT { ";" STMT} ]

EXP → EXP LOG_OP EXP
EXP → not EXP
EXP → EXP REL_OP EXP
EXP → EXP ARITH_OP EXP
EXP → LITERAL
EXP → CALL_STMT
EXP → new NAME
EXP → VAR
EXP → REF_VAR
EXP → DEREF_VAR
EXP → "(" EXP ")"

REF_VAR → ref "(" VAR ")"

DEREF_VAR → deref "(" VAR ")"
DEREF_VAR → DEREF "(" DEREF_VAR ")"

VAR → NAME 
VAR → EXP "." NAME

LOG_OP → "&&" 
LOG_OP → "||"

REL_OP → "<"
REL_OP → "<="
REL_OP → ">"
REL_OP → ">="
REL_OP → "="
REL_OP → "<>"

ARITH_OP → "+"
ARITH_OP → "-"
ARITH_OP → "*"
ARITH_OP → "/"
ARITH_OP → "^"

LITERAL → FLOAT_LITERAL 
LITERAL → INT_LITERAL 
LITERAL → STRING_LITERAL 
LITERAL → BOOL_LITERAL 
LITERAL → null

BOOL_LITERAL → true 
BOOL_LITERAL → false

STMT → ASSIGN_STMT
STMT → IF_STMT
STMT → WHILE_STMT
STMT → RETURN_STMT
STMT → CALL_STMT

ASSIGN_STMT → VAR ”:=” EXP 
ASSIGN_STMT → DEREF_VAR ”:=” EXP

IF_STMT → if EXP then STMT_LIST [ else STMT_LIST ] fi
IF_STMT → unless EXP do STMT_LIST [ else STMT_LIST ] od
IF_STMT → case EXP of CASE { "|" CASE } [ otherwise STMT_LIST ] esac

CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST

WHILE_STMT → while EXP do STMT_LIST od

RETURN_STMT → return [ EXP ]

CALL_STMT → NAME "(" [ EXP { "," EXP } ] ")"

TYPE → float 
TYPE → int 
TYPE → string 
TYPE → bool 
TYPE → NAME 
TYPE → ref "(" TYPE ")"