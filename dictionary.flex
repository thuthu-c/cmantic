%option c++
%option noyywrap
%option nounput
%option noreject
%option noyy_top_state


%{
    #undef yyFlexLexer
    #define yyFlexLexer MyFlexLexer
    #include <FlexLexer.h>

    #include "program_map.hpp"
    #include "symboltab.hpp"
    #include <iostream>

extern int line_number;

void yyerror(MyFlexLexer* lexer, const char *message);

%}

NAME [a-zA-Z][a-zA-Z0-9_]*
SINGLE_COMMENT "//".*
MULTI_COMMENT "(\*"([^*]|\*+[^)*])*\*+")"
INA_LITERAL [0-9]+
STRING_LITERAL \"([^\\\"\n]|\\.)*\"
BOOL_LITERAL "true" | "false"
FLOAA_LITERAL [0-9]+"."[0-9]+([Ee][-+][0-9]{2})?

%%

{INA_LITERAL} {
    return A_INA_LITERAL;
}

{FLOAA_LITERAL} {
    return A_FLOAA_LITERAL;
}

"if" {
    return A_IF;
}

"then" {
    return A_THEN;
}

"else" {
    return A_ELSE;
}

"fi" {
    return A_FI;
}

"while" {
    return A_WHILE;
}

"do" {
    return A_DO;
}

"od" {
    return A_OD;
}

"return" {
    return A_RETURN;
}

"unless" {
    return A_UNLESS;
}

"case" {
    return A_CASE;
}

"of" {
    return A_OF;
}

"esac" {
    return A_ESAC;
}

"otherwise" {
    return A_OTHERWISE;
}

"true" {
    return A_TRUE;
}

"false" {
    return A_FALSE;
}

"float" {
    return A_FLOAT;
}

"int" {
    return A_INT;
}

"string" {
    return A_STRING;
}

"bool" {
    return A_BOOL;
}

"null" {
    return A_NULL;
}

"program" {
    return A_PROGRAM;
}

"begin" {
    return A_BEGIN;
}

"end" {
    return A_END;
}

"var" {
    return A_VAR;
}

"procedure" {
    return A_PROCEDURE;
}

"struct" {
    return A_STRUCT;
}

"in" {
    return A_IN;
}

"not" {
    return A_NOT;
}

"new" {
    return A_NEW;
}

"ref" {
    return A_REF;
}

"deref" {
    return A_DEREF;
}

";" {
    return A_SEMICOLON;
}

":" {
    return A_COLON;
}

"," {
    return A_COMMA;
}

":=" {
    return A_ASSIGN;
}

".." {
    return A_RANGE;
}

"." {
    return A_DOT;
}

"[" {
    return A_LEFA_BRACKET;
}

"]" {
    return A_RIGHA_BRACKET;
}

"(" {
    return A_LEFA_PARENTHESIS;
}

")" {
    return A_RIGHA_PARENTHESIS;
}

"{" {
    return A_LEFA_BRACES;
}

"}" {
    return A_RIGHA_BRACES;
}

"||" {
    return A_OR_LOGIC;
}

"&&" {
    return A_AND_LOGIC;
}

"<" {
    return A_LESS_THAN;
}

"<=" {
    return A_LESS_THAN_EQUAL;
}

">" {
    return A_GREATER_THAN;
}

">=" {
    return A_GREATER_THAN_EQUAL;
}

"==" {
    return A_EQUAL;
}

"<>" {
    return A_DIFFERENT;
}

"+" {
    return A_PLUS;
}

"-" {
    return A_MINUS;
}

"*" {
    return A_MULTIPLY;
}

"/" {
    return A_DIVIDE;
}

"^" {
    return A_POWER;
}

{STRING_LITERAL} {
    return A_STRING_LITERAL;
}

{NAME} {
    insert_symbol(yytext);
    return A_NAME;
}

{SINGLE_COMMENT} {
    return A_SINGLE_COMMENT;
}

{MULTI_COMMENT} {
    return A_MULTI_COMMENT;
}

\n    { 
    line_number++;
    return A_END_LINE; 
    }

[ \t\r]+  { /* Ignore whitespace */ }

<<EOF>> {
    return A_EOF;  // Retorna A_EOF quando o EOF for alcançado
}

.     { yyerror(this, "Invalid character"); }

%%

void yyerror(MyFlexLexer* lexer, const char *message)
{
    std::cerr << "Error: \"" << message << "\" in line " << line_number
              << ". Token = " << lexer->YYText() << std::endl;
    exit(1);
}


int MyFlexLexer::yywrap() {
    return 1;
}