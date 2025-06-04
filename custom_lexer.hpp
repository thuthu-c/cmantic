#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include "parser.tab.hh"

class CustomLexer : public yyFlexLexer
{
  public:
    CustomLexer() : yyFlexLexer() {};
    CustomLexer(std::istream *in_stream) : yyFlexLexer(in_stream)
    {
    }

    int yylex(yy::parser::semantic_type* yylval);
};
