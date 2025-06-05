%require "3.2"
%language "c++"

// %define parse.trace true

%code requires {
    #include <string>
    #include <vector>
    #include <memory>
    #include <iostream>

    #include "symbol_table.hpp"
    #include "type_utils.hpp"

    class CustomLexer;
}

%parse-param {CustomLexer &lexer}

%header

%code {
    #include "custom_lexer.hpp"
    #define yylex lexer.yylex

    SymbolTable symbol_table;
}

%union {
	int ival;
	float fval;
	std::string* sval;

  VarType* type_val;
  std::vector<ParamField>* param_vec;
}

%token<ival> A_INT_LITERAL
%token<fval> A_FLOAT_LITERAL
%token<sval> A_NAME A_STRING_LITERAL

%token A_LINE

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

%type<type_val> optional_assign_exp exp type_spec literal bool_literal var_access
%type<param_vec> optional_param_list param_list optional_rec_field_list rec_field_list

%destructor { delete $$; } <sval> <type_val> <param_vec>

%start main

%%

main:
      program_prod
    |
    ;

program_prod:
      A_PROGRAM A_NAME { std::cout << "Parsing program: " << *$2 << std::endl; delete $2; }
      A_BEGIN optional_declaration_list A_END { symbol_table.print(); }
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
      {
        if (symbol_table.lookup_current_scope_only(*$2)) {
          error("Variavel '" + *$2 + "' ja declarada neste escopo.");
        } else {
          bool types_are_ok = true;
          if ($5) {
            if (!are_types_compatible(*$4, *$5)) {
                std::string declared_type = type_to_string(*$4);
                std::string assigned_type = type_to_string(*$5);
                error("Incompatibilidade de tipos para a variável '" + *$2 +
                      "'. Tipo declarado: " + declared_type +
                      ", mas o tipo da expressão atribuída é:: " + assigned_type + ".");
                types_are_ok = false;
            }
          }

          if (types_are_ok) {
            Variable var_content{*$4};
            Symbol new_symbol{*$2, SymbolCategory::VARIABLE, var_content};
            symbol_table.insert_symbol(*$2, new_symbol);
          }
        }
        delete $2;
        delete $4;
        if ($5) delete $5;
      }
    | A_VAR A_NAME A_ASSIGN exp
      {
        if (symbol_table.lookup_current_scope_only(*$2)) {
          error("Variavel '" + *$2 + "' ja declarada neste escopo.");
          delete $4;
        } else {
          Variable var_content{*$4};
          Symbol new_symbol{*$2, SymbolCategory::VARIABLE, var_content};
          symbol_table.insert_symbol(*$2, new_symbol);
          delete $4;
        }
        delete $2;
      }
    ;

optional_assign_exp:
      /* empty */ { $$ = nullptr; }
    | A_ASSIGN exp { $$ = $2; }
    ;

type_spec:
      A_FLOAT { $$ = new VarType{PrimitiveType::FLOAT}; }
    | A_INT { $$ = new VarType{PrimitiveType::INT}; }
    | A_STRING { $$ = new VarType{PrimitiveType::STRING}; }
    | A_BOOL { $$ = new VarType{PrimitiveType::BOOL}; }
    | A_NAME  // Para tipos definidos pelo usuário (ex: nome de struct)
      {
        Symbol* s = symbol_table.lookup(*$1);
        if (!s || s->category != SymbolCategory::RECORD) {
          error("Tipo '" + *$1 + "' nao eh um tipo de registro valido.");
          $$ = new VarType{PrimitiveType::UNDEFINED};
        } else {
          $$ = new VarType{PrimitiveType::NOT_PRIMITIVE, *$1};
        }
        delete $1;
      }
    | A_REF '(' type_spec ')'
      {
        std::unique_ptr<VarType> referenced_type = std::make_unique<VarType>(*$3);
        $$ = new VarType(PrimitiveType::REF, std::move(referenced_type));
        delete $3;
      }
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
      literal  { $$ = $1; }
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
      A_FLOAT_LITERAL  { $$ = new VarType{PrimitiveType::FLOAT}; }
    | A_INT_LITERAL    { $$ = new VarType{PrimitiveType::INT}; }
    | A_STRING_LITERAL { $$ = new VarType{PrimitiveType::STRING}; }
    | bool_literal   { $$ = $1; }
    | A_NULL         { $$ = new VarType{PrimitiveType::VOID}; }
    ;

bool_literal:
      A_TRUE  { $$ = new VarType{PrimitiveType::BOOL}; }
    | A_FALSE { $$ = new VarType{PrimitiveType::BOOL}; }
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
      A_INT_LITERAL
    | A_INT_LITERAL A_RANGE A_INT_LITERAL
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

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}