#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

class CustomLexer : public yyFlexLexer
{
  public:
    CustomLexer() : yyFlexLexer() {};
    CustomLexer(std::istream *in_stream) : yyFlexLexer(in_stream)
    {
    }

    int yylex(yy::parser::semantic_type* yylval);
};
