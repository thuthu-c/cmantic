cmake_minimum_required(VERSION 3.12)

project(SyntaxAnalyzerProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar pacotes Flex e Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# --- Arquivos Gerados ---
# Definir os caminhos para os arquivos que serão gerados pelo Flex e Bison
# É uma boa prática colocá-los no diretório binário de compilação (CMAKE_CURRENT_BINARY_DIR)
set(LEXER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(PARSER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Criar os diretórios se não existirem (útil para IDEs)
file(MAKE_DIRECTORY ${LEXER_OUTPUT_DIR})
file(MAKE_DIRECTORY ${PARSER_OUTPUT_DIR})

# Arquivo do analisador léxico (Flex)
set(LEXER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.flex) # Seu arquivo .flex
set(LEXER_CPP_FILE ${LEXER_OUTPUT_DIR}/lex.yy.cc) # Arquivo C++ gerado pelo Flex
set(LEXER_HPP_FILE ${LEXER_OUTPUT_DIR}/lex.yy.hh) # Cabeçalho opcional do Flex (se gerado)

# Arquivo do analisador sintático (Bison)
set(PARSER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser.y)    # Seu arquivo .y
set(PARSER_CPP_FILE ${PARSER_OUTPUT_DIR}/parser.tab.cc) # Arquivo C++ gerado pelo Bison
set(PARSER_HPP_FILE ${PARSER_OUTPUT_DIR}/parser.tab.hh) # Cabeçalho C++ gerado pelo Bison (com tokens, etc.)

# --- Comandos de Geração ---

# Gerar analisador léxico com Flex
# A opção --header-file é útil para C++ se o lexer precisa de uma classe declarada
# ou se você quer um cabeçalho explícito.
add_custom_command(
    OUTPUT ${LEXER_CPP_FILE} ${LEXER_HPP_FILE} # Adicione LEXER_HPP_FILE se seu Flex gera um
    COMMAND ${FLEX_EXECUTABLE} --outfile=${LEXER_CPP_FILE}  ${LEXER_FILE}
    DEPENDS ${LEXER_FILE}
    COMMENT "Generating C++ lexer from ${LEXER_FILE}"
)

# Gerar analisador sintático com Bison
# A opção -d ou --defines gera o arquivo de cabeçalho (parser.tab.hpp por padrão com C++)
# A opção --language=c++ é importante se não estiver no arquivo .y
# A opção --output é para o arquivo .cpp gerado
# O nome do arquivo de cabeçalho gerado pelo Bison pode ser controlado
# com --defines=arquivo.hpp ou será o padrão.
add_custom_command(
    OUTPUT ${PARSER_CPP_FILE} ${PARSER_HPP_FILE}
    COMMAND ${BISON_EXECUTABLE} -d --output=${PARSER_CPP_FILE} --defines=${PARSER_HPP_FILE} ${PARSER_FILE}
    DEPENDS ${PARSER_FILE}
    COMMENT "Generating C++ parser from ${PARSER_FILE}"
)

# --- Compilação do Executável ---

# Adicionar o executável
add_executable(syntax_analyzer
    # Arquivos gerados
    ${LEXER_CPP_FILE}
    ${PARSER_CPP_FILE}

    # Seus arquivos de código fonte
    main.cpp
    symbol_table.cpp
    logger.cpp
    # Adicione outros arquivos .cpp se necessário
)

# Incluir diretórios para cabeçalhos
target_include_directories(syntax_analyzer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}   # Para seus cabeçalhos como custom_lexer.hpp (se ainda existir), symbol_table.hpp, etc.
    ${PARSER_OUTPUT_DIR}          # Para parser.tab.hpp
    ${LEXER_OUTPUT_DIR}           # Para analyzer.flex.hpp (se gerado e usado)
)

# Se o Flex ou Bison gerarem arquivos que precisam ser explicitamente compilados
# e não são automaticamente pegos por serem .cpp (o que geralmente são),
# você pode precisar de um add_custom_target ou garantir que os outputs
# da custom_command sejam adicionados como fontes ao add_executable.
# A forma acima com ${LEXER_CPP_FILE} e ${PARSER_CPP_FILE} no add_executable
# geralmente funciona bem.

# Opcional: Limpar arquivos gerados no 'make clean'
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${LEXER_CPP_FILE} ${LEXER_HPP_FILE} ${PARSER_CPP_FILE} ${PARSER_HPP_FILE}
)