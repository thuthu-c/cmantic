#include "recursive-parser.hpp"
#include <iostream>

void RecursiveParser::parse(){
    lookaheadtoken = lexer.yylex();
    Program();
}

void RecursiveParser::match(int token){
    if (lookaheadtoken == token) {
        lookaheadtoken = lexer.yylex();
    } else {
        error("Token inesperado");
    }
}
void RecursiveParser::error(const std::string message){
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}

void RecursiveParser::Program(){
    match(T_PROGRAM);
    match(T_NAME);
    match(T_BEGIN);
    Decls();
    match(T_END);
    match(T_EOF);
}

void RecursiveParser::Decls(){
    if (lookaheadtoken == T_VAR || lookaheadtoken == T_PROCEDURE || lookaheadtoken == T_STRUCT) {
        Decl();
        Decls_();
    }
}

void RecursiveParser::Decls_(){
    if (lookaheadtoken == T_SEMICOLON) {
        match(T_SEMICOLON);
        Decls();
    }
}

void RecursiveParser::Decl(){
    switch (lookaheadtoken) {
        case T_VAR: match(T_VAR); match(T_NAME); VarDecl(); break;
        case T_PROCEDURE: match(T_PROCEDURE); match(T_NAME); match(T_LEFT_PARENTHESIS); Params(); match(T_RIGHT_PARENTHESIS); ProcRetDecl(); break;
        case T_STRUCT: match(T_STRUCT); match(T_NAME); match(T_LEFT_BRACES); RecFields(); match(T_RIGHT_BRACES); break;
        default: error("Expected VAR, PROCEDURE, or STRUCT");
    }
}

void RecursiveParser::ProcDecl(){}
void RecursiveParser::RecDecl(){}

void RecursiveParser::VarDecl(){
    switch (lookaheadtoken) {
        case T_COLON: match(T_COLON); Type(); VarInit(); break;
        case T_ASSIGN: match(T_ASSIGN); Exp(); break;
        default: error("Expected NAME or COMMA");
    }
}

void RecursiveParser::VarInit(){
    if (lookaheadtoken == T_ASSIGN) {
        match(T_ASSIGN);
        Exp();
    }
}

void RecursiveParser::ProcRetDecl(){
    if (lookaheadtoken == T_COLON) {
        match(T_COLON);
        Type();
    }
    ProcBody();
}

void RecursiveParser::ProcBody(){
    match(T_BEGIN);
    DeclsOpt();
    StmtList();
    match(T_END);
}

void RecursiveParser::DeclsOpt(){
    if (lookaheadtoken == T_VAR || lookaheadtoken == T_PROCEDURE || lookaheadtoken == T_STRUCT) {
        Decl();
        Decls_();
        match(T_IN);
    } else if (lookaheadtoken == T_IN) {
        match(T_IN);
    }
}

void RecursiveParser::RecFields(){
    if (lookaheadtoken == T_NAME) {
        match(T_NAME);
        match(T_COLON);
        Type();
        RecFields_();
    }
}

void RecursiveParser::RecFields_(){
    if (lookaheadtoken == T_SEMICOLON) {
        match(T_SEMICOLON);
        RecFields();
    }
}

void RecursiveParser::ParamFieldDecl(){}

void RecursiveParser::Params(){
    if (lookaheadtoken == T_NAME) {
        match(T_NAME);
        match(T_COLON);
        Type();
        Params_();
    }
}

void RecursiveParser::Params_(){
    if (lookaheadtoken == T_COMMA) {
        match(T_COMMA);
        Params();
    }
}

void RecursiveParser::StmtList(){
    if (lookaheadtoken == T_DEREF || lookaheadtoken == T_NAME || lookaheadtoken == T_IF || lookaheadtoken == T_UNLESS || lookaheadtoken == T_CASE || lookaheadtoken == T_WHILE || lookaheadtoken == T_RETURN) {
        Stmt();
        StmtList_();
    }
}

void RecursiveParser::StmtList_(){
    if (lookaheadtoken == T_SEMICOLON) {
        match(T_SEMICOLON);
        StmtList();
    }
}

