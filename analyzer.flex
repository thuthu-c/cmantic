%option c++ noyywrap

%option yyclass="CustomLexer"

%{
    #include "parser.tab.hh"
    #include "custom_lexer.hpp"
    #include "program_map.hpp"
    #include "symbol_table.hpp"
    #include <iostream>

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
    return A_INT_LITERAL;
}

{FLOAT_LITERAL} {
    yylval->ival = std::stof(yytext);
    return A_FLOAT_LITERAL;
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
    printf("Program keyword found\n");
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
    return ';';
}

":" {
    return ':';
}

"," {
    return ',';
}

":=" {
    return A_ASSIGN;
}

".." {
    return A_RANGE;
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
    return A_OR_LOGIC;
}

"|" {
    return '|';
}

"&&" {
    return A_AND_LOGIC;
}

"<" {
    return '<';
}

"<=" {
    return A_LESS_THAN_EQUAL;
}

">" {
    return '>';
}

">=" {
    return A_GREATER_THAN_EQUAL;
}

"==" {
    return A_EQUAL;
}

"=" {
    return '=';
}

"<>" {
    return A_DIFFERENT;
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
    yylval->sval = std::string(yytext + 1, yytext + strlen(yytext) - 2).c_str();
    return A_STRING_LITERAL;
}

{NAME} {
    insert_symbol(yytext);
    return A_NAME;
}

{SINGLE_COMMENT} {
    printf("Single comment: %s\n", yytext);
}

{MULTI_COMMENT} {
    printf("Multi comment: %s\n", yytext);
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