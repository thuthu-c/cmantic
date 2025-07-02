# Esquema de geração de código intermediario

## Tradução das produções

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

## Compreensão 

Determinadas produções deverão ser implementados de forma a gerar determinados textos, um programa de exemplo por exemplo pode ser dado como:

**Cmantic:**:
```
procedure main (int argc, string[] argv)
begin
    var a int := 10 + 10;
    if 21 > a then
        print("a")
    else
        print("b")
    fi;
end
```

Deverá ser traduzido para:

```c
void main (int argc, char* argv[]) {
    int a = 10 + 10;
    bool b = 21 > a;
    if (b) goto end1;
    goto end2;

    end1: 
        print("a");
        return;
    end2:   
        print("b");
        return;
}
```

Dessa forma é necessário ter um controle nas labels e gotos de forma a conseguir manter o fluxo correto do programa. 

É importante compreender direito as **expressões**, dado que toda variável pode ter apenas um operador, então expressões aninhadas terão variáveis "aninhadas", ou seja:
```
var a : int := 15;
if (a > 10 || a < 20)
```

Deve ser traduzido para:
```c
int tmp1 = 15;
int a = tmp1;
int tmp2 = a > 10;
int tmp3 = a < 20;
int tmp4 = tmp2 || tmp3;
if (tmp4)
```
Os padrões aqui são que: A árvore da expressão será aberta por sua associatividade, com as folhas e, posteriormente subindo a árvore, será criado uma variável tmpN para cada operador e seus 2 operandos. Por fim, uma última variável tmpN terá o valor da expressão completa e será usada para atribuições ou para comparações com Ifs.

Para os blocos, nós teremos que traduzir: **while**, **unless**, **case**, **if/else**.

Caso do while:
```
var a : bool := true;
var b : bool := false;
while a || b do
    a = not a
od;
```

```c
bool a = true;
bool b = false;

while_tmp1:
bool tmp1 = a || b;
if (tmp1)
    goto while_tmp2;
goto end_while_tmp1;

while_tmp2:
    a = !a;
    goto while_tmp1;

end_while_tmp1:
...


## Dúvidas
- Nossa linguagem não tem array, necessário adicionar? R: Não é necessário adiconar :check:
- Somente if, ou if else? R: Somente Ifs :check: