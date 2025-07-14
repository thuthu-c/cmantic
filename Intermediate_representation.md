
# Esquema de geração de código intermediario

## Tradução das produções

PROGRAM → program NAME begin [ DECL {";" DECL}] end {PROGRAM.translate = "int CONTROL; + void main(void) {" + build_control_procedure() 
                                                    + ForEach(DECL): DECL.translate + "}"
                                                    }

DECL → VAR_DECL 
DECL → PROC_DECL 
DECL → REC_DECL

VAR_DECL → var NAME ":" TYPE [ ":=" EXP]            {IfEmpty: VAR_DECL.translate = TYPE.lexeme + NAME.lexeme || VAR_DECL.value = (NAME, TYPE)
                                                    IfNotEmpty: IfTrue: TYPE == EXP.value.type then VAR_DECL.translate = TYPE.lexeme + NAME.lexeme + " = " 
                                                    + EXP.name + ";"
                                                    || VAR_DECL.value = (NAME, TYPE) 
                                                    || emit(VAR_DECL.translate)
                                                    }

VAR_DECL → var NAME ":=" EXP                        {IfTrue: VAR_DECL.translate = EXP.value.type + NAME.lexeme + " = " + EXP.name 
                                                    || VAR_DECL.value = (NAME, EXP.value.type)
                                                    || emit(VAR_DECL.translate)
                                                    }

PROC_DECL → procedure NAME "(" [PARAMFIELD_DECL {"," PARAMFIELD_DECL}] ")" 
[":" TYPE] begin [[DECL {";" DECL}] in ] STMT_LIST end      {proc_name := new_label() 
                                                            || create_procedure_scope(proc_name)
                                                            || PROC_DECL.translate = proc_name ":" + forEach(DECL): DECL.translate + STMT_LIST.translate 
                                                            + "goto controlProcedure;"
                                                            || emit(PROC_DECL.translate)
                                                            }

REC_DECL → struct NAME "{" [ PARAMFIELD_DECL { ";" PARAMFIELD_DECL } ] "}"      {IfNotEmpety: REC_DECL.translate = "typedef struct {" 
                                                                                + ForEach(PARAMFIELD_DECL):PARAMFIELD_DECL.translate + "} ;"
                                                                                IfEmpty: REC_DECL.translate = "" // Não é permitido Structs vazias no C
                                                                                || emit(REC_DECL.translate)
                                                                                } 

PARAMFIELD_DECL → NAME ":" TYPE                     {PARAMFIELD_DECL.translate = TYPE.lexeme + NAME.lexeme}

STMT_LIST → [ STMT { ";" STMT} ]

EXP → EXP1 LOG_OP EXP2                              {IfTrue: EXP1.value.type == EXP2.value.type then EXP.value.type = EXP1.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + EXP1.value.name + LOG_OP.lexeme + EXP2.value.name + ";" 
                                                    || EXP.value.name = t1
                                                    }

EXP → not EXP1                                      {EXP.value.type = EXP1.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = !" + EXP1.value.name + ";"
                                                    || EXP.value.name = t1
                                                    }

EXP → EXP1 REL_OP EXP2                              {IfTrue: EXP1.value.type == EXP2.value.type then EXP.value.type = EXP1.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + EXP1.value.name + REL_OP.lexeme + EXP2.value.name + ";" 
                                                    || EXP.value.name = t1
                                                    }

EXP → EXP1 ARITH_OP EXP2                            {IfTrue: EXP1.value.type == EXP2.value.type then EXP.value.type = EXP1.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + EXP1.value.name + ARITH_OP.lexeme + EXP2.value.name + ";"
                                                    || EXP.value.name = t1
                                                    }

EXP → LITERAL                                       {EXP.value.type = Literal.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + Literal.lexeme + ";"
                                                    || EXP.value.name = t1
                                                    }
                                                    
EXP → CALL_STMT                                     {EXP.value.type = CALL_STMT.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + CALL_STMT.scope.return_label + ";"
                                                    || EXP.value.name = t1
                                                    }

EXP → new NAME                                      {EXP.value.type = NAME.value.type || t1 := new_name()
                                                    || EXP.translate = "{};" // Cria uma struct vazia
                                                    || EXP.value.name = t1
                                                    }

EXP → VAR                                           {EXP.value.type = VAR.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + VAR.lexeme
                                                    || EXP.value.name = t1
                                                    }

EXP → REF_VAR                                       {EXP.value.type = REF_VAR.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + REF_VAR.translate
                                                    || EXP.value.name = t1
                                                    }

EXP → DEREF_VAR                                     {EXP.value.type = DEREF_VAR.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = " + DEREF_VAR.translate
                                                    || EXP.value.name = t1
                                                    }

EXP → "(" EXP1 ")"                                  {EXP.value.type = EXP1.value.type || t1 := new_name()
                                                    || EXP.translate = EXP.value.type + t1 + " = (" + EXP1.value.name + ")"
                                                    || EXP.value.name = t1
                                                    }

