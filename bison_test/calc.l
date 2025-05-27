%{
#include "calc.tab.h" // Token definitions from Bison
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]       { return yytext[0]; }
[ \t]         { /* skip whitespace */ }
\n              { return '\n'; }
.               { printf("Unexpected character: %s\n", yytext); }
%%