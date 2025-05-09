#include "predictive_analysis.hpp"
#include "table.hpp"

int pointed_token = 1;

void advance_token(){
    pointed_token = yylex();
}

bool match_nonterminal(int id_from_stack, int id_from_lexic){
    if(id_from_stack == -1) return true; // it is the empty token
    if(id_from_stack == id_from_lexic){
        advance_token();
        return true;
    }
    return false;
}

bool predict(std::stack<int> &stack, int non_terminal_id, int terminal_id){
    std::vector<int> production = table[non_terminal_id][-terminal_id];
    if(production.empty()){
        return false;
    }
    for(int symbol : production){
        stack.push(symbol);
    }
    return true;
}

bool preditive_analisys(){
    int cur_symbol_id;
    bool not_explode;
    std::stack<int> symbol_stack;
    symbol_stack.push(1);


    while (pointed_token != 0){
        cur_symbol_id = symbol_stack.top();
        symbol_stack.pop();

        if(cur_token_id < 0){
            not_explode = match_nonterminal(cur_symbol_id ,cur_token_id);
            if(!not_explode){
                return false;
            }
        }else if(cur_token_id > 0){
            not_explode = predict(symbol_stack, cur_symbol_id ,cur_token_id);
            if(!not_explode){
                return false;
            }
        }
    }

    if(!symbol_stack.empty()){
        return false;
    }

    return true;
    
}