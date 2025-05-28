%require "3.2"
%language "c++"

%code requires {
    #include <string>
    #include "custom_lexer.hpp"
}

%parse-param {CustomLexer &lexer}

%header

%code {
    #define yylex lexer.yylex
}

%union {
	int ival;
	float fval;
	std::string sval;
}

%token<ival> INT_LITERAL
%token<fval> FLOAT_LITERAL
%token<sval> STRING_LITERAL 
%token A_NAME A_LINE

%token A_PROGRAM A_BEGIN A_END A_PROCEDURE A_VAR
%token A_IF A_THEN A_ELSE A_FI A_WHILE A_DO A_OD A_RETURN A_UNLESS A_CASE A_OF A_ESAC A_OTHERWISE 
%token A_TRUE A_FALSE A_FLOAT A_INT A_STRING A_BOOL A_NULL A_STRUCT
%token A_IN A_NOT A_NEW A_REF A_DEREF
%token ';' ':' ',' '[' ']' '{' '}' '(' ')' '<' '>'  '=' '+' '-' '*' '/' '^' '.'
%token A_ASSIGN A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL A_DIFFERENT A_EQUAL A_OR_LOGIC A_AND_LOGIC A_RANGE

%left '+' '-'
%left '*' '/'
%right '^'

/* %type<ival> espressao_int
%type<fval> espressao_float */

%start main

%%
main:
      A_PROGRAM A_END // Exemplo de regra para 'main'
    | /* main pode ser vazio, se permitido */
    ;
%%

int main() {
	yyin = stdin;
	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}