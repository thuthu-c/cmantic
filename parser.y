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
%token<sval> A_NAME 
%token A_LINE STRING_LITERAL

%token A_PROGRAM A_BEGIN A_END A_PROCEDURE A_VAR
%token A_IF A_THEN A_ELSE A_FI A_WHILE A_DO A_OD A_RETURN A_UNLESS A_CASE A_OF A_ESAC A_OTHERWISE 
%token A_TRUE A_FALSE A_FLOAT A_INT A_STRING A_BOOL A_NULL A_STRUCT
%token A_IN A_NOT A_NEW A_REF A_DEREF A_U_MINUS A_U_PLUS
%token ';' ':' ',' '[' ']' '{' '}' '(' ')' '<' '>'  '=' '+' '-' '*' '/' '^' '.' '|'
%token A_ASSIGN A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL A_DIFFERENT A_EQUAL A_OR_LOGIC A_AND_LOGIC A_RANGE


// Menor para maior precedência
%left  A_OR_LOGIC
%left  A_AND_LOGIC
%nonassoc '<' '>' A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL '=' A_DIFFERENT
%left '+' '-'
%left '*' '/'
%right '^'
%right A_NOT A_U_MINUS A_U_PLUS
%left '.'

%start main

%%

main:
      program_prod
    |
    ;

program_prod:
      A_PROGRAM A_NAME A_BEGIN optional_declaration_list A_END
    ;

optional_declaration_list:
      /* empty */
    | declaration_list
    ;

declaration_list:
      declaration
    | declaration_list ';' declaration
    ;

declaration:
      var_declaration
    | proc_declaration
    | rec_declaration
    ;

var_declaration:
      A_VAR A_NAME ':' type_spec optional_assign_exp
    | A_VAR A_NAME A_ASSIGN exp
    ;

optional_assign_exp:
      /* empty */
    | A_ASSIGN exp
    ;

type_spec:
      A_FLOAT
    | A_INT
    | A_STRING
    | A_BOOL
    | A_NAME  // Para tipos definidos pelo usuário (ex: nome de struct)
    | A_REF '(' type_spec ')'
    ;

proc_declaration:
      A_PROCEDURE A_NAME '(' optional_param_list ')' optional_return_type
      A_BEGIN optional_proc_decls_in_block stmt_list A_END
    ;

optional_param_list:
      /* empty */
    | param_list
    ;

param_list:
      paramfield_decl
    | param_list ',' paramfield_decl // Corresponde a [ PARAMFIELD_DECL { ',' PARAMFIELD_DECL } ]
    ;

paramfield_decl:
      A_NAME ':' type_spec
    ;

optional_return_type:
      /* empty */
    | ':' type_spec
    ;

optional_proc_decls_in_block:
      /* empty */
    | optional_declaration_list A_IN // Corresponde a [[DECL {";" DECL}] in ]
    ;

stmt_list:
      /* empty */
    | stmt_sequence
    ;

stmt_sequence:
      stmt
    | stmt ';' stmt_sequence // Corresponde a [ STMT { ";" STMT} ]
    ;

rec_declaration:
      A_STRUCT A_NAME '{' optional_rec_field_list '}'
    ;

optional_rec_field_list:
      /* empty */
    | rec_field_list
    ;

rec_field_list:
      paramfield_decl
    | rec_field_list ';' paramfield_decl // Corresponde a [ PARAMFIELD_DECL { ';' PARAMFIELD_DECL } ]
    ;

exp:
      literal
    | call_stmt_as_exp // Se uma chamada de função pode ser uma expressão
    | A_NEW A_NAME
    | var_access
    | ref_var
    | deref_var
    | '(' exp ')'
    | A_NOT exp
    | exp A_OR_LOGIC exp
    | exp A_AND_LOGIC exp
    | exp '<' exp
    | exp A_LESS_THAN_EQUAL exp
    | exp '>' exp
    | exp A_GREATER_THAN_EQUAL exp
    | exp '=' exp                 // Usando '=' como token de comparação relacional
    | exp A_DIFFERENT exp
    | exp '+' exp %prec A_U_PLUS // U_PLUS tem precedência mais alta que '+' e '-'
    | exp '-' exp %prec A_U_MINUS // U_MINUS tem precedência mais alta que '+' e '-'
    | exp '*' exp
    | exp '/' exp
    | exp '^' exp
    ;

ref_var:
      A_REF '(' var_access ')'
    ;

deref_var:
      A_DEREF '(' var_access ')'
    | A_DEREF '(' deref_var ')'  // Para desreferências aninhadas
    ;

var_access:
      A_NAME
	  | exp '.' A_NAME // Acesso a membros de uma estrutura ou objeto
    ;


literal:
      FLOAT_LITERAL
    | INT_LITERAL
    | STRING_LITERAL
    | bool_literal
    | A_NULL
    ;

bool_literal:
      A_TRUE
    | A_FALSE
    ;

stmt:
      assign_stmt
    | if_stmt
    | while_stmt
    | return_stmt
    | call_stmt
    ;

assign_stmt:
      var_access A_ASSIGN exp // VAR ":=" EXP
    | deref_var A_ASSIGN exp  // DEREF_VAR ":=" EXP
    ;

if_stmt:
      A_IF exp A_THEN stmt_list optional_else_clause A_FI
    | A_UNLESS exp A_DO stmt_list optional_else_clause A_OD // OD é o terminador para UNLESS
    | A_CASE exp A_OF case_list optional_otherwise_clause A_ESAC
    ;

optional_else_clause:
      /* empty */
    | A_ELSE stmt_list
    ;

case_list:
      case_clause
    | case_list '|' case_clause
    ;

case_clause:
      case_label_list ':' stmt_list
    ;

case_label_list:
      case_label_element
    | case_label_list ',' case_label_element
    ;

case_label_element:
      INT_LITERAL
    | INT_LITERAL A_RANGE INT_LITERAL
    ;

optional_otherwise_clause:
      /* empty */
    | A_OTHERWISE stmt_list
    ;

while_stmt:
      A_WHILE exp A_DO stmt_list A_OD
    ;

return_stmt:
      A_RETURN optional_exp_val
    ;

optional_exp_val:
      /* empty */
    | exp
    ;

call_stmt: // Usado como um comando (STMT)
      A_NAME '(' optional_arg_list ')'
    ;

call_stmt_as_exp: // Usado como uma expressão (EXP)
    A_NAME '(' optional_arg_list ')'
    ;


optional_arg_list:
      /* empty */
    | arg_list
    ;

arg_list:
      exp
    | arg_list ',' exp
    ;

%% // Fim das Regras Gramaticais

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