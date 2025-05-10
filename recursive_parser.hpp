#pragma once

#include <string.h>
#include "program_map.hpp"
#include "custom_lexer.hpp"

class RecursiveParser : public CustomLexer {
    public:
        RecursiveParser(std::istream* in_stream) : CustomLexer(in_stream), lookaheadtoken(-1) {}
        void parse();

    private:
        int lookaheadtoken;

        void match(int token);

        void Program();
        void Decls();
        void Decls_();
        void Decl();
        void VarDecl();
        void ProcDecl();
        void RecDecl();
        void VarInit();
        void ProcRetDecl();
        void ProcBody();
        void DeclsOpt();
        void RecFields();
        void RecFields_();
        void ParamFieldDecl();
        void Params();
        void Params_();
        void StmtList();
        void StmtList_();
        void Stmt();
        void AssignOrCallStmt();
        void Exps();
        void Exps_();
        void IfStmt();
        void ElsePart();
        void Cases();
        void Case_();
        void Case();
        void Intervals();
        void Intervals_();
        void Interval();
        void CaseRange();
        void CaseDefault();
        void WhileStmt();
        void ReturnStmt();
        void Exp();
        void Exp_();
        void AndExp();
        void AndExp_();
        void NotExp();
        void RelExp();
        void RelExp_();
        void AddExp();
        void AddExp_();
        void MultExp();
        void MultExp_();
        void PowExp();
        void PowExp_();
        void Value();
        void RefVar();
        void DerefVar();
        void DeVar();
        void Var();
        void VarOrCall();
        void Register();
        void Atribute();
        void FuncCall();
        void Type();
        void RelOp();
        void AddOp();
        void MultOp();
        void Literal();
        void BoolLiteral();
};