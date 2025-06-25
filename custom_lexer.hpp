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

    int yylex(yy::parser::semantic_type* yylval, yy::parser::location_type* yylloc);

    int getLine() const { return m_line; }
    int getColumn() const { return m_col; }

  private:
    int m_line = 1;
    int m_col = 1;
};
