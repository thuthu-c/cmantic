# cmantic
Repositório para o projeto de compiladores onde foi implementado um analisador léxico e sintático, além de uma tabela de símbolos e algumas funções utilitárias para manipulação de tipos.

# Executando o parser

```
bison -d parser.y 
flex analyzer.flex
g++ -o parser main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp -lfl
./parser tests/program_1.cmt 
```
