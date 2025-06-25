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
    #define YY_DECL int CustomLexer::yylex(yy::parser::semantic_type* yylval, yy::parser::location_type* yylloc)

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
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    yylval->ival = std::stoi(yytext);
    return yy::parser::token::A_INT_LITERAL;
}

{FLOAT_LITERAL} {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    yylval->fval = std::stof(yytext);
    return yy::parser::token::A_FLOAT_LITERAL;
}

"if" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_IF;
}

"then" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_THEN;
}

"else" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_ELSE;
}

"fi" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_FI;
}

"while" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_WHILE;
}

"do" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_DO;
}

"od" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_OD;
}

"return" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_RETURN;
}

"unless" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_UNLESS;
}

"case" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_CASE;
}

"of" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_OF;
}

"esac" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_ESAC;
}

"otherwise" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_OTHERWISE;
}

"true" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_TRUE;
}

"false" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_FALSE;
}

"float" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_FLOAT;
}

"int" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_INT;
}

"string" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_STRING;
}

"bool" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_BOOL;
}

"null" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_NULL;
}

"program" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_PROGRAM;
}

"begin" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_BEGIN;
}

"end" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_END;
}

"var" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_VAR;
}

"procedure" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_PROCEDURE;
}

"struct" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_STRUCT;
}

"in" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_IN;
}

"not" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_NOT;
}

"new" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_NEW;
}

"ref" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_REF;
}

"deref" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_DEREF;
}

";" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return ';';
}

":=" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_ASSIGN;
}

":" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return ':';
}

"," {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return ',';
}

".." {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_RANGE;
}

"." {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '.';
}

"[" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '[';
}

"]" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return ']';
}

"(" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '(';
}

")" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return ')';
}

"{" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '{';
}

"}" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '}';
}

"||" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_OR_LOGIC;
}

"|" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '|';
}

"&&" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_AND_LOGIC;
}

"<=" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_LESS_THAN_EQUAL;
}

"<" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '<';
}

">=" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_GREATER_THAN_EQUAL;
}

">" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '>';
}

"==" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_EQUAL;
}

"=" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '=';
}

"<>" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return yy::parser::token::A_DIFFERENT;
}

"+" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '+';
}

"-" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '-';
}

"*" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '*';
}

"/" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '/';
}

"^" {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    return '^';
}

{STRING_LITERAL} {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    yylval->sval = new std::string(yytext + 1, strlen(yytext) - 2);
    return yy::parser::token::A_STRING_LITERAL;
}

{NAME} {
    yylloc->begin.line = m_line; yylloc->begin.column = m_col;
    m_col += yyleng;
    yylloc->end.line = m_line; yylloc->end.column = m_col - 1;
    yylval->sval = new std::string(yytext);
    return yy::parser::token::A_NAME;
}

{SINGLE_COMMENT} {
    std::cout << "Single comment: " << yytext << std::endl;
    m_col += yyleng;
}

{MULTI_COMMENT} {
    std::cout << "Multi comment: " << yytext << std::endl;
    for(int i = 0; yytext[i] != '\0'; i++) {
        if(yytext[i] == '\n') {
            m_line++;
            m_col = 1;
        } else {
            m_col++;
        }
    }
}

\n          { m_line++; m_col = 1; }

[ \t\r]+    { m_col += yyleng; }


.     { yyerror(*this, "Caractere invalido"); }

%%

void yyerror(CustomLexer& lexer, const char *message)
{
    std::cerr << "Error: \"" << message << "\"  na Linha " << lexer.getLine() << ", Coluna " << lexer.getColumn()
              << ". Token = " << lexer.YYText() << std::endl;
    exit(1);
}


/* int CustomLexer::yywrap() {
    return 1;
} */