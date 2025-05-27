#pragma once
#include <vector>
#include <string>
#include <map>
#include "program_map.hpp"

extern std::vector<std::vector<std::vector<int>>> table;
extern std::map<int, std::string> symbol_map;

void initialize_table();