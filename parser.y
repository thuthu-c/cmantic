%require "3.2"
%language "c++"

%locations
%define parse.error verbose

// %define parse.trace true

%code requires {
    #include <string>
    #include <vector>
    #include <memory>
    #include <iostream>
    #include <stack>
    #include <sstream>
    #include <fstream>
    #include <variant>
    #include <map>
    #include <algorithm>
    #include <filesystem>

    #include "symbol_table.hpp"
    #include "type_utils.hpp"
    #include "code_generator.hpp"

    struct NodeInfo {
        std::string code;
        std::string place;
        VarType* type;
        std::vector<NodeInfo*>* arg_list;
        NodeInfo(VarType* t = nullptr) : type(t), arg_list(nullptr) {}
    };

    struct CaseClauseInfo {
        std::string condition_code;
        NodeInfo* body_node;
    };

    class CustomLexer;
}

%parse-param {CustomLexer &lexer}
%header

%code {
    #include "custom_lexer.hpp"
    #define yylex lexer.yylex

    SymbolTable symbol_table;
    CodeGenerator code_generator;
    std::stack<VarType> procedure_return_types;
    std::string current_procedure_end_label;
    bool is_in_main_procedure = false;
    bool found_main = false;

    std::string output_dir = "output/";
}

%union {
    int ival;
    float fval;
    std::string* sval;
    VarType* type_val;
    std::vector<ParamField>* param_vec;
    NodeInfo* node_info;
    std::vector<NodeInfo*>* arg_vec;

    CaseClauseInfo* case_clause_info;
    std::vector<CaseClauseInfo*>* case_list_info;
}

%token<ival> A_INT_LITERAL
%token<fval> A_FLOAT_LITERAL
%token<sval> A_NAME A_STRING_LITERAL

%type<node_info> exp literal bool_literal var_access ref_var deref_var call_stmt_as_exp optional_exp_val
%type<node_info> stmt assign_stmt if_stmt while_stmt return_stmt call_stmt stmt_list stmt_sequence
%type<node_info> optional_else_clause optional_otherwise_clause
%type<node_info> optional_assign_exp
%type<node_info> declaration var_declaration declaration_list optional_declaration_list optional_proc_decls_in_block
%type<node_info> lvalue
%type<node_info> case_label_element

%type<sval> case_label_list
%type<case_clause_info> case_clause
%type<case_list_info> case_list

%type<type_val> type_spec optional_return_type
%type<param_vec> optional_param_list param_list rec_field_list optional_rec_field_list paramfield_decl
%type<arg_vec> optional_arg_list arg_list

%token A_LINE
%token A_PROGRAM A_BEGIN A_END A_PROCEDURE A_VAR
%token A_IF A_THEN A_ELSE A_FI A_WHILE A_DO A_OD A_RETURN A_UNLESS A_CASE A_OF A_ESAC A_OTHERWISE
%token A_TRUE A_FALSE A_FLOAT A_INT A_STRING A_BOOL A_NULL A_STRUCT
%token A_IN A_NOT A_NEW A_REF A_DEREF A_U_MINUS A_U_PLUS
%token ';' ':' ',' '[' ']' '{' '}' '(' ')' '<' '>'  '=' '+' '-' '*' '/' '^' '.' '|'
%token A_ASSIGN A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL A_DIFFERENT A_EQUAL A_OR_LOGIC A_AND_LOGIC A_RANGE

%left  A_OR_LOGIC
%left  A_AND_LOGIC
%nonassoc '<' '>' A_LESS_THAN_EQUAL A_GREATER_THAN_EQUAL A_EQUAL A_DIFFERENT
%left '+' '-'
%left '*' '/'
%right '^'
%right A_NOT A_U_MINUS A_U_PLUS
%left '.'

%destructor { delete $$; } <sval> <type_val> <param_vec> <node_info> <case_clause_info>
%destructor { if ($$) { for(auto p : *$$) delete p; delete $$; } } <arg_vec> <case_list_info>

%start main

%%

main:
    program_prod
    |
    ;