void RecursiveParser::Stmt(){
    switch (lookaheadtoken) {
        case T_DEREF: match(T_DEREF); match(T_LEFT_PARENTHESIS); DeVar(); match(T_RIGHT_PARENTHESIS); match(T_ASSIGN); Exp(); break;
        //ASSIGN_OR_CALL_STMT
        case T_NAME:
            match(T_NAME);
            if (lookaheadtoken == T_LEFT_PARENTHESIS) {
                FuncCall();
            } else {
                Atribute();
                match(T_ASSIGN);
                Exp();
            }
            break;
        case T_IF: match(T_IF); Exp(); match(T_THEN); StmtList(); ElsePart(); match(T_FI); break;
        case T_UNLESS: match(T_UNLESS); Exp(); match(T_DO); StmtList(); ElsePart(); match(T_OD); break;
        case T_CASE: match(T_CASE); Exp(); match(T_OF); Cases(); CaseDefault(); match(T_ESAC); break;
        case T_WHILE: match(T_WHILE); Exp(); match(T_DO); StmtList(); match(T_OD); break;
        case T_RETURN: match(T_RETURN); Exp(); break;
        default: error("Expected statement");
    }
}
void RecursiveParser::AssignOrCallStmt(){}

void RecursiveParser::Exps(){
    if (lookaheadtoken == T_NOT || lookaheadtoken == T_NAME || lookaheadtoken == T_FLOAT_LITERAL || lookaheadtoken == T_INT_LITERAL || lookaheadtoken == T_NULL || lookaheadtoken == T_STRING_LITERAL || lookaheadtoken == T_TRUE || lookaheadtoken == T_FALSE || lookaheadtoken == T_REF || lookaheadtoken == T_DEREF || lookaheadtoken == T_NEW || lookaheadtoken == T_LEFT_PARENTHESIS) {
        Exp();
        Exps_();
    }
}

void RecursiveParser::Exps_(){
    if (lookaheadtoken == T_COMMA) {
        match(T_COMMA);
        Exps();
    }
}
void RecursiveParser::IfStmt(){}

void RecursiveParser::ElsePart(){
    if (lookaheadtoken == T_ELSE) {
        match(T_ELSE);
        StmtList();
    }
}

void RecursiveParser::Cases(){
    Case();
    while (lookaheadtoken == T_SEMICOLON) {
        match(T_SEMICOLON);
        Case();
    }
}

void RecursiveParser::Case_(){}

void RecursiveParser::Case(){
    Interval();
    while (lookaheadtoken == T_COMMA) {
        match(T_COMMA);
        Interval();
    }
    match(T_COLON);
    StmtList();
}

void RecursiveParser::Intervals(){}

void RecursiveParser::Intervals_(){}

void RecursiveParser::Interval(){
    match(T_INT_LITERAL);
    if (lookaheadtoken == T_RANGE) {
        match(T_RANGE);
        match(T_INT_LITERAL);
    }
}

void RecursiveParser::CaseRange(){}

void RecursiveParser::CaseDefault(){
    if (lookaheadtoken == T_OTHERWISE) {
        match(T_OTHERWISE);
        StmtList();
    }
}

void RecursiveParser::WhileStmt(){}
void RecursiveParser::ReturnStmt(){}

void RecursiveParser::Exp(){
    AndExp();
    while (lookaheadtoken == T_OR_LOGIC) {
        match(T_OR_LOGIC);
        AndExp();
    }
}

void RecursiveParser::Exp_(){}

void RecursiveParser::AndExp(){
    NotExp();
    while (lookaheadtoken == T_AND_LOGIC) {
        match(T_AND_LOGIC);
        NotExp();
    }
}

void RecursiveParser::AndExp_(){}

void RecursiveParser::NotExp(){
    if (lookaheadtoken == T_NOT) {
        match(T_NOT);
    } 
    RelExp();
}

void RecursiveParser::RelExp(){
    AddExp();
    while (lookaheadtoken == T_LESS_THAN || lookaheadtoken == T_LESS_THAN_EQUAL || lookaheadtoken == T_GREATER_THAN || lookaheadtoken == T_GREATER_THAN_EQUAL || lookaheadtoken == T_EQUAL || lookaheadtoken == T_DIFFERENT) {
        RelOp();
        AddExp();
    }
}

void RecursiveParser::RelExp_(){}

void RecursiveParser::AddExp(){
    MultExp();
    while (lookaheadtoken == T_PLUS || lookaheadtoken == T_MINUS) {
        AddOp();
        MultExp();
    }
}

void RecursiveParser::AddExp_(){}

