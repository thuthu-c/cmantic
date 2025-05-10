#include "recursive_parser.hpp"
#include <iostream>
#include "logger.hpp"

void RecursiveParser::parse()
{
    lookaheadtoken = yylex();
    Program();
}

void RecursiveParser::match(int token)
{
    auto expectedIt = ATOMIC_SYMBOLS_STRINGS.find(token);
    auto lookaheadIt = ATOMIC_SYMBOLS_STRINGS.find(lookaheadtoken);

    std::string expectedStr = (expectedIt != ATOMIC_SYMBOLS_STRINGS.end()) ? expectedIt->second : "<unknown>";
    std::string lookaheadStr = (lookaheadIt != ATOMIC_SYMBOLS_STRINGS.end()) ? lookaheadIt->second : "<unknown>";

    logger.logTrace("Expected token: " + expectedStr + ", Lookahead token: " + lookaheadStr);

    if (lookaheadtoken == token)
    {
        lookaheadtoken = yylex();
    }
    else
    {
        logger.logError("Token inesperado");
    }
}

void RecursiveParser::Program()
{
    match(A_PROGRAM);
    match(A_NAME);
    match(A_BEGIN);
    Decls();
    match(A_END);
    match(A_EOF);
}

void RecursiveParser::Decls()
{
    if (lookaheadtoken == A_VAR || lookaheadtoken == A_PROCEDURE || lookaheadtoken == A_STRUCT)
    {
        Decl();
        Decls_();
    }
}

void RecursiveParser::Decls_()
{
    if (lookaheadtoken == A_SEMICOLON)
    {
        match(A_SEMICOLON);
        Decls();
    }
}

void RecursiveParser::Decl()
{
    switch (lookaheadtoken)
    {
    case A_VAR:
        match(A_VAR);
        match(A_NAME);
        VarDecl();
        break;
    case A_PROCEDURE:
        match(A_PROCEDURE);
        match(A_NAME);
        match(A_LEFA_PARENTHESIS);
        Params();
        match(A_RIGHA_PARENTHESIS);
        ProcRetDecl();
        break;
    case A_STRUCT:
        match(A_STRUCT);
        match(A_NAME);
        match(A_LEFA_BRACES);
        RecFields();
        match(A_RIGHA_BRACES);
        break;
    default:
        logger.logError("Expected VAR, PROCEDURE, or STRUCT");
    }
}

void RecursiveParser::ProcDecl()
{
}
void RecursiveParser::RecDecl()
{
}

void RecursiveParser::VarDecl()
{
    switch (lookaheadtoken)
    {
    case A_COLON:
        match(A_COLON);
        Type();
        VarInit();
        break;
    case A_ASSIGN:
        match(A_ASSIGN);
        Exp();
        break;
    default:
        logger.logError("Expected NAME or COMMA");
    }
}

void RecursiveParser::VarInit()
{
    if (lookaheadtoken == A_ASSIGN)
    {
        match(A_ASSIGN);
        Exp();
    }
}

void RecursiveParser::ProcRetDecl()
{
    if (lookaheadtoken == A_COLON)
    {
        match(A_COLON);
        Type();
    }
    ProcBody();
}

void RecursiveParser::ProcBody()
{
    match(A_BEGIN);
    DeclsOpt();
    StmtList();
    match(A_END);
}

void RecursiveParser::DeclsOpt()
{
    if (lookaheadtoken == A_VAR || lookaheadtoken == A_PROCEDURE || lookaheadtoken == A_STRUCT)
    {
        Decl();
        Decls_();
        match(A_IN);
    }
    else if (lookaheadtoken == A_IN)
    {
        match(A_IN);
    }
}

void RecursiveParser::RecFields()
{
    if (lookaheadtoken == A_NAME)
    {
        match(A_NAME);
        match(A_COLON);
        Type();
        RecFields_();
    }
}

void RecursiveParser::RecFields_()
{
    if (lookaheadtoken == A_SEMICOLON)
    {
        match(A_SEMICOLON);
        RecFields();
    }
}

void RecursiveParser::ParamFieldDecl()
{
}

void RecursiveParser::Params()
{
    if (lookaheadtoken == A_NAME)
    {
        match(A_NAME);
        match(A_COLON);
        Type();
        Params_();
    }
}

void RecursiveParser::Params_()
{
    if (lookaheadtoken == A_COMMA)
    {
        match(A_COMMA);
        Params();
    }
}

void RecursiveParser::StmtList()
{
    if (lookaheadtoken == A_DEREF || lookaheadtoken == A_NAME || lookaheadtoken == A_IF || lookaheadtoken == A_UNLESS ||
        lookaheadtoken == A_CASE || lookaheadtoken == A_WHILE || lookaheadtoken == A_RETURN)
    {
        Stmt();
        StmtList_();
    }
}

void RecursiveParser::StmtList_()
{
    if (lookaheadtoken == A_SEMICOLON)
    {
        match(A_SEMICOLON);
        StmtList();
    }
}

