%{
    #include <stdio.h>
    #include <stdlib.h>

    int qtdNumeros=0, nLinhas=0;
%}

%option noyywrap

NAME [a-zA-Z][a-zA-Z0-9_]*
SINGLE_COMMENT "//".*
MULTI_COMMENT "(\*"([^*]|\*+[^)*])*\*+")"
INT_LITERAL [0-9]+
STRING_LITERAL \"([^\\\"\n]|\\.)*\"
BOOL_LITERAL "true" | "false"

%%

{INT_LITERAL} {
    printf("An integer: %s\n", yytext);
}

"true"|"false" {
    printf("A boolean: %s\n", yytext);
}

{STRING_LITERAL} {
    printf("A string: %s\n", yytext);
}

{NAME} {
    printf("A name: %s\n", yytext);
}

{SINGLE_COMMENT} {
    printf("A comment: %s\n", yytext);
}

{MULTI_COMMENT} {
    printf("This is a multi line comment: %s\n", yytext);
}

\n    { nLinhas++; }

.     { /* Ignora outros caracteres */ }

%%

int main (int argc, char **argv)
{
    ++argv,--argc;
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" ); 
    else 
        yyin = stdin;

    yylex();
    return 0;
}
