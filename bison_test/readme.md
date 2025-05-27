
## Running

In the directory that the files are in run:

```terminal
bison -d calc.y         # Generates calc.tab.c and calc.tab.h
flex calc.l             # Generates lex.yy.c
gcc -o calc calc.tab.c lex.yy.c -lfl
```