void RecursiveParser::MultExp(){
    PowExp();
    while (lookaheadtoken == T_MULTIPLY || lookaheadtoken == T_DIVIDE) {
        MultOp();
        PowExp();
    }
}

void RecursiveParser::MultExp_(){}

void RecursiveParser::PowExp(){
    Value();
    while (lookaheadtoken == T_POWER) {
        match(T_POWER);
        Value();
    }
}

void RecursiveParser::PowExp_(){}

void RecursiveParser::Value(){
    switch (lookaheadtoken) {
        // Literals
        case T_FLOAT_LITERAL: match(T_FLOAT_LITERAL); break;
        case T_INT_LITERAL: match(T_INT_LITERAL); break;
        case T_NULL: match(T_NULL); break;
        case T_STRING_LITERAL: match(T_STRING_LITERAL); break;
        case T_TRUE: match(T_TRUE); break;
        case T_FALSE: match(T_FALSE); break;

        //Var_or_call
        case T_NAME: VarOrCall(); break;

        //Ref_var
        case T_REF: match(T_REF); match(T_LEFT_PARENTHESIS); Var(); match(T_RIGHT_PARENTHESIS); break;

        //Deref_var
        case T_DEREF: match(T_DEREF); match(T_LEFT_PARENTHESIS); DeVar(); match(T_RIGHT_PARENTHESIS); break;

        case T_NEW: match(T_NEW); match(T_NAME); break;
        case T_LEFT_PARENTHESIS: match(T_LEFT_PARENTHESIS); Exp(); match(T_RIGHT_PARENTHESIS); break;
        default: error("Expected value");
    }
}

void RecursiveParser::RefVar(){}
void RecursiveParser::DerefVar(){}

void RecursiveParser::DeVar(){
    if (lookaheadtoken == T_DEREF) {
        match(T_DEREF);
        match(T_LEFT_PARENTHESIS);
        DeVar();
        match(T_RIGHT_PARENTHESIS);
    } else {
        Var();
    }
}

void RecursiveParser::Var(){
    match(T_NAME);
    Atribute();
}

void RecursiveParser::VarOrCall(){
    match(T_NAME);
    FuncCall();
    Atribute();
}

void RecursiveParser::Register(){}

void RecursiveParser::Atribute(){
    if (lookaheadtoken == T_DOT) {
        match(T_DOT);
        match(T_NAME);
        Atribute();
    }
}

void RecursiveParser::FuncCall(){
    if (lookaheadtoken == T_LEFT_PARENTHESIS) {
        match(T_LEFT_PARENTHESIS);
        Exps();
        match(T_RIGHT_PARENTHESIS);
    }
}

void RecursiveParser::Type(){
    switch (lookaheadtoken) {
        case T_BOOL: match(T_BOOL); break;
        case T_INT: match(T_INT); break;
        case T_FLOAT: match(T_FLOAT); break;
        case T_STRING: match(T_STRING); break;
        case T_NAME: match(T_NAME); break;
        case T_REF: match(T_REF); match(T_LEFT_PARENTHESIS); Type(); match(T_RIGHT_PARENTHESIS); break;
        default: error("Expected type");
    }
}

void RecursiveParser::RelOp(){
    switch (lookaheadtoken) {
        case T_LESS_THAN: match(T_LESS_THAN); break;
        case T_LESS_THAN_EQUAL: match(T_LESS_THAN_EQUAL); break;
        case T_GREATER_THAN: match(T_GREATER_THAN); break;
        case T_GREATER_THAN_EQUAL: match(T_GREATER_THAN_EQUAL); break;
        case T_EQUAL: match(T_EQUAL); break;
        case T_DIFFERENT: match(T_DIFFERENT); break;
        default: error("Expected relational operator");
    }
}

void RecursiveParser::AddOp(){
    switch (lookaheadtoken) {
        case T_PLUS: match(T_PLUS); break;
        case T_MINUS: match(T_MINUS); break;
        default: error("Expected addition operator");
    }
}

void RecursiveParser::MultOp(){
    switch (lookaheadtoken) {
        case T_MULTIPLY: match(T_MULTIPLY); break;
        case T_DIVIDE: match(T_DIVIDE); break;
        default: error("Expected multiplication operator");
    }
}

void RecursiveParser::Literal(){}
void RecursiveParser::BoolLiteral(){}