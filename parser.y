%require "3.2"
%language "c++"

// %define parse.trace true

%code requires {
    #include <string>
    #include <vector>
    #include <memory>
    #include <iostream>
    #include <stack>

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
    std::vector<VarType*>* type_vec;
}

%token<ival> A_INT_LITERAL
%token<fval> A_FLOAT_LITERAL
%token<sval> A_NAME A_STRING_LITERAL

%type<type_val> optional_assign_exp exp type_spec literal bool_literal var_access
%type<type_val> ref_var deref_var call_stmt_as_exp optional_exp_val optional_return_type
%type<param_vec> optional_param_list param_list optional_rec_field_list rec_field_list paramfield_decl
%type<type_vec> optional_arg_list arg_list

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
%nonassoc '<' '>' A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL A_EQUAL A_DIFFERENT
%left '+' '-'
%left '*' '/'
%right '^'
%right A_NOT A_U_MINUS A_U_PLUS
%left '.'

%destructor { delete $$; } <sval> <type_val> <param_vec>
%destructor { if ($$) { for(auto p : *$$) delete p; delete $$; } } <type_vec>

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
        }
        delete $2;
        delete $4;
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
        error("Tipo '" + *$1 + "' nao eh um tipo de struct valido.");
        $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
        $$ = new VarType{PrimitiveType::NOT_PRIMITIVE, *$1};
      }
      delete $1;
    }
    | A_REF '(' type_spec ')'
      {
        auto referenced_type = std::make_unique<VarType>(*$3);
        $$ = new VarType(PrimitiveType::REF, std::move(referenced_type));
        delete $3;
      }
    ;

proc_declaration:
      A_PROCEDURE A_NAME '(' optional_param_list ')' optional_return_type
      A_BEGIN optional_proc_decls_in_block stmt_list A_END
      {
        std::vector<ParamField>* params = *$4;

        if (symbol_table.lookup_current_scope_only(*$2)) {
            error("Procedimento '" + *$2 + "' já declarado neste escopo.");
        } else {
            Procedure proc_content;
            proc_content.params = *params;
            proc_content.return_type = $6 ? *$6 : VarType{PrimitiveType::VOID};
            Symbol proc_symbol{*$2, SymbolCategory::PROCEDURE, proc_content};
            symbol_table.insert_symbol(*$2, proc_symbol);
        }

        delete $2;
        delete params;
        if ($6) delete $6;
      }
    ;

optional_param_list:
    /* empty */  { $$ = new std::vector<ParamField>(); }
    | param_list { $$ = $1; }
    ;

param_list:
    paramfield_decl { $$ = $1; }
    | param_list ',' paramfield_decl { $1->insert($1->end(), $3->begin(), $3->end()); delete $3; $$ = $1; }
    ;

paramfield_decl:
    A_NAME ':' type_spec { $$ = new std::vector<ParamField>{{*$1, *$3}}; delete $1; delete $3; }
    ;

optional_return_type:
    /* empty */ { $$ = nullptr; }
    | ':' type_spec { $$ = $2; }
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
    {
      if (symbol_table.lookup_current_scope_only(*$2)) {
          error("Tipo de struct '" + *$2 + "' já definido neste escopo.");
      } else {
          Record rec_content{*$4};
          Symbol new_symbol{*$2, SymbolCategory::RECORD, rec_content};
          symbol_table.insert_symbol(*$2, new_symbol);
      }
      delete $2;
      delete $4;
    }
    ;

optional_rec_field_list:
    /* empty */ { $$ = new std::vector<ParamField>(); }
    | rec_field_list { $$ = $1; }
    ;

rec_field_list:
    paramfield_decl
    | rec_field_list ';' paramfield_decl { $1->insert($1->end(), $3->begin(), $3->end()); delete $3; $$ = $1; }
    ;

