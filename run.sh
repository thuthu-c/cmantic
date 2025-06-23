bison -d parser.y 
flex analyzer.flex
g++ -o parser main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp -lfl