void RecursiveParser::Stmt()
{
    switch (lookaheadtoken)
    {
    case A_DEREF:
        match(A_DEREF);
        match(A_LEFA_PARENTHESIS);
        DeVar();
        match(A_RIGHA_PARENTHESIS);
        match(A_ASSIGN);
        Exp();
        break;
    // ASSIGN_OR_CALL_STMT
    case A_NAME:
        match(A_NAME);
        if (lookaheadtoken == A_LEFA_PARENTHESIS)
        {
            FuncCall();
        }
        else
        {
            Atribute();
            match(A_ASSIGN);
            Exp();
        }
        break;
    case A_IF:
        match(A_IF);
        Exp();
        match(A_THEN);
        StmtList();
        ElsePart();
        match(A_FI);
        break;
    case A_UNLESS:
        match(A_UNLESS);
        Exp();
        match(A_DO);
        StmtList();
        ElsePart();
        match(A_OD);
        break;
    case A_CASE:
        match(A_CASE);
        Exp();
        match(A_OF);
        Cases();
        CaseDefault();
        match(A_ESAC);
        break;
    case A_WHILE:
        match(A_WHILE);
        Exp();
        match(A_DO);
        StmtList();
        match(A_OD);
        break;
    case A_RETURN:
        match(A_RETURN);
        Exp();
        break;
    default:
        logger.logError("Expected statement");
    }
}
void RecursiveParser::AssignOrCallStmt()
{
}

void RecursiveParser::Exps()
{
    if (lookaheadtoken == A_NOT || lookaheadtoken == A_NAME || lookaheadtoken == A_FLOAA_LITERAL ||
        lookaheadtoken == A_INA_LITERAL || lookaheadtoken == A_NULL || lookaheadtoken == A_STRING_LITERAL ||
        lookaheadtoken == A_TRUE || lookaheadtoken == A_FALSE || lookaheadtoken == A_REF || lookaheadtoken == A_DEREF ||
        lookaheadtoken == A_NEW || lookaheadtoken == A_LEFA_PARENTHESIS)
    {
        Exp();
        Exps_();
    }
}

void RecursiveParser::Exps_()
{
    if (lookaheadtoken == A_COMMA)
    {
        match(A_COMMA);
        Exps();
    }
}
void RecursiveParser::IfStmt()
{
}

void RecursiveParser::ElsePart()
{
    if (lookaheadtoken == A_ELSE)
    {
        match(A_ELSE);
        StmtList();
    }
}

void RecursiveParser::Cases()
{
    Case();
    while (lookaheadtoken == A_SEMICOLON)
    {
        match(A_SEMICOLON);
        Case();
    }
}

void RecursiveParser::Case_()
{
}

void RecursiveParser::Case()
{
    Interval();
    while (lookaheadtoken == A_COMMA)
    {
        match(A_COMMA);
        Interval();
    }
    match(A_COLON);
    StmtList();
}

void RecursiveParser::Intervals()
{
}

void RecursiveParser::Intervals_()
{
}

void RecursiveParser::Interval()
{
    match(A_INA_LITERAL);
    if (lookaheadtoken == A_RANGE)
    {
        match(A_RANGE);
        match(A_INA_LITERAL);
    }
}

void RecursiveParser::CaseRange()
{
}

void RecursiveParser::CaseDefault()
{
    if (lookaheadtoken == A_OTHERWISE)
    {
        match(A_OTHERWISE);
        StmtList();
    }
}

void RecursiveParser::WhileStmt()
{
}
void RecursiveParser::ReturnStmt()
{
}

void RecursiveParser::Exp()
{
    AndExp();
    while (lookaheadtoken == A_OR_LOGIC)
    {
        match(A_OR_LOGIC);
        AndExp();
    }
}

void RecursiveParser::Exp_()
{
}

void RecursiveParser::AndExp()
{
    NotExp();
    while (lookaheadtoken == A_AND_LOGIC)
    {
        match(A_AND_LOGIC);
        NotExp();
    }
}

void RecursiveParser::AndExp_()
{
}

void RecursiveParser::NotExp()
{
    if (lookaheadtoken == A_NOT)
    {
        match(A_NOT);
    }
    RelExp();
}

void RecursiveParser::RelExp()
{
    AddExp();
    while (lookaheadtoken == A_LESS_THAN || lookaheadtoken == A_LESS_THAN_EQUAL || lookaheadtoken == A_GREATER_THAN ||
           lookaheadtoken == A_GREATER_THAN_EQUAL || lookaheadtoken == A_EQUAL || lookaheadtoken == A_DIFFERENT)
    {
        RelOp();
        AddExp();
    }
}

void RecursiveParser::RelExp_()
{
}

void RecursiveParser::AddExp()
{
    MultExp();
    while (lookaheadtoken == A_PLUS || lookaheadtoken == A_MINUS)
    {
        AddOp();
        MultExp();
    }
}

