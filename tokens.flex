%{
    int numChars = 0;
%}

%%

. {
    numChars++;
    printf("%s", yytext);
}

\n {
    numChars++;
    printf("\n");
}

%% 

int main ()
{
    yylex();
    printf("Número_de_caracteres_%d \n", numChars);
}