#pragma once

#undef yyFlexLexer
#define yyFlexLexer MyFlexLexer
#include <FlexLexer.h>

class CustomLexer : public yyFlexLexer
{
public:
    // CustomLexer() : yyFlexLexer() {}
    CustomLexer(std::istream* in_stream) : yyFlexLexer(in_stream) {}

    int yylex() {
        return yyFlexLexer::yylex(); 
    }
};