exp:
    literal  { $$ = $1; }
    | call_stmt_as_exp { $$ = $1; }
    | A_NEW A_NAME
    {
      Symbol* s = symbol_table.lookup(*$2);
      if (!s || s->category != SymbolCategory::RECORD) {
          error("Tipo '" + *$2 + "' não é um tipo de registro válido para 'new'.");
          $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
          $$ = new VarType{PrimitiveType::NOT_PRIMITIVE, *$2};
      }
      delete $2;
    }
    | var_access { $$ = $1; }
    | ref_var { $$ = $1; }
    | deref_var { $$ = $1; }
    | '(' exp ')' { $$ = $2; }
    | A_NOT exp
    {
        if ($2->p_type != PrimitiveType::BOOL) {
            error("Operador 'not' requer um operando booleano, mas obteve " + type_to_string(*$2) + ".");
            $$ = new VarType{PrimitiveType::UNDEFINED};
        } else {
            $$ = $2;
        }
        delete $2;
    }
    | '-' exp %prec A_U_MINUS
    {
        if (!$2 || ($2->p_type != PrimitiveType::INT && $2->p_type != PrimitiveType::FLOAT)) {
            error("Operador unário '-' requer operando numérico. Foi: " + type_to_string(*$2) + ".");
            $$ = new VarType{PrimitiveType::UNDEFINED};
        } else {
            $$ = $2;
        }
        delete $2;
    }
    | '+' exp %prec A_U_PLUS
    {
        if (!$2 || ($2->p_type != PrimitiveType::INT && $2->p_type != PrimitiveType::FLOAT)) {
            error("Operador unário '+' requer operando numérico. Foi: " + type_to_string(*$2) + ".");
            $$ = new VarType{PrimitiveType::UNDEFINED};
        } else {
            $$ = $2;
        }
        delete $2;
    }
    | exp A_OR_LOGIC exp { $$ = check_logical_op($1, $3, "||"); }
    | exp A_AND_LOGIC exp { $$ = check_logical_op($1, $3, "&&"); }
    | exp '<' exp { $$ = check_relational_op($1, $3, "<"); }
    | exp A_LESS_THAN_EQUAL exp { $$ = check_relational_op($1, $3, "<="); }
    | exp '>' exp { $$ = check_relational_op($1, $3, ">"); }
    | exp A_GREATER_THAN_EQUAL exp { $$ = check_relational_op($1, $3, ">="); }
    | exp A_EQUAL exp { $$ = check_relational_op($1, $3, "=="); }
    | exp A_DIFFERENT exp { $$ = check_relational_op($1, $3, "<>"); }
    | exp '+' exp { $$ = check_arithmetic_op($1, $3, "+"); }
    | exp '-' exp { $$ = check_arithmetic_op($1, $3, "-"); }
    | exp '*' exp { $$ = check_arithmetic_op($1, $3, "*"); }
    | exp '/' exp { $$ = check_arithmetic_op($1, $3, "/"); }
    | exp '^' exp { $$ = check_arithmetic_op($1, $3, "^"); }
    ;

ref_var:
    A_REF '(' var_access ')'
    {
      auto referenced_type = std::make_unique<VarType>(*$3);
      $$ = new VarType(PrimitiveType::REF, std::move(referenced_type));
      delete $3;
    }
    ;

deref_var:
    A_DEREF '(' var_access ')'
    {
      if ($3->p_type != PrimitiveType::REF || !$3->referenced_type) {
          error("Não é possível desreferenciar um tipo não-referência: " + type_to_string(*$3) + ".");
          $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
          $$ = new VarType{*$3->referenced_type};
      }
      delete $3;
    }
    | A_DEREF '(' deref_var ')'
    {
      if ($3->p_type != PrimitiveType::REF || !$3->referenced_type) {
          error("Não é possível desreferenciar um tipo não-referência: " + type_to_string(*$3) + ".");
          $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
          $$ = new VarType{*$3->referenced_type};
      }
      delete $3;
    }
    ;

var_access:
    A_NAME
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s) {
          error("Variável '" + *$1 + "' não declarada.");
          $$ = new VarType{PrimitiveType::UNDEFINED};
      } else if (s->category != SymbolCategory::VARIABLE) {
          error("Símbolo '" + *$1 + "' não é uma variável.");
          $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
          $$ = new VarType{std::get<Variable>(s->content).type};
      }
      delete $1;
    }
    | exp '.' A_NAME
    {
      $$ = new VarType{PrimitiveType::UNDEFINED};
      if ($1->p_type == PrimitiveType::NOT_PRIMITIVE && $1->record_name.has_value()) {
          Symbol* rec_symbol = symbol_table.lookup($1->record_name.value());
          if (rec_symbol && rec_symbol->category == SymbolCategory::RECORD) {
              const Record& rec = std::get<Record>(rec_symbol->content);
              bool found_field = false;
              for (const auto& field : rec.fields) {
                  if (field.name == *$3) {
                      delete $$; // Descarta o UNDEFINED
                      $$ = new VarType{field.type};
                      found_field = true;
                      break;
                  }
              }
              if (!found_field) {
                  error("Struct '" + $1->record_name.value() + "' não possui o campo '" + *$3 + "'.");
              }
          } else {
              error("Tipo de struct '" + $1->record_name.value() + "' não encontrado.");
          }
      } else {
          error("Acesso de membro '.' requer um tipo de struct à esquerda, mas obteve " + type_to_string(*$1) + ".");
      }
      delete $1;
      delete $3;
    }
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
    var_access A_ASSIGN exp
    {
      if (!are_types_compatible(*$1, *$3)) {
          error("Incompatibilidade de tipos na atribuição. Esperado " + type_to_string(*$1) + " mas obteve " + type_to_string(*$3) + ".");
      }
      delete $1;
      delete $3;
    }
    | deref_var A_ASSIGN exp
    {
      if (!are_types_compatible(*$1->, *$3)) {
          error("Incompatibilidade de tipos na atribuição por desreferência. Esperado " + type_to_string(*$1) + " mas obteve " + type_to_string(*$3) + ".");
      }
      delete $1;
      delete $3;
    }
    ;

