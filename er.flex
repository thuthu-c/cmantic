%{
    int qtdNumeros=0, nLinhas=0; 
    char nome [10] = string;
%}

NAME [a-zA-Z][a-zA-Z0-9_]
INT_LITERAL [0-9]+

%%

\n                        nLinhas++;
{INT_LITERAL}+            {printf("d_%s\n", yytext); qtdNumeros++;}
{NAME}+                   {printf("d_%s\n", yytext); qtdNumeros++;}

. 

%%


int main ()
{
    yylex();
    printf("#_linhas=%d\n", nLinhas);
    printf("#_numeros=%d\n", qtdNumeros);
}