program_prod:
    A_PROGRAM A_NAME
    {
        code_generator.set_program_name(*$2);
        delete $2;
    }
    A_BEGIN optional_declaration_list A_END
    {
        code_generator.emit_code_to_procedure(true, $5->code);
        delete $5;

        if (!found_main) {
            error(@1, "Erro fatal: procedimento 'main' não definido.");
        }
        
        std::filesystem::create_directories(output_dir);
        std::ofstream outfile(output_dir + code_generator.get_program_name() + ".c");
        if (outfile.is_open()) {
            outfile << code_generator.get_final_code();
            outfile.close();
            std::cout << "Código intermediário gerado em " << code_generator.get_program_name() << ".c" << std::endl;
        } else {
            std::cerr << "Erro ao abrir o ficheiro de saída." << std::endl;
        }
        std::cout << "Programa finalizado com sucesso." << std::endl;
    }
    ;

optional_declaration_list:
    /* empty */ { $$ = new NodeInfo(); }
    | declaration_list { $$ = $1; }
    ;

declaration_list:
    declaration { $$ = $1; }
    | declaration_list ';' declaration
    {
        $$ = new NodeInfo();
        $$->code = $1->code + $3->code;
        delete $1; delete $3;
    }
    ;

declaration:
    var_declaration { $$ = $1; }
    | proc_declaration { $$ = new NodeInfo(); }
    | rec_declaration  { $$ = new NodeInfo(); }
    ;

var_declaration:
    A_VAR A_NAME ':' type_spec optional_assign_exp
    {
      if (symbol_table.lookup_current_scope_only(*$2)) {
        error(@2, "Variável '" + *$2 + "' já declarada neste escopo.");
      } else {
        if ($5->type && !are_types_compatible(*$4, *$5->type)) {
            error(@2, "Incompatibilidade de tipos para a variável '" + *$2 + "'.");
        } else {
          Variable var_content{*$4};
          Symbol new_symbol{*$2, SymbolCategory::VARIABLE, var_content};
          symbol_table.insert_symbol(*$2, new_symbol);

          $$ = new NodeInfo();
          std::string c_type = code_generator.type_to_c_type(*$4);
          code_generator.emit_declaration(c_type + " " + *$2 + ";\n");
          if ($5->type) {
              $$->code = $5->code + *$2 + " = " + $5->place + ";\n";
          }
        }
      }
      delete $2; delete $4; delete $5;
    }
    | A_VAR A_NAME A_ASSIGN exp
      {
        if (symbol_table.lookup_current_scope_only(*$2)) {
          error(@2, "Variável '" + *$2 + "' já declarada neste escopo.");
        } else {
          Variable var_content{*$4->type};
          Symbol new_symbol{*$2, SymbolCategory::VARIABLE, var_content};
          symbol_table.insert_symbol(*$2, new_symbol);

          $$ = new NodeInfo();
          std::string c_type = code_generator.type_to_c_type(*$4->type);
          code_generator.emit_declaration(c_type + " " + *$2 + ";\n");
          $$->code = $4->code + *$2 + " = " + $4->place + ";\n";
        }
        delete $2; delete $4;
      }
    ;

optional_assign_exp:
    /* empty */ { $$ = new NodeInfo(); }
    | A_ASSIGN exp { $$ = $2; }
    ;

type_spec:
    A_FLOAT { $$ = new VarType{PrimitiveType::FLOAT}; }
    | A_INT { $$ = new VarType{PrimitiveType::INT}; }
    | A_STRING { $$ = new VarType{PrimitiveType::STRING}; }
    | A_BOOL { $$ = new VarType{PrimitiveType::BOOL}; }
    | A_NAME
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s || s->category != SymbolCategory::RECORD) {
        error(@1, "Tipo '" + *$1 + "' não é um tipo de struct válido.");
        $$ = new VarType{PrimitiveType::UNDEFINED};
      } else {
        $$ = new VarType{PrimitiveType::NOT_PRIMITIVE, *$1};
      }
      delete $1;
    }
    | A_REF '(' type_spec ')'
      {
        $$ = new VarType(PrimitiveType::REF, std::make_unique<VarType>(*$3));
        delete $3;
      }
    | A_DEREF '(' type_spec ')'
      {
        $$ = new VarType(PrimitiveType::DEREF, std::make_unique<VarType>(*$3));
        delete $3;
      }
    ;

