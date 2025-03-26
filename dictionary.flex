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
FLOAT_LITERAL [0-9]+"."[0-9]+([Ee][-+][0-9]{2})?

%%

{INT_LITERAL} {
    printf("An integer: %s\n", yytext);
}

{FLOAT_LITERAL} {
    printf("A float: %s\n", yytext);
}

"if" printf( "A if: %s\n", yytext );

"then" printf( "A then: %s\n", yytext );

"else" printf( "A else: %s\n", yytext );

"fi" printf( "A fi: %s\n", yytext );

"while" printf( "A while: %s\n", yytext );

"do" printf( "A do: %s\n", yytext );

"od" printf( "A od: %s\n", yytext );

"return" printf( "A return: %s\n", yytext );

"unless" printf( "A unless: %s\n", yytext );

"case" printf( "A case: %s\n", yytext );

"of" printf( "A of: %s\n", yytext );

"esac" printf( "A esac: %s\n", yytext );

"otherwise" printf( "A otherwise: %s\n", yytext );

"true" printf("A true: %s\n", yytext);

"false" printf("A false: %s\n", yytext);

"float" printf("A float: %s\n", yytext );

"int" printf("A int: %s\n", yytext );

"string" printf("A string: %s\n", yytext );

"bool" printf("A bool: %s\n", yytext );

"null" printf("A null: %s\n", yytext );

"program" printf("A program: %s\n", yytext );

"begin" printf("A begin: %s\n", yytext );

"end" printf("A end: %s\n", yytext );

"var" printf("A var: %s\n", yytext );

"procedure" printf("A procedure: %s\n", yytext );

"struct" printf("A struct: %s\n", yytext );

"in" printf("A in: %s\n", yytext );

"not" printf("A not: %s\n", yytext );

"new" printf("A new: %s\n", yytext );

"ref" printf("A ref: %s\n", yytext );

"deref" printf("A deref: %s\n", yytext );

";" printf("A ;: %s\n", yytext );

":" printf("A :: %s\n", yytext );

"," printf("A ,: %s\n", yytext );

":=" printf("A :=: %s\n", yytext );

"." printf("A .: %s\n", yytext );

"[" printf("A [: %s\n", yytext );

"]" printf("A ]: %s\n", yytext );

"(" printf("A (: %s\n", yytext );

")" printf("A ): %s\n", yytext );

"{" printf("A {: %s\n", yytext );

"}" printf("A }: %s\n", yytext );

"||" printf("A ||: %s\n", yytext );

"&&" printf("A &&: %s\n", yytext );

"<" printf("A <: %s\n", yytext );

"<=" printf("A <=: %s\n", yytext );

">" printf("A >: %s\n", yytext );

">=" printf("A >=: %s\n", yytext );

"=" printf("A =: %s\n", yytext );

"<>" printf("A <>: %s\n", yytext );

"+" printf("A +: %s\n", yytext );

"-" printf("A -: %s\n", yytext );

"*" printf("A *: %s\n", yytext );

"/" printf("A /: %s\n", yytext );

"^" printf("A ^: %s\n", yytext );

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
