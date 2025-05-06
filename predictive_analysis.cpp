#include "predictive_analysis.h"

std::vector<int> prediction_table[][];
int pointed_token;

int get_cur_token(){
    return pointed_token;
}

void advance_token(){
    //todo
}

void match_nonterminal(int id_from_stack, int id_from_lexic){
    if(id_from_stack == id_from_lexic){
        advance_token();
    }else{
        //explode
    }
}

void predict(std::stack<int> &stack, int id_from_stack, int id_from_lexic){
    std::vector<int> production = prediction_table[id_from_stack][-id_from_lexic];

    if(production.empty()){
        // explode
    }else{
        for(int symbol : production){
            stack.push(symbol);
        }
    }
}

void preditive_analisys(){
    int cur_token_id = 1;
    int cur_symbol_id;
    std::stack<int> symbol_stack;
    symbol_stack.push(1);


    while (cur_token_id != 0){
        cur_token_id = get_cur_token();
        cur_symbol_id = symbol_stack.top();
        symbol_stack.pop();

        if(cur_token_id < 0){
            match_nonterminal(cur_symbol_id ,cur_token_id);
        }else if(cur_token_id > 0){
            predict(symbol_stack, cur_symbol_id ,cur_token_id)
        }
    }

    if(!symbol_stack.empty()){
        // explode
    }
    
}