proc_declaration:
      A_PROCEDURE A_NAME '(' optional_param_list ')' optional_return_type
      {
        if (symbol_table.lookup_current_scope_only(*$2)) {
            error(@2, "Procedimento '" + *$2 + "' já declarado neste escopo.");
        } else {
            is_in_main_procedure = (*$2 == "main");
            if (is_in_main_procedure) {
                if (found_main) error(@2, "Redefinição do procedimento 'main'.");
                found_main = true;
            }

            Procedure proc_content;
            proc_content.params = *$4;
            proc_content.return_type = $6 ? *$6 : VarType{PrimitiveType::VOID};
            proc_content.label = "proc_" + *$2;
            
            procedure_return_types.push(proc_content.return_type);
            Symbol proc_symbol{*$2, SymbolCategory::PROCEDURE, proc_content};
            symbol_table.insert_symbol(*$2, proc_symbol);

            current_procedure_end_label = code_generator.new_label();
            
            if (!is_in_main_procedure) {
                std::stringstream proc_header;
                proc_header << proc_content.label << ":\n{\n";
                code_generator.emit_code_to_procedure(false, proc_header.str());
            }

            symbol_table.push_scope();
            for (const auto& param : *$4) {
                 Variable var_content{param.type};
                 Symbol param_as_var{param.name, SymbolCategory::VARIABLE, var_content};
                 symbol_table.insert_symbol(param.name, param_as_var);
                 code_generator.emit_declaration(code_generator.type_to_c_type(param.type) + " " + param.name + ";\n");
            }
        }
        delete $2; delete $4; if ($6) delete $6;
      }
      A_BEGIN optional_proc_decls_in_block stmt_list A_END
      {
        std::string body_code = $9->code + $10->code;
        code_generator.emit_code_to_procedure(is_in_main_procedure, body_code);
        
        if (!is_in_main_procedure) {
            std::stringstream proc_footer;
            proc_footer << current_procedure_end_label << ":\n";
            proc_footer << "goto control_procedure;\n}\n";
            code_generator.emit_code_to_procedure(false, proc_footer.str());
        }

        is_in_main_procedure = false;
        if (!procedure_return_types.empty()) procedure_return_types.pop();
        symbol_table.pop_scope();
        delete $9;
        delete $10;
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
    /* empty */ { $$ = new NodeInfo(); }
    | optional_declaration_list A_IN { $$ = $1; }
    ;

stmt_list:
    /* empty */ { $$ = new NodeInfo(); }
    | stmt_sequence { $$ = $1; }
    ;

stmt_sequence:
    stmt { $$ = $1; }
    | stmt ';' stmt_sequence
    {
        $$ = new NodeInfo();
        $$->code = $1->code + $3->code;
        delete $1; delete $3;
    }
    ;

rec_declaration:
    A_STRUCT A_NAME '{' optional_rec_field_list '}'
    {
      if (symbol_table.lookup_current_scope_only(*$2)) {
          error(@1, "Tipo de struct '" + *$2 + "' já definido neste escopo.");
      } else {
          Record rec_content{*$4};
          Symbol new_symbol{*$2, SymbolCategory::RECORD, rec_content};
          symbol_table.insert_symbol(*$2, new_symbol);

          std::stringstream rec_code;
          rec_code << "typedef struct {\n";
          for (const auto& field : rec_content.fields) {
              rec_code << code_generator.type_to_c_type(field.type) << " " << field.name << ";\n";
          }
          rec_code << "} " << *$2 << ";\n";
          code_generator.emit_declaration(rec_code.str());
      }
      delete $2; delete $4;
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
          error(@1, "Tipo '" + *$2 + "' não é um tipo de registo válido para 'new'.");
          $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
      } else {
          $$ = new NodeInfo(new VarType{PrimitiveType::NOT_PRIMITIVE, *$2});
          $$->place = code_generator.new_temp();
          code_generator.emit_declaration(*$2 + " " + $$->place + ";\n");
          $$->code = "/* novo " + *$2 + " para " + $$->place + " */\n";
      }
      delete $2;
    }
    | var_access { $$ = $1; }
    | ref_var { $$ = $1; }
    | deref_var
    {
        if ($1->type->p_type != PrimitiveType::DEREF) {
            $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
        } else {
            $$ = new NodeInfo(new VarType(*$1->type->referenced_type));
            $$->place = code_generator.new_temp();
            code_generator.emit_declaration(code_generator.type_to_c_type(*$$->type) + " " + $$->place + ";\n");
            $$->code = $1->code + $$->place + " = *" + $1->place + ";\n";
        }
        delete $1;
    }
    | '(' exp ')' { $$ = $2; }
    | A_NOT exp
    {
        if ($2->type->p_type != PrimitiveType::BOOL) {
            error(@2, "O operador 'not' requer um operando booleano.");
            $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
        } else {
            $$ = new NodeInfo(new VarType{PrimitiveType::BOOL});
            $$->place = code_generator.new_temp();
            code_generator.emit_declaration("int " + $$->place + ";\n");
            $$->code = $2->code + $$->place + " = !" + $2->place + ";\n";
        }
        delete $2;
    }
    | '-' exp %prec A_U_MINUS
    {
        if (!$2->type || ($2->type->p_type != PrimitiveType::INT && $2->type->p_type != PrimitiveType::FLOAT)) {
            error(@2, "O operador unário '-' requer um operando numérico.");
            $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
        } else {
            $$ = new NodeInfo(new VarType(*$2->type));
            $$->place = code_generator.new_temp();
            code_generator.emit_declaration(code_generator.type_to_c_type(*$$->type) + " " + $$->place + ";\n");
            $$->code = $2->code + $$->place + " = -" + $2->place + ";\n";
        }
        delete $2;
    }
    | '+' exp %prec A_U_PLUS
    {
        if (!$2->type || ($2->type->p_type != PrimitiveType::INT && $2->type->p_type != PrimitiveType::FLOAT)) {
            error(@2, "O operador unário '+' requer um operando numérico.");
            $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
        } else {
            $$ = $2; 
        }
    }
    | exp A_OR_LOGIC exp {
        VarType* res_type = check_logical_op($1->type, $3->type, "||");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " || " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp A_AND_LOGIC exp {
        VarType* res_type = check_logical_op($1->type, $3->type, "&&");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " && " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '<' exp {
        VarType* res_type = check_relational_op($1->type, $3->type, "<");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " < " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '>' exp {
        VarType* res_type = check_relational_op($1->type, $3->type, ">");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " > " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp A_LESS_THAN_EQUAL exp {
        VarType* res_type = check_relational_op($1->type, $3->type, "<=");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " <= " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp A_GREATER_THAN_EQUAL exp {
        VarType* res_type = check_relational_op($1->type, $3->type, ">=");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " >= " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp A_EQUAL exp {
        VarType* res_type = check_relational_op($1->type, $3->type, "==");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " == " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp A_DIFFERENT exp {
        VarType* res_type = check_relational_op($1->type, $3->type, "!=");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration("int " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " != " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '+' exp {
        VarType* res_type = check_arithmetic_op($1->type, $3->type, "+");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration(code_generator.type_to_c_type(*res_type) + " " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " + " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '-' exp {
        VarType* res_type = check_arithmetic_op($1->type, $3->type, "-");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration(code_generator.type_to_c_type(*res_type) + " " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " - " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '*' exp {
        VarType* res_type = check_arithmetic_op($1->type, $3->type, "*");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration(code_generator.type_to_c_type(*res_type) + " " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " * " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '/' exp {
        VarType* res_type = check_arithmetic_op($1->type, $3->type, "/");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration(code_generator.type_to_c_type(*res_type) + " " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = " + $1->place + " / " + $3->place + ";\n";
        delete $1; delete $3;
    }
    | exp '^' exp {
        VarType* res_type = check_arithmetic_op($1->type, $3->type, "^");
        $$ = new NodeInfo(res_type);
        $$->place = code_generator.new_temp();
        code_generator.emit_declaration(code_generator.type_to_c_type(*res_type) + " " + $$->place + ";\n");
        $$->code = $1->code + $3->code + $$->place + " = pow(" + $1->place + ", " + $3->place + ");\n";
        delete $1; delete $3;
    }
    ;

ref_var:
    A_REF '(' var_access ')'
    {
      $$ = new NodeInfo(new VarType(PrimitiveType::REF, std::make_unique<VarType>(*$3->type)));
      $$->place = code_generator.new_temp();
      code_generator.emit_declaration(code_generator.type_to_c_type(*$$->type) + " " + $$->place + ";\n");
      $$->code = $3->code + $$->place + " = &" + $3->place + ";\n";
      delete $3;
    }
    ;

deref_var:
    A_DEREF '(' var_access ')'
    {
      if ($3->type->p_type != PrimitiveType::REF || !$3->type->referenced_type) {
          error(@3, "Não é possível desreferenciar um tipo que não é referência.");
          $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
      } else {
          auto inner_type = std::make_unique<VarType>(*$3->type->referenced_type);
          $$ = new NodeInfo(new VarType(PrimitiveType::DEREF, std::move(inner_type)));
          $$->place = $3->place; 
          $$->code = $3->code;
      }
      delete $3;
    }
    ;

var_access:
    A_NAME
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s || s->category != SymbolCategory::VARIABLE) {
          error(@1, "Símbolo '" + *$1 + "' não é uma variável declarada.");
          $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
      } else {
          $$ = new NodeInfo(new VarType{std::get<Variable>(s->content).type});
          $$->place = *$1;
      }
      delete $1;
    }
    | exp '.' A_NAME
    {
      $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
      if ($1->type->p_type == PrimitiveType::NOT_PRIMITIVE && $1->type->record_name.has_value()) {
          Symbol* rec_symbol = symbol_table.lookup($1->type->record_name.value());
          if (rec_symbol && rec_symbol->category == SymbolCategory::RECORD) {
              const Record& rec = std::get<Record>(rec_symbol->content);
              bool found = false;
              for (const auto& field : rec.fields) {
                  if (field.name == *$3) {
                      delete $$->type;
                      $$->type = new VarType{field.type};
                      $$->place = $1->place + "." + *$3;
                      $$->code = $1->code;
                      found = true;
                      break;
                  }
              }
              if (!found) error(@3, "O struct '" + $1->type->record_name.value() + "' não possui o campo '" + *$3 + "'.");
          }
      } else {
          error(@1, "O acesso a membros '.' requer um struct à esquerda.");
      }
      delete $1; delete $3;
    }
    ;

literal:
    A_FLOAT_LITERAL
    {
        $$ = new NodeInfo(new VarType{PrimitiveType::FLOAT});
        $$->place = std::to_string($1);
    }
    | A_INT_LITERAL
    {
        $$ = new NodeInfo(new VarType{PrimitiveType::INT});
        $$->place = std::to_string($1);
    }
    | A_STRING_LITERAL
    {
        $$ = new NodeInfo(new VarType{PrimitiveType::STRING});
        $$->place = "\"" + *$1 + "\"";
        delete $1;
    }
    | bool_literal { $$ = $1; }
    | A_NULL
    {
        $$ = new NodeInfo(new VarType{PrimitiveType::VOID});
        $$->place = "NULL";
    }
    ;

bool_literal:
    A_TRUE  { $$= new NodeInfo(new VarType{PrimitiveType::BOOL});$$->place = "1"; }
    | A_FALSE { $$= new NodeInfo(new VarType{PrimitiveType::BOOL});$$->place = "0"; }
    ;

stmt:
    assign_stmt { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    | call_stmt { $$ = $1; }
    ;

lvalue:
    var_access { $$ = $1; }
    | deref_var { $$ = $1; }
    ;

assign_stmt:
    lvalue A_ASSIGN exp
    {
      VarType* lvalue_type = $1->type;
      if ($1->type->p_type == PrimitiveType::DEREF) {
          lvalue_type = $1->type->referenced_type.get();
      }

      if (!are_types_compatible(*lvalue_type, *$3->type)) {
          error(@1, "Incompatibilidade de tipos na atribuição.");
      }
      
      $$ = new NodeInfo();
      std::string target = $1->place;
      if ($1->type->p_type == PrimitiveType::DEREF) {
          target = "*" + target;
      }
      $$->code = $1->code + $3->code + target + " = " + $3->place + ";\n";
      delete $1; delete $3;
    }
    ;

if_stmt:
    A_IF exp A_THEN stmt_list optional_else_clause A_FI
    {
      if ($2->type->p_type != PrimitiveType::BOOL) error(@2, "A condição do 'if' deve ser booleana.");

      std::string then_label = code_generator.new_label();
      std::string end_label = code_generator.new_label();
      std::string else_label = ($5->code.empty()) ? end_label : code_generator.new_label();

      $$ = new NodeInfo();
      std::stringstream c;
      c << $2->code;
      c << "if (" << $2->place << ") goto " << then_label << ";\n";
      c << "goto " << else_label << ";\n";
      c << then_label << ":\n" << $4->code;
      c << "goto " << end_label << ";\n";
      if (!else_label.empty() && else_label != end_label) {
          c << else_label << ":\n" << $5->code;
      }
      c << end_label << ":\n";

      $$->code = c.str();
      delete $2; delete $4; delete $5;
    }
    | A_UNLESS exp A_DO stmt_list optional_else_clause A_OD
    {
        if ($2->type->p_type != PrimitiveType::BOOL) error(@2, "A condição do 'unless' deve ser booleana.");
        
        std::string neg_temp = code_generator.new_temp();
        code_generator.emit_declaration("int " + neg_temp + ";\n");

        std::string then_label = code_generator.new_label();
        std::string end_label = code_generator.new_label();
        std::string else_label = ($5->code.empty()) ? end_label : code_generator.new_label();

        $$ = new NodeInfo();
        std::stringstream c;
        c << $2->code;
        c << neg_temp << " = !" << $2->place << ";\n";
        c << "if (" << neg_temp << ") goto " << then_label << ";\n";
        c << "goto " << else_label << ";\n";
        c << then_label << ":\n" << $4->code;
        c << "goto " << end_label << ";\n";
        if (!else_label.empty() && else_label != end_label) {
            c << else_label << ":\n" << $5->code;
        }
        c << end_label << ":\n";

        $$->code = c.str();
        delete $2; delete $4; delete $5;
    }
    | A_CASE exp A_OF case_list optional_otherwise_clause A_ESAC
    {
        if ($2->type->p_type != PrimitiveType::INT) error(@2, "A expressão do 'case' deve ser um inteiro.");

        std::string end_label = code_generator.new_label();
        $$ = new NodeInfo();
        std::stringstream case_code;
        case_code << $2->code;
        
        std::vector<CaseClauseInfo*>& clauses = *$4;
        std::vector<std::string> body_labels;
        for (size_t i = 0; i < clauses.size(); ++i) {
            body_labels.push_back(code_generator.new_label());
        }

        for (size_t i = 0; i < clauses.size(); ++i) {
            std::string condition = clauses[i]->condition_code;
            size_t pos;
            while((pos = condition.find("%%VAR_PLACE%%")) != std::string::npos)
                condition.replace(pos, 13, $2->place);
            case_code << "if (" << condition << ") goto " << body_labels[i] << ";\n";
        }

        if ($5) {
            case_code << $5->code;
        }
        case_code << "goto " << end_label << ";\n";

        for (size_t i = 0; i < clauses.size(); ++i) {
            case_code << body_labels[i] << ":\n";
            case_code << clauses[i]->body_node->code;
            case_code << "goto " << end_label << ";\n";
        }
        
        case_code << end_label << ":\n";

        $$->code = case_code.str();
        delete $2; delete $4; delete $5;
    }
    ;

optional_else_clause:
    /* empty */ { $$ = new NodeInfo(); }
    | A_ELSE stmt_list { $$ = $2; }
    ;

case_list:
    case_clause { $$ = new std::vector<CaseClauseInfo*>{$1}; }
    | case_list '|' case_clause { $1->push_back($3); $$ = $1; }
    ;

case_clause:
    case_label_list ':' stmt_list
    {
        $$ = new CaseClauseInfo{ *$1, $3 };
        delete $1;
    }
    ;

case_label_list:
    case_label_element { $$ = new std::string($1->place); delete $1; }
    | case_label_list ',' case_label_element
    {
        $$ = new std::string(*$1 + " || " + $3->place);
        delete $1; delete $3;
    }
    ;

case_label_element:
    A_INT_LITERAL { $$= new NodeInfo();$$->place = "%%VAR_PLACE%% == " + std::to_string($1); }
    | A_INT_LITERAL A_RANGE A_INT_LITERAL { $$= new NodeInfo();$$->place = "(%%VAR_PLACE%% >= " + std::to_string($1) + " && %%VAR_PLACE%% <= " + std::to_string($3) + ")"; }
    ;

optional_otherwise_clause:
    /* empty */ { $$ = nullptr; }
    | A_OTHERWISE ':' stmt_list { $$ = $3; }
    ;

while_stmt:
    A_WHILE exp A_DO stmt_list A_OD
    {
      if ($2->type->p_type != PrimitiveType::BOOL) error(@2, "A condição do 'while' deve ser booleana.");
      
      std::string start_label = code_generator.new_label();
      std::string body_label = code_generator.new_label();
      std::string end_label = code_generator.new_label();

      $$ = new NodeInfo();
      std::stringstream c;
      c << start_label << ":\n";
      c << $2->code;
      c << "if (" << $2->place << ") goto " << body_label << ";\n";
      c << "goto " << end_label << ";\n";
      c << body_label << ":\n";
      c << $4->code;
      c << "goto " << start_label << ";\n";
      c << end_label << ":\n";
      $$->code = c.str();
      delete $2; delete $4;
    }
    ;

return_stmt:
    A_RETURN optional_exp_val
    {
        VarType returned_type = $2->type ? *$2->type : VarType{PrimitiveType::VOID};
        if (!are_types_compatible(procedure_return_types.top(), returned_type)) {
            error(@2, "Tipo de retorno incompatível.");
        }

        $$ = new NodeInfo();
        std::stringstream c;
        c << $2->code;
        if ($2->type && $2->type->p_type != PrimitiveType::VOID) {
            std::string return_var = code_generator.get_return_variable_name(*$2->type);
            c << return_var << " = " << $2->place << ";\n";
        }
        c << "goto " << current_procedure_end_label << ";\n";
        $$->code = c.str();
        delete $2;
    }
    ;

optional_exp_val:
    /* empty */ { $$ = new NodeInfo(); }
    | exp { $$ = $1; }
    ;

call_stmt:
    A_NAME '(' optional_arg_list ')'
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s || s->category != SymbolCategory::PROCEDURE) {
          error(@1, "Procedimento '" + *$1 + "' não declarado.");
          $$ = new NodeInfo();
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          if (proc.params.size() != $3->size()) error(@3, "Número incorreto de argumentos.");

          $$ = new NodeInfo();
          std::string return_label = code_generator.new_label();
          int call_id = code_generator.register_call(return_label);

          std::stringstream c;
          c << "stack_pointer++;\n";
          c << "activation_stack[stack_pointer] = " << call_id << ";\n";
          for(size_t i = 0; i < proc.params.size(); ++i) {
              if(!are_types_compatible(proc.params[i].type, *(*$3)[i]->type)) error(@3, "Tipo de argumento incorreto.");
              c << (*$3)[i]->code;
              c << proc.params[i].name << " = " << (*$3)[i]->place << ";\n";
          }
          c << "goto " << proc.label << ";\n";
          c << return_label << ":\n";
          $$->code = c.str();
      }
      delete $1; delete $3;
    }
    ;

call_stmt_as_exp:
    A_NAME '(' optional_arg_list ')'
    {
      Symbol* s = symbol_table.lookup(*$1);
      if (!s || s->category != SymbolCategory::PROCEDURE) {
          error(@1, "Função '" + *$1 + "' não declarada.");
          $$ = new NodeInfo(new VarType{PrimitiveType::UNDEFINED});
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          if (proc.return_type.p_type == PrimitiveType::VOID) error(@1, "Procedimento sem valor de retorno usado como uma expressão.");
          if (proc.params.size() != $3->size()) error(@3, "Número incorreto de argumentos.");

          $$ = new NodeInfo(new VarType{proc.return_type});
          $$->place = code_generator.new_temp();
          code_generator.emit_declaration(code_generator.type_to_c_type(proc.return_type) + " " + $$->place + ";\n");

          std::string return_label = code_generator.new_label();
          int call_id = code_generator.register_call(return_label);

          std::stringstream c;
          c << "stack_pointer++;\n";
          c << "activation_stack[stack_pointer] = " << call_id << ";\n";
          for(size_t i = 0; i < proc.params.size(); ++i) {
              if(!are_types_compatible(proc.params[i].type, *(*$3)[i]->type)) error(@3, "Tipo de argumento incorreto.");
              c << (*$3)[i]->code;
              c << proc.params[i].name << " = " << (*$3)[i]->place << ";\n";
          }
          c << "goto " << proc.label << ";\n";
          c << return_label << ":\n";
          
          std::string return_var = code_generator.get_return_variable_name(proc.return_type);
          c << $$->place << " = " << return_var << ";\n";
          $$->code = c.str();
      }
      delete $1; delete $3;
    }
    ;

optional_arg_list:
    /* empty */ { $$ = new std::vector<NodeInfo*>(); }
    | arg_list { $$ = $1; }
    ;

arg_list:
    exp { $$ = new std::vector<NodeInfo*>{$1}; }
    | arg_list ',' exp { $1->push_back($3); $$ = $1; }
    ;

%%

void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << "Erro de Sintaxe na Linha " << loc.begin.line << ", Coluna " << loc.begin.column << ": " << msg << std::endl;
    exit(1);
}