void RecursiveParser::AddExp_()
{
}

void RecursiveParser::MultExp()
{
    PowExp();
    while (lookaheadtoken == A_MULTIPLY || lookaheadtoken == A_DIVIDE)
    {
        MultOp();
        PowExp();
    }
}

void RecursiveParser::MultExp_()
{
}

void RecursiveParser::PowExp()
{
    Value();
    while (lookaheadtoken == A_POWER)
    {
        match(A_POWER);
        Value();
    }
}

void RecursiveParser::PowExp_()
{
}

void RecursiveParser::Value()
{
    switch (lookaheadtoken)
    {
    // Literals
    case A_FLOAA_LITERAL:
        match(A_FLOAA_LITERAL);
        break;
    case A_INA_LITERAL:
        match(A_INA_LITERAL);
        break;
    case A_NULL:
        match(A_NULL);
        break;
    case A_STRING_LITERAL:
        match(A_STRING_LITERAL);
        break;
    case A_TRUE:
        match(A_TRUE);
        break;
    case A_FALSE:
        match(A_FALSE);
        break;

    // Var_or_call
    case A_NAME:
        VarOrCall();
        break;

    // Ref_var
    case A_REF:
        match(A_REF);
        match(A_LEFA_PARENTHESIS);
        Var();
        match(A_RIGHA_PARENTHESIS);
        break;

    // Deref_var
    case A_DEREF:
        match(A_DEREF);
        match(A_LEFA_PARENTHESIS);
        DeVar();
        match(A_RIGHA_PARENTHESIS);
        break;

    case A_NEW:
        match(A_NEW);
        match(A_NAME);
        break;
    case A_LEFA_PARENTHESIS:
        match(A_LEFA_PARENTHESIS);
        Exp();
        match(A_RIGHA_PARENTHESIS);
        break;
    default:
        logger.logError("Expected value");
    }
}

void RecursiveParser::RefVar()
{
}
void RecursiveParser::DerefVar()
{
}

void RecursiveParser::DeVar()
{
    if (lookaheadtoken == A_DEREF)
    {
        match(A_DEREF);
        match(A_LEFA_PARENTHESIS);
        DeVar();
        match(A_RIGHA_PARENTHESIS);
    }
    else
    {
        Var();
    }
}

void RecursiveParser::Var()
{
    match(A_NAME);
    Atribute();
}

void RecursiveParser::VarOrCall()
{
    match(A_NAME);
    FuncCall();
    Atribute();
}

void RecursiveParser::Register()
{
}

void RecursiveParser::Atribute()
{
    if (lookaheadtoken == A_DOT)
    {
        match(A_DOT);
        match(A_NAME);
        Atribute();
    }
}

void RecursiveParser::FuncCall()
{
    if (lookaheadtoken == A_LEFA_PARENTHESIS)
    {
        match(A_LEFA_PARENTHESIS);
        Exps();
        match(A_RIGHA_PARENTHESIS);
    }
}

void RecursiveParser::Type()
{
    switch (lookaheadtoken)
    {
    case A_BOOL:
        match(A_BOOL);
        break;
    case A_INT:
        match(A_INT);
        break;
    case A_FLOAT:
        match(A_FLOAT);
        break;
    case A_STRING:
        match(A_STRING);
        break;
    case A_NAME:
        match(A_NAME);
        break;
    case A_REF:
        match(A_REF);
        match(A_LEFA_PARENTHESIS);
        Type();
        match(A_RIGHA_PARENTHESIS);
        break;
    default:
        logger.logError("Expected type");
    }
}

void RecursiveParser::RelOp()
{
    switch (lookaheadtoken)
    {
    case A_LESS_THAN:
        match(A_LESS_THAN);
        break;
    case A_LESS_THAN_EQUAL:
        match(A_LESS_THAN_EQUAL);
        break;
    case A_GREATER_THAN:
        match(A_GREATER_THAN);
        break;
    case A_GREATER_THAN_EQUAL:
        match(A_GREATER_THAN_EQUAL);
        break;
    case A_EQUAL:
        match(A_EQUAL);
        break;
    case A_DIFFERENT:
        match(A_DIFFERENT);
        break;
    default:
        logger.logError("Expected relational operator");
    }
}

void RecursiveParser::AddOp()
{
    switch (lookaheadtoken)
    {
    case A_PLUS:
        match(A_PLUS);
        break;
    case A_MINUS:
        match(A_MINUS);
        break;
    default:
        logger.logError("Expected addition operator");
    }
}

void RecursiveParser::MultOp()
{
    switch (lookaheadtoken)
    {
    case A_MULTIPLY:
        match(A_MULTIPLY);
        break;
    case A_DIVIDE:
        match(A_DIVIDE);
        break;
    default:
        logger.logError("Expected multiplication operator");
    }
}

void RecursiveParser::Literal()
{
}
void RecursiveParser::BoolLiteral()
{
}