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
INT_LITERAL [0-9]+
STRING_LITERAL \"([^\\\"\n]|\\.)*\"
BOOL_LITERAL "true" | "false"
FLOAT_LITERAL [0-9]+"."[0-9]+([Ee][-+][0-9]{2})?

%%

{INT_LITERAL} {
    return T_INT_LITERAL;
}

{FLOAT_LITERAL} {
    return T_FLOAT_LITERAL;
}

"if" {
    return T_IF;
}

"then" {
    return T_THEN;
}

"else" {
    return T_ELSE;
}

"fi" {
    return T_FI;
}

"while" {
    return T_WHILE;
}

"do" {
    return T_DO;
}

"od" {
    return T_OD;
}

"return" {
    return T_RETURN;
}

"unless" {
    return T_UNLESS;
}

"case" {
    return T_CASE;
}

"of" {
    return T_OF;
}

"esac" {
    return T_ESAC;
}

"otherwise" {
    return T_OTHERWISE;
}

"true" {
    return T_TRUE;
}

"false" {
    return T_FALSE;
}

"float" {
    return T_FLOAT;
}

"int" {
    return T_INT;
}

"string" {
    return T_STRING;
}

"bool" {
    return T_BOOL;
}

"null" {
    return T_NULL;
}

"program" {
    return T_PROGRAM;
}

"begin" {
    return T_BEGIN;
}

"end" {
    return T_END;
}

"var" {
    return T_VAR;
}

"procedure" {
    return T_PROCEDURE;
}

"struct" {
    return T_STRUCT;
}

"in" {
    return T_IN;
}

"not" {
    return T_NOT;
}

"new" {
    return T_NEW;
}

"ref" {
    return T_REF;
}

"deref" {
    return T_DEREF;
}

";" {
    return T_SEMICOLON;
}

":" {
    return T_COLON;
}

"," {
    return T_COMMA;
}

":=" {
    return T_ASSIGN;
}

"." {
    return T_DOT;
}

"[" {
    return T_LEFT_BRACKET;
}

"]" {
    return T_RIGHT_BRACKET;
}

"(" {
    return T_LEFT_PARENTHESIS;
}

")" {
    return T_RIGHT_PARENTHESIS;
}

"{" {
    return T_LEFT_BRACES;
}

"}" {
    return T_RIGHT_BRACES;
}

"||" {
    return T_OR_LOGIC;
}

"&&" {
    return T_AND_LOGIC;
}

"<" {
    return T_LESS_THAN;
}

"<=" {
    return T_LESS_THAN_EQUAL;
}

">" {
    return T_GREATER_THAN;
}

">=" {
    return T_GREATER_THAN_EQUAL;
}

"=" {
    return T_EQUAL;
}

"<>" {
    return T_DIFFERENT;
}

"+" {
    return T_PLUS;
}

"-" {
    return T_MINUS;
}

"*" {
    return T_MULTIPLY;
}

"/" {
    return T_DIVIDE;
}

"^" {
    return T_POWER;
}

{STRING_LITERAL} {
    return T_STRING_LITERAL;
}

{NAME} {
    insert_symbol(yytext);
    return T_NAME;
}

{SINGLE_COMMENT} {
    return T_SINGLE_COMMENT;
}

{MULTI_COMMENT} {
    return T_MULTI_COMMENT;
}

\n    { 
    line_number++;
    return T_END_LINE; 
    }

[ \t\r]+  { /* Ignore whitespace */ }

<<EOF>> {
    return T_EOF;  // Retorna T_EOF quando o EOF for alcançado
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