# cmantic
repo para o projeto de compiladores

# Executando

O código é compilado via CMakeLists.txt, dessa forma faça o seguinte (testado em linux via WSL):
```
mkdir build && cd build
cmake ..
make
./lexer ../test_file
```

# Executando o parser - temp

```
bison -d parser.y 
flex analyzer.flex
g++ -o parser main.cpp parser.tab.cc lex.yy.cc symbol_table.cpp type_utils.cpp -lfl
./parser tests/program_1.cmt 
```
