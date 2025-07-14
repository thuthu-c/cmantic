echo -e "Compilando analisador sintático"
bison -d parser.y 
echo -e "Compilando analisador léxico"
flex analyzer.flex
echo -e "Compilando cmantic"
g++ -o cmantic main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp code_generator.cpp -lfl
echo -e "Compilação finalizada com sucesso"