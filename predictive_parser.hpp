#pragma once

#include "program_map.hpp"
#include "custom_lexer.hpp"
#include "table.hpp"
#include <stack>
#include <vector>

class PredictiveParser : public CustomLexer
{
  public:
    PredictiveParser(std::istream *in_stream) : CustomLexer(in_stream), cur_token_id(P_PROGRAM)
    {
      initialize_table();
    }
    bool parse();

  private:
    int cur_token_id;
    void predict(std::stack<int> &stack, int non_terminal_id, int terminal_id);
    void match_nonterminal(int id_from_stack, int id_from_lexic);
    void advance_token();
};