if_stmt:
    A_IF exp A_THEN stmt_list optional_else_clause A_FI
    {
      if ($2->p_type != PrimitiveType::BOOL) {
          error("Condição do 'if' deve ser booleana, mas foi " + type_to_string(*$2) + ".");
      }
      delete $2;
    }
    | A_UNLESS exp A_DO stmt_list optional_else_clause A_OD
    {
      if ($2->p_type != PrimitiveType::BOOL) {
          error("Condição do 'unless' deve ser booleana, mas foi " + type_to_string(*$2) + ".");
      }
      delete $2;
    }
    | A_CASE exp A_OF case_list optional_otherwise_clause A_ESAC
    {
      if ($2->p_type != PrimitiveType::INT) {
            error("Expressão do 'case' deve ser do tipo inteiro, mas foi " + type_to_string(*$2) + ".");
      }
      delete $2;
    }
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
    {
      if ($2->p_type != PrimitiveType::BOOL) {
          error("Condição do 'while' deve ser booleana, mas foi " + type_to_string(*$2) + ".");
      }
      delete $2;
    }
    ;

return_stmt:
    A_RETURN optional_exp_val
    {
        if ($2) delete $2;
    }
    ;

optional_exp_val:
    /* empty */ { $$ = nullptr; }
    | exp { $$ = $1; }
    ;

call_stmt: // Usado como um comando (STMT)
    A_NAME '(' optional_arg_list ')'
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s) {
          error("Procedimento '" + *$1 + "' não foi declarado.");
      } else if (s->category != SymbolCategory::PROCEDURE) {
          error("Símbolo '" + *$1 + "' não é um procedimento, não pode ser chamado.");
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          const auto& params = proc.params;
          const auto& args = *$3;

          if (params.size() != args.size()) {
              error("Número incorreto de argumentos para '" + *$1 + "'. Esperado: " + std::to_string(params.size()) + ", Fornecido: " + std::to_string(args.size()) + ".");
          } else {
              for (size_t i = 0; i < params.size(); ++i) {
                  if (!are_types_compatible(params[i].type, *args[i])) {
                      error("Incompatibilidade de tipo para o argumento " + std::to_string(i+1) + " na chamada de '" + *$1 + "'. Esperado: " + type_to_string(params[i].type) + ", Fornecido: " + type_to_string(*args[i]) + ".");
                  }
              }
          }
      }
      delete $1;
      delete $3;
    }
    ;

call_stmt_as_exp: // Usado como uma expressão (EXP)
    A_NAME '(' optional_arg_list ')'
    {
      $$ = new VarType{PrimitiveType::UNDEFINED};
      Symbol* s = symbol_table.lookup(*$1);
      if (!s) {
          error("Função '" + *$1 + "' não foi declarada.");
      } else if (s->category != SymbolCategory::PROCEDURE) {
          error("Símbolo '" + *$1 + "' não é uma função.");
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          if (proc.return_type.p_type == PrimitiveType::VOID) {
              error("Procedimento '" + *$1 + "' não retorna um valor e não pode ser usado em uma expressão.");
          } else {
                delete $$;
                $$ = new VarType{proc.return_type};
          }

          const auto& params = proc.params;
          const auto& args = *$3;
          if (params.size() != args.size()) {
              error("Número incorreto de argumentos para '" + *$1 + "'. Esperado: " + std::to_string(params.size()) + ", Fornecido: " + std::to_string(args.size()) + ".");
          } else {
                for (size_t i = 0; i < params.size(); ++i) {
                  if (!are_types_compatible(params[i].type, *args[i])) {
                    error("Incompatibilidade de tipo para o argumento " + std::to_string(i+1) + " na chamada de '" + *$1 + "'. Esperado: " + type_to_string(params[i].type) + ", Fornecido: " + type_to_string(*args[i]) + ".");
                  }
              }
          }
      }
      delete $1;
    }
    ;


optional_arg_list:
    /* empty */ { $$ = new std::vector<VarType*>(); }
    | arg_list { $$ = $1; }
    ;

arg_list:
    exp { $$ = new std::vector<VarType*>{$1}; }
    | arg_list ',' exp { $1->push_back($3); $$ = $1; }
    ;

%% // Fim das Regras Gramaticais

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}