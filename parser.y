%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
}

%token<ival> INT
%token<fval> FLOAT

%token MAIS MENOS MULT DIVI
%token P_ESQ P_DIR CH_ESQ CH_DIR CO_ESQ CO_DIR EQ AS DIF LE ME M L PONTO_VIRG
%token LINHA T_QUIT

%left MAIS MENOS
%left MULT DIVI

%type<ival> espressao_int
%type<fval> espressao_float

%start main

%%

main: 
	   | main linha
;

linha: LINHA
    | espressao_float LINHA { printf("\tResultado: %f\n", $1); }
    | espressao_int LINHA { printf("\tResultado: %i\n", $1); } 
    | T_QUIT LINHA { printf("Bye!\n"); exit(0); }
;

espressao_float: FLOAT                 		 	{ $$ = $1; }

	  | espressao_int MAIS espressao_float	 { $$ = $1 + $3; }
	  | espressao_int MENOS espressao_float	 { $$ = $1 - $3; }
	  | espressao_int MULT espressao_float 	 { $$ = $1 * $3; }
	  | espressao_int DIVI espressao_float	 { $$ = $1 / $3; }
	  
	  | espressao_float MAIS espressao_int	 { $$ = $1 + $3; }
	  | espressao_float MENOS espressao_int	 { $$ = $1 - $3; }
	  | espressao_float MULT espressao_int 	 { $$ = $1 * $3; }
	  | espressao_float DIVI espressao_int	 { $$ = $1 / $3; }

	  | espressao_float MAIS espressao_float	{ $$ = $1 + $3; }
	  | espressao_float MENOS espressao_float	{ $$ = $1 - $3; }
	  | espressao_float MULT espressao_float 	{ $$ = $1 * $3; }
	  | espressao_float DIVI espressao_float	{ $$ = $1 / $3; }

	  | P_ESQ espressao_float P_DIR		 	{ $$ = $2; }
	  | CH_ESQ espressao_float CH_DIR		{ $$ = $2; }
	  | CO_ESQ espressao_float CO_DIR		{ $$ = $2; }
;

espressao_int: INT							{ $$ = $1; }

	  | MENOS espressao_int					{ $$ = - $2; }
	  | MAIS espressao_int					{ $$ = $2; }
	  | espressao_int MAIS espressao_int	{ $$ = $1 + $3; }
	  | espressao_int MENOS espressao_int	{ $$ = $1 - $3; }
	  | espressao_int MULT espressao_int	{ $$ = $1 * $3; }
	  | espressao_int DIVI espressao_int	{if($3) { $$ = $1 / (float)$3; }
											else {yyerror("Divisao por zero! Tah LOUCO?!");}
											}
	  | P_ESQ espressao_int P_DIR		{ $$ = $2; }
	  | CH_ESQ espressao_int CH_DIR		{ $$ = $2; }
	  | CO_ESQ espressao_int CO_DIR		{ $$ = $2; }
;

%%

int main() {
	yyin = stdin;
	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Erro!: %s\n", s);
	//exit(1);
}