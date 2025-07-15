
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

O relatório completo deste trabalho pode ser encontrado neste [arquivo](PDFs/Relatório%20de%20Compiladores%20Unidade%202.pdf)

## Estrutura do Projeto

```
├── analyzer.flex                           # Definições léxicas (Flex)
├── parser.y                                # Definições sintáticas (Bison)
├── main.cpp                                # Ponto de entrada do programa
├── symbol_table.cpp/hpp                    # Implementação da tabela de símbolos
├── type_utils.cpp/hpp                      # Utilitários para manipulação de tipos
├── code_generator.cpp/hpp                  # Funções para geração de código
├── custom_lexer.hpp                        # Classe base para analisadores léxicos
├── run_tests.sh                            # Script para rodar todos os testes
├── run.sh                                  # Script para compilar o programa
├── grammar.md                              # Gramática da linguagem
├── intermediate_representation.md          # Arquivo com interpretações para criação da geração de código
├── tokens.md                               # Lista de tokens terminais
├── tests/                                  # Casos de teste (válidos e inválidos)
├── output/                                 # Códigos de três endereços gerados pelo compilador
├── PDFs/                                   # Pasta com os arquivos PDFs de base e relatórios
└── README.md                               # Este arquivo
```

## Compilação e Execução

### Pré-requisitos

- [Flex](https://github.com/westes/flex)
- [Bison](https://www.gnu.org/software/bison/)
- Compilador C++ (recomendado: g++)

### Compilando via linha de comando

```sh
bison -d parser.y 
flex analyzer.flex
g++ -o cmantic main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp code_generator.cpp -lfl
```

Alternativamente, pode-se usar o script ./run.sh que fará as 3 compilações automaticamente.

O executável será gerado como `cmantic`.

### Executando

```sh
./cmantic <arquivo_de_teste>
```

Exemplo:

```sh
./cmantic tests/valid/caso_aninhado.cmt
```

## Testes

Para rodar todos os testes automaticamente:

```sh
./run_tests.sh
```

O script executa casos de teste válidos e inválidos, exibindo mensagens coloridas para facilitar a leitura dos resultados.

- Testes válidos estão em `tests/valid/`
- Testes inválidos estão em `tests/invalid/`

## Gramática da Linguagem

A gramática completa está documentada em [`grammar.md`](grammar.md). Exemplo de fragmento:

```
PROGRAM -> program NAME begin DECLS end
DECLS -> DECL DECLS_  | ϵ
DECLS_ -> ";" DECLS | ϵ
DECL -> VAR_DECL | PROC_DECL | REC_DECL
...
```

## Atributos

Os atributos utilizados nas produções estão descritos tanto em [`attributes.md`](attributes.md) para verificação de tipos, como em [`Intermediate_representation.md`](Intermediate_representation.md) para a geração de código, incluindo informações sobre escopo, tipos e validação semântica.

---

## Créditos

Projeto desenvolvido para a disciplina de Compiladores.
