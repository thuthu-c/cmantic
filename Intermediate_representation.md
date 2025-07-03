
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

REF_VAR → ref "(" VAR ")"                       {REF_VAR.value = VAR || //Tradução do Ref}

DEREF_VAR → deref "(" VAR ")"                   {DEREF_VAR.value = VAR || //Tradução do deref}
DEREF_VAR → DEREF "(" DEREF_VAR ")"             {DEREF_VAR.value = DEREF_VAR || //Tradução do deref}

VAR → NAME                                      {VAR.value = NAME}
VAR → EXP "." NAME                              {VAR.value = EXP.NAME}

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

LITERAL → FLOAT_LITERAL      {LITERAL.type = float}   
LITERAL → INT_LITERAL        {LITERAL.type = int}
LITERAL → STRING_LITERAL     {LITERAL.type = string}
LITERAL → BOOL_LITERAL       {LITERAL.type = bool}
LITERAL → null               {LITERAL.type = undefined}

BOOL_LITERAL → true 
BOOL_LITERAL → false

STMT → ASSIGN_STMT
STMT → IF_STMT
STMT → WHILE_STMT
STMT → RETURN_STMT
STMT → CALL_STMT

ASSIGN_STMT → VAR ”:=” EXP                                                  {ASSIGN_STMT.value = (VAR.NAME.name, EXP.type)}
ASSIGN_STMT → DEREF_VAR ”:=” EXP                                            {ASSIGN_STMT.value = (DEREF_VAR.VAR.name, EXP.type)}

IF_STMT → if EXP then STMT_LIST OPTIONAL_ELSE fi                            {IF_STMT.translate = "if (" + EXP.value.name + ") goto " + new_if_label() 
                                                                            + OPTIONAL_ELSE.translate + retrieve_last_if + ":" + STMT_LIST.translate + " goto " + new_endif_label() + retrieve_last_endif + ":"}
OPTIONAL_ELSE → ϵ | else STMT_LIST                                          {IfNotEmpty: OPTIONAL_ELSE.translate = "goto " + new_else + retrieve_else + ": " +}


IF_STMT → unless EXP do STMT_LIST [ else STMT_LIST ] od                     {// Tradução do unless}
IF_STMT → case EXP of CASE { "|" CASE } [ otherwise STMT_LIST ] esac        {// Tradução do case}

CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST

WHILE_STMT → while EXP do STMT_LIST od                                      {// Tradução do while}

RETURN_STMT → return [ EXP ]                                                {// Tradução do return}           

CALL_STMT → NAME "(" [ EXP { "," EXP } ] ")"                                {CALL_STMT.value = NAME.value ||
                                                                            // Tradução da chamada de uma procedure }

TYPE → float                                                                {TYPE.type = float}
TYPE → int                                                                  {TYPE.type = int}
TYPE → string                                                               {TYPE.type = string}
TYPE → bool                                                                 {TYPE.type = bool}
TYPE → NAME                                                                 {TYPE.type = NAME.value.name}
TYPE → ref "(" TYPE ")"                                                     {TYPE.type = TYPE_1}


#### Lista de operações
+: Concatenação de strings
IfNotEmpty: Se a produção não resultou em ϵ

#### Lista de funções
new_if: Gera uma nova label para um bloco if
new_else: Gera uma nova label para um bloco else
new_endif: Gera uma nova label para o fim de um bloco if
retrieve_last_if: Recupera a última label gerada para blocos if
retrieve_last_endif: Recupera a última label gerada para o fim de blocos if

#### Lista de Atributos por produção

| Simbolo    | Atributo | Descrição
| -------- | ------- | ------- |
| LITERAL | type | Tipo |
| EXP | value | Tupla (name, type) |
| CALL_STMT | value | Tupla (name, type) |
| ASSIGN_STMT | value | Tupla (name, type) |
| IF_STMT | translate | String resultante da tradução |
| OPTIONAL_ELSE | translate | String resultante da tradução |
| TYPE | type | Tipo |
| TYPE | translate | Texto de tradução |
| VAR | value | Tupla (name, type) |
| REF_VAR | value | Tupla (name, type) |
| DEREF_VAR | value | Tupla (name, type) |
| NAME | value | Tupla (name, type) |


#### Descrição dos atributos

## Compreensão da geração de código intermediário

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
    bool tmp1 = 21 > a;
    if (tmp1) goto end1;
    goto end2;

    end1: 
        print("a");
        return;
    end2:   
        print("b");
        return;
}
```

a = b op c

Dessa forma é necessário ter um controle nas labels e gotos de forma a conseguir manter o fluxo correto do programa. 

#### Caso das Expressões
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

####  Caso do while:
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
```

Aqui é possível notar primeiramente que deve haver uma label antes de todo o bloco de repetição e a variável de avaliação deve ser a primeira linha deste bloco. Desta forma sempre será possível reavaliar se o while ainda deve executar. Em seguida temos dois casos: o label onde adentrou o while, e o label quando o while foi finalizado pulando o bloco de código interno do while.

####  Caso do unless:

```
var a : bool := true;
var b : bool := false;
unless a || b do
    a = not a;
od;
```

```c
bool a = true;
bool b = false;

bool tmp1 = a || b;
bool tmp2 = !tmp1; // Unless se dá pela negação da expressão, uma traduação para "a não ser que <expr> seja verdade, então ..."
if (tmp2)
    goto unless_tmp1;
goto end_unless_tmp1;

unless_tmp1:
    bool tmp3 = !a;
    a = tmp3;

end_unless_tmp1:
...
```

No caso do unless, é necessário uma nova variável temporária para fazer a negação da expressão do if, de resto segue o mesmo padrão.

#### Caso do case

```cmantic
var idade : int = 5;
case idade of
    0..12: return "Criança" |
    13..17: return "Adolescente"
    otherwise: return "Idoso"
esac
```

```c
int tmp0 = 5;
int idade = tmp0;

int tmp1 = 0;
int tmp2 = 12;
int tmp11 = idade >= tmp1;
int tmp12 = idade <= tmp2;
int tmp13 = tmp11 || tmp12;
if (tmp13) goto case_tmp1;

int tmp3 = 13;
int tmp4 = 17;
int tmp31 = idade >= tmp3;
int tmp32 = idade <= tmp4;
int tmp33 = tmp31 || tmp32;
if (tmp33) goto case_tmp2;

goto case_otherwise_tmp1;

case_tmp1:
    char* tmpc1 = "Criança";
    char* return_tmp1 = tmpc1;
    goto end_case_tmp1

case_tmp2:
    char* tmpc2 = "Adolescente";
    char* return_tmp2 = tmpc2;
    goto end_case_tmp1

case_otherwise_tmp1:
    char* tmpc3 = "Idoso";
    char* return_tmp3 = tmpc3;
    goto end_case_tmp1


end_case_tmp1:
...

```

#### Caso do procedure
```cmantic
procedure name (x :int, y : int) : int
begin
    var z : int = x + y;
    return z
end

var call : int = name(10, 20)
```

```c
int tmp1 = 10;
int tmp2 = 20;
goto name;
end_name:
...

name:
    int tmp23238 = tmp1 + tmp2;
    int z = tmp23238;
    int call = z; // Referente ao retorno
    goto end_name;
```

#### Caso do if/else
```cmantic
var a : bool = true;
var b : bool = false;
 if a || b then
    return a && b
else
    return a && b
fi;
```

```c
int tmp1 = true;
int tmp2 = false;
int a = tmp1;
int b = tmp2;
int tmp3 = a || b;

if (tmp3)
    goto name;
goto else1;
else_tmp1:
    ...
    goto end_if_tmp1;
if_tmp1:
    ...
    goto end_if_tmp1;

end_if_tmp1:
...

```

## Dúvidas
- Nossa linguagem não tem array, necessário adicionar? R: Não é necessário adiconar :check:
- Somente if, ou if else? R: Somente Ifs :check: