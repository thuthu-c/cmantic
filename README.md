
# Cmantic

Este repositório contém a implementação de um compilador didático para uma linguagem fictícia, incluindo analisador léxico, sintático, tabela de símbolos e utilitários para manipulação de tipos.

## Sumário

- [Visão Geral](#visão-geral)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Compilação e Execução](#compilação-e-execução)
- [Testes](#testes)
- [Principais Arquivos](#principais-arquivos)
- [Gramática da Linguagem](#gramática-da-linguagem)
- [Atributos Sintáticos](#atributos-sintáticos)

---

## Visão Geral

O projeto implementa as etapas iniciais de um compilador:

- **Análise Léxica:** Utilizando Flex.
- **Análise Sintática:** Utilizando Bison (parser LALR) e também um parser recursivo descendente.
- **Tabela de Símbolos:** Gerenciamento de variáveis, procedimentos e registros.
- **Verificação de Tipos:** Checagem de tipos em expressões e declarações.

## Estrutura do Projeto

```
├── analyzer.flex           # Definições léxicas (Flex)
├── parser.y               # Definições sintáticas (Bison)
├── main.cpp               # Ponto de entrada do programa
├── symbol_table.cpp/hpp   # Implementação da tabela de símbolos
├── type_utils.cpp/hpp     # Utilitários para manipulação de tipos
├── custom_lexer.hpp       # Classe base para analisadores léxicos
├── project_1/             # Implementações alternativas (ex: parser recursivo)
├── tests/                 # Casos de teste (válidos e inválidos)
├── run_tests.sh           # Script para rodar todos os testes
├── build/                 # Diretório de build (gerado pelo CMake)
├── bison_test/            # Exemplos e testes de Bison/Flex
├── PDFs/                  # Materiais de apoio e especificação
├── grammar.md             # Gramática da linguagem
├── attributes.md          # Atributos sintáticos e semânticos
├── tokens.md              # Lista de tokens terminais
└── README.md              # Este arquivo
```

## Compilação e Execução

### Pré-requisitos

- [Flex](https://github.com/westes/flex)
- [Bison](https://www.gnu.org/software/bison/)
- [CMake](https://cmake.org/)
- Compilador C++ (recomendado: g++)

### Compilando via linha de comando

```sh
bison -d parser.y 
flex analyzer.flex
g++ -o parser main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp -lfl
```

### Compilando via CMake

```sh
cd project_1
mkdir -p build
cd build
cmake ..
make
```

O executável será gerado como `parser` (ou `syntax_analyzer` via CMake).

### Executando

```sh
./parser <arquivo_de_teste>
```

Exemplo:

```sh
./parser tests/valid/program_var_decl.cmt
```

## Testes

Para rodar todos os testes automaticamente:

```sh
./run_tests.sh
```

O script executa casos de teste válidos e inválidos, exibindo mensagens coloridas para facilitar a leitura dos resultados.

- Testes válidos estão em `tests/valid/`
- Testes inválidos estão em `tests/invalid/`

## Principais Arquivos

- [`analyzer.flex`](analyzer.flex): Definições dos padrões léxicos.
- [`parser.y`](parser.y): Gramática e regras semânticas do parser.
- [`symbol_table.hpp`](symbol_table.hpp): Estruturas e funções para tabela de símbolos.
- [`type_utils.hpp`](type_utils.hpp): Funções auxiliares para tipos.
- [`project_1/recursive_parser.hpp`](project_1/recursive_parser.hpp): Parser recursivo descendente (alternativo).
- [`run_tests.sh`](run_tests.sh): Script de automação de testes.
- [`grammar.md`](grammar.md): Gramática formal da linguagem.
- [`attributes.md`](attributes.md): Descrição dos atributos sintáticos e semânticos.
- [`tokens.md`](tokens.md): Lista de tokens reconhecidos pelo léxico.

## Gramática da Linguagem

A gramática completa está documentada em [`grammar.md`](grammar.md). Exemplo de fragmento:

```
PROGRAM -> program NAME begin DECLS end
DECLS -> DECL DECLS_  | ϵ
DECLS_ -> ";" DECLS | ϵ
DECL -> VAR_DECL | PROC_DECL | REC_DECL
...
```

## Atributos Sintáticos

Os atributos utilizados nas produções estão descritos em [`attributes.md`](attributes.md), incluindo informações sobre escopo, tipos e validação semântica.

---

## Créditos

Projeto desenvolvido para a disciplina de Compiladores.
