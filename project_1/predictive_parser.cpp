#include "predictive_parser.hpp"
#include "logger.hpp"
#include <sstream>

void PredictiveParser::advance_token()
{
    cur_token_id = yylex();
}

void PredictiveParser::match_nonterminal(int id_from_stack, int id_from_lexic)
{
    if (id_from_stack == -1)
        return; // it is the empty token
    if (id_from_stack == id_from_lexic)
    {
        advance_token();
        return;
    }

    std::stringstream ss;
    ss << "Couldn't match non-terminal tokens. Stack Token: " << id_from_stack << ", Current Token: " << id_from_lexic;
    logger.logError(ss.str());
}

void PredictiveParser::predict(std::stack<int> &stack, int non_terminal_id, int terminal_id)
{
    std::vector<int> production = table[non_terminal_id][-terminal_id];
    if (production.empty())
    {
        logger.logError("Production list is empty");
    }
    for (int symbol : production)
    {
        stack.push(symbol);
    }
}

bool PredictiveParser::parse()
{
    int cur_production_id;
    bool not_explode;
    std::stack<int> symbol_stack;
    symbol_stack.push(P_PROGRAM);

    while (cur_token_id != 0)
    {
        cur_production_id = symbol_stack.top();
        symbol_stack.pop();

        if (cur_token_id < 0)
        {
            match_nonterminal(cur_production_id, cur_token_id);
        }
        else if (cur_token_id > 0)
        {
            predict(symbol_stack, cur_production_id, cur_token_id);
        }
    }

    if (!symbol_stack.empty())
    {
        return false;
    }

    return true;
}