REF_VAR → ref "(" VAR ")"                       {REF_VAR.value = VAR || 
                                                REF_VAR.translate = "&" + VAR.value.name
                                                }

DEREF_VAR → deref "(" VAR ")"                   {DEREF_VAR.value = VAR.value || 
                                                DEREF_VAR.translate = "*" + VAR.value.name}
DEREF_VAR → DEREF "(" DEREF_VAR1 ")"            {DEREF_VAR.value = DEREF_VAR1.value || 
                                                DEREF_VAR.translate = "*" + DEREF_VAR1.translate}

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

ASSIGN_STMT → VAR ”:=” EXP                                                  {ASSIGN_STMT.value = (VAR.value.name, EXP.type)
                                                                            || ASSING_STMT.translate = VAR.value.name + " = " + EXP.translate + ";"
                                                                            || emit(ASSING_STMT.translate)
                                                                            }

ASSIGN_STMT → DEREF_VAR ”:=” EXP                                            {ASSIGN_STMT.value = (DEREF_VAR.Value.name, EXP.type)
                                                                            || ASSING_STMT.translate = "*" + VAR.value.name + " = " + EXP.translate + ";"
                                                                            || emit(ASSING_STMT.translate)
                                                                            }

IF_STMT → if EXP then STMT_LIST OPTIONAL_ELSE fi                            { l1 := new_label() || l2 := new_label() 
                                                                            || IF_STMT.translate = "if (" + EXP.value.name + ") goto " + l1 + ";"
                                                                            + OPTIONAL_ELSE.translate + "goto " + l2 + ";" + l1 + ":" + STMT_LIST.translate + " goto " + l2 + ";" + l2 + ":"
                                                                            || emit(IF_STMT.translate)} // l1 é o bloco verdadeiro, l2 é o fim do if

OPTIONAL_ELSE → ϵ | else STMT_LIST                                          {IfNotEmpty: l1 := new_label()
                                                                            || OPTIONAL_ELSE.translate = "goto " + l1 + ";" + 
                                                                            l1 +  ": " + STMT_LIST.translate
                                                                            } // l1 é o bloco do else


IF_STMT → unless EXP do STMT_LIST OPTIONAL_ELSE od                          { t1 := new_name()  || l1 := new_label() || l2 := new_label() ||
                                                                            IF_STMT.translate = EXP.value.type + t1 " = !" + EXP.value.name + ";" +
                                                                            "if (" + EXP.value.name + ") goto " + l1 + ";" + OPTIONAL_ELSE.translate + "goto" + l2 + ";" + l1 + ":" STMT_LIST.translate + "goto " + l2 + ";" + l2 + ":"
                                                                            || emit(IF_STMT.translate)
                                                                            } // l1 é bloco verdadero, l2 é o fim do if

