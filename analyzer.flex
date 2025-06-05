%option c++ noyywrap

%option yyclass="CustomLexer"

%{
    #include "parser.tab.hh"
    #include "custom_lexer.hpp"
    #include "symbol_table.hpp"

    #include <iostream>
    #include <string>
    #include <cstring>

    #undef  YY_DECL
    #define YY_DECL int CustomLexer::yylex(yy::parser::semantic_type* yylval)

    extern int line_number;

    void yyerror(CustomLexer& lexer, const char *message);
%}

NAME [a-zA-Z][a-zA-Z0-9_]*
SINGLE_COMMENT "//".*
MULTI_COMMENT "(\*"([^*]|\*+[^)*])*\*+")"
INT_LITERAL [0-9]+
STRING_LITERAL \"([^\\\"\n]|\\.)*\"
FLOAT_LITERAL [0-9]+"."[0-9]+([Ee][-+][0-9]{2})?

%%

{INT_LITERAL} {
    yylval->ival = std::stoi(yytext);
    return yy::parser::token::A_INT_LITERAL;
}

{FLOAT_LITERAL} {
    yylval->ival = std::stof(yytext);
    return yy::parser::token::A_FLOAT_LITERAL;
}

"if" {
    return yy::parser::token::A_IF;
}

"then" {
    return yy::parser::token::A_THEN;
}

"else" {
    return yy::parser::token::A_ELSE;
}

"fi" {
    return yy::parser::token::A_FI;
}

"while" {
    return yy::parser::token::A_WHILE;
}

"do" {
    return yy::parser::token::A_DO;
}

"od" {
    return yy::parser::token::A_OD;
}

"return" {
    return yy::parser::token::A_RETURN;
}

"unless" {
    return yy::parser::token::A_UNLESS;
}

"case" {
    return yy::parser::token::A_CASE;
}

"of" {
    return yy::parser::token::A_OF;
}

"esac" {
    return yy::parser::token::A_ESAC;
}

"otherwise" {
    return yy::parser::token::A_OTHERWISE;
}

"true" {
    return yy::parser::token::A_TRUE;
}

"false" {
    return yy::parser::token::A_FALSE;
}

"float" {
    return yy::parser::token::A_FLOAT;
}

"int" {
    return yy::parser::token::A_INT;
}

"string" {
    return yy::parser::token::A_STRING;
}

"bool" {
    return yy::parser::token::A_BOOL;
}

"null" {
    return yy::parser::token::A_NULL;
}

"program" {
    return yy::parser::token::A_PROGRAM;
}

"begin" {
    return yy::parser::token::A_BEGIN;
}

"end" {
    return yy::parser::token::A_END;
}

"var" {
    return yy::parser::token::A_VAR;
}

"procedure" {
    return yy::parser::token::A_PROCEDURE;
}

"struct" {
    return yy::parser::token::A_STRUCT;
}

"in" {
    return yy::parser::token::A_IN;
}

"not" {
    return yy::parser::token::A_NOT;
}

"new" {
    return yy::parser::token::A_NEW;
}

"ref" {
    return yy::parser::token::A_REF;
}

"deref" {
    return yy::parser::token::A_DEREF;
}

";" {
    return ';';
}

":=" {
    return yy::parser::token::A_ASSIGN;
}

":" {
    return ':';
}

"," {
    return ',';
}

".." {
    return yy::parser::token::A_RANGE;
}

"." {
    return '.';
}

"[" {
    return '[';
}

"]" {
    return ']';
}

"(" {
    return '(';
}

")" {
    return ')';
}

"{" {
    return '{';
}

"}" {
    return '}';
}

"||" {
    return yy::parser::token::A_OR_LOGIC;
}

"|" {
    return '|';
}

"&&" {
    return yy::parser::token::A_AND_LOGIC;
}

"<=" {
    return yy::parser::token::A_LESS_THAN_EQUAL;
}

"<" {
    return '<';
}

">=" {
    return yy::parser::token::A_GREATER_THAN_EQUAL;
}

">" {
    return '>';
}

"==" {
    return yy::parser::token::A_EQUAL;
}

"=" {
    return '=';
}

"<>" {
    return yy::parser::token::A_DIFFERENT;
}

"+" {
    return '+';
}

"-" {
    return '-';
}

"*" {
    return '*';
}

"/" {
    return '/';
}

"^" {
    return '^';
}

{STRING_LITERAL} {
    yylval->sval = new std::string(yytext + 1, strlen(yytext) - 2);
    return yy::parser::token::A_STRING_LITERAL;
}

{NAME} {
    yylval->sval = new std::string(yytext);
    return yy::parser::token::A_NAME;
}

{SINGLE_COMMENT} {
    std::cout << "Single comment: " << yytext << std::endl;
}

{MULTI_COMMENT} {
    std::cout << "Multi comment: " << yytext << std::endl;
}

\n    { 
    line_number++;
    }

[ \t\r]+  { /* Ignore whitespace */ }

.     { yyerror(*this, "Invalid character"); }

%%

void yyerror(CustomLexer& lexer, const char *message)
{
    std::cerr << "Error: \"" << message << "\" in line " << line_number
              << ". Token = " << lexer.YYText() << std::endl;
    exit(1);
}


/* int CustomLexer::yywrap() {
    return 1;
} */