IF_STMT → case EXP of CASE { "|" CASE } [ otherwise STMT_LIST ] esac        {// Tradução do case}

CASE → INT_LITERAL [ "." "." INT_LITERAL ] { "," INT_LITERAL [ "." "." INT_LITERAL ] } ":" STMT_LIST

WHILE_STMT → while EXP do STMT_LIST od                                      { l1 := new_label() || l2 := new_label() || l3 := new_label()
                                                                            || WHILE_STMT.translate = l1 + ":" + EXP.translate + "if ("  
                                                                            + EXP.value.name ") goto " + l2 + ";" 
                                                                            + "goto " + l3 + "; " + l2 + ":" + 
                                                                            STMT_LIST.translate + "goto " + l1 + ";" + l3 + ":"
                                                                            || emit(WHILE_STMT.translate)}

RETURN_STMT → return [ EXP ]                                                {IfNotEmpty: RETURN_STMT.translate = "return " + EXP.value.name + ";" 
                                                                            IfEmpty: RETURN_STMT.translate = "return " + ";" 
                                                                            || emit(RETURN_STMT.translate)
                                                                            }           

CALL_STMT → NAME "(" [ EXP { "," EXP } ] ")"                                {CALL_STMT.scope := find_scope(NAME)  || CALL_STMT.value.type = NAME.value.type 
                                                                            || return_point := new_label() 
                                                                            || call_count := new_call_count() || new_call(call_count, return_point)
                                                                            || CALL_STMT.translate = ForEach(EXP): scope.params[idx].name = EXP.name + ";" + "CONTROL = " + call_count + ";" + "goto " + scope.proc_name + ";" + return_point + ":"
                                                                            || emit(CALL_STMT.translate)
                                                                            } // Efetivamente, a tradução está atribuindo os parâmetros da função a partir dos labels criado para os parâmetrose depois fazendo um goto para o label do nome da função. Em seguida cria o label de retorno.

TYPE → float                                                                {TYPE.type = float || TYPE.translate = "float"}
TYPE → int                                                                  {TYPE.type = int || TYPE.translate = "int"}
TYPE → string                                                               {TYPE.type = string || TYPE.translate = "char*"}
TYPE → bool                                                                 {TYPE.type = bool || TYPE.translate = "bool"}
TYPE → NAME                                                                 {TYPE.type = NAME.value.type || TYPE.translate = NAME}
TYPE → ref "(" TYPE1 ")"                                                    {TYPE.type = TYPE_1 || TYPE.translate = TYPE1.type + "*"}


#### Lista de operações
|| Pipe de operações realizadas
+: Concatenação de strings
IfEmpty: Se a produção opcional resultou em ϵ
IfNotEmpty: Se a produção opcional não resultou em ϵ
IfTrue: Se o resultado da comparação retornar verdadeiro

#### Lista de funções
new_name: Gera um novo nome para variáveis {std::string name = "t" + GLOBAL_COUNT}
new_label: Gera uma nova label (push) {std::string name = "l" + GLOBAL_COUNT; label_stack.push(name)}
retrieve_label: Recupera a última label da pilha (pop) {label_stack.pop()}
emit: Escreve o texto para o código intermediário {file << translate.str()}

// Funções de procedimentos
find_type: Se TYPE foi especificado, retorna type; Senão, busca o RETURN_STMT para inferir o tipo
find_Scope: Busca o escopo pelo nome
new_call: Adiciona na call_stack uma nova chamada com um id da chamada e o label de retorno, a call_stack se tornará o controlProcedure da forma:
controlProcedure:
    if (CONTROL == 1) goto l1;
    if (CONTROL == 2) goto l2;
build_control_procedure: Irá traduzir as chamadas armazenadas no call_stack para texto similar ao acima
A call stack é do tipo Stack<Pair<int, string>>

create_procedure_scope: Irá criar um escopo do tipo Map<String1, Vector<String2, String3..n-1, Stringn> onde:
String1: É o nome original da função no código CMANTIC
String2: É a label criada para a função
String3..n-1: Nomes dos parâmetros criados via new_name() (Ou seja, são os nomes do código intermediário)
Stringn: É o nome da variável de retorno criado via new_name() (Ou seja, o nome do código intermediário)

#### Lista de Atributos por produção

| Simbolo    | Atributo | Descrição
| -------- | ------- | ------- |
| LITERAL | type | Tipo |
| PROGRAM | translate | String resultante da tradução |
| VAR_DECL | value | Tupla (name, type) |
| VAR_DECL | translate | String resultante da tradução |
| REC_DECL | translate | String resultante da tradução |
| PROC_DECL | translate | String resultante da tradução |
| PARAMFIELD_DECL | translate | String resultante da tradução |

| EXP | value | Tupla (name, type) |
| EXP | translate | String resultante da tradução |

| IF_STMT | translate | String resultante da tradução |
| CALL_STMT | scope | Escopo da função chamada |
| CALL_STMT | value | Tupla (name, type) |
| CALL_STMT | translate | String resultante da tradução |
| ASSIGN_STMT | value | Tupla (name, type) |
| ASSIGN_STMT | translate | String resultante da tradução |
| WHILE_STMT | translate | String resultante da tradução |
| RETURN_STMT | translate | String resultante da tradução |
| OPTIONAL_ELSE | translate | String resultante da tradução |

| TYPE | type | Tipo |
| TYPE | translate | Texto de tradução |
| VAR | value | Tupla (name, type) |
| REF_VAR | value | Tupla (name, type) |
| REF_VAR | translate | String resultante da tradução |
| DEREF_VAR | value | Tupla (name, type) |
| DEREF_VAR | translate | String resultante da tradução |
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

```c++
// yacc
std::string block_label = new_label();
std::string while_label = new_label();
std::string end_while_label = new_label();

std::sstream translate;
translate << block_label << ":" << exp.translate << "if (" << exp.value.name << ") goto " << while_label << "; goto " << end_while_label << "; " << while_label ": " << STMT_LIST.translate << "goto " << block_label << "; " << end_while_label;
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

#### Multiplas chamdas para procedure
```c
procedure soma (a: int, b: int) : int
begin
    resultado = a + b;
    return resultado
end


char* control = //retreive_new_end_call;

controlProcedure:
    // Translate da pilha de "controls"
    if (control == "end_soma1") goto end_soma1;
    if (control == "end_soma2") goto end_soma2;

soma:
    tmp3 = soma_a + soma_b;
    return_soma = tmp3;
    goto controlProcedure;


int soma_a = 10;
int soma_b = 20;
goto soma;
end_soma1: // new_end_call(); controls_stack.push(retreve_last_end_call);
int call = return_soma;
...

int x3 = 10;
int x4 = 20;
goto soma;
end_soma2: // new_end_call(); controls_stack.push(retreve_last_end_call);
```

## Dúvidas
- Nossa linguagem não tem array, necessário adicionar? R: Não é necessário adiconar :check:
- Somente if, ou if else? R: Somente Ifs :check: