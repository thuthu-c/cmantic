#!/bin/bash

# ============================================================================
# Script para executar a bateria de testes do Compilador Cmantic
#
# Para testes VÁLIDOS:
# 1. Gera o código C com o compilador Cmantic.
# 2. Compila o código C gerado com o gcc.
# 3. Executa o programa compilado.
#    -> O script irá parar imediatamente se qualquer uma dessas etapas falhar.
#
# Para testes INVÁLIDOS:
# 1. Tenta gerar código com o compilador Cmantic.
#    -> É esperado que esta etapa falhe, gerando um erro.
# ============================================================================

# --- Configuração ---
EXECUTABLE="./cmantic"
VALID_DIR="tests/valid"
INVALID_DIR="tests/invalid"
OUTPUT_DIR="output"

# --- Cores ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # Sem Cor

# --- Lógica de Erro ---
# Sai imediatamente se qualquer comando falhar. Essencial para os testes válidos.
set -e

# --- Preparação ---
# Garante que o diretório de saída existe
mkdir -p "$OUTPUT_DIR"

# Verificação de Existência do Executável Cmantic
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Erro: O executável '$EXECUTABLE' não foi encontrado!${NC}"
    echo "Por favor, compile o projeto Cmantic antes de executar os testes."
    exit 1
fi

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}  INICIANDO BATERIA DE TESTES DO CMANTIC ${NC}"
echo -e "${BLUE}=========================================${NC}"
echo ""

# --- Testes Válidos ---
echo -e "${GREEN}--- INICIANDO CASOS DE TESTE VÁLIDOS ---${NC}"
echo "Para cada teste, o código C será gerado, compilado e executado."
echo "O script irá parar ao primeiro erro."
echo "------------------------------------------"

for test_file in "$VALID_DIR"/*.cmt; do
    if [ -f "$test_file" ]; then
        echo ""
        # Extrai o nome base do arquivo, sem o diretório e a extensão .cmt
        base_name=$(basename "$test_file" .cmt)
        c_file="$OUTPUT_DIR/$base_name.c"
        executable_file="$OUTPUT_DIR/$base_name"

        echo -e "${YELLOW}>> [1/3] Gerando código C para: ${test_file}${NC}"
        $EXECUTABLE "$test_file"

        # Verifica se o arquivo .c foi realmente gerado antes de continuar
        if [ ! -f "$c_file" ]; then
            echo -e "${RED}ERRO: Compilador Cmantic não gerou o arquivo de saída esperado: $c_file${NC}"
            exit 1
        fi

        echo -e "${YELLOW}>> [2/3] Compilando arquivo C gerado: ${c_file}${NC}"
        gcc "$c_file" -o "$executable_file" -lm # A flag -lm é para linkar a biblioteca de matemática, se necessário

        echo -e "${YELLOW}>> [3/3] Executando o programa compilado: ${executable_file}${NC}"
        "$executable_file"

        echo -e "${GREEN}SUCESSO!${NC}"
        echo "------------------------------------------"
    fi
done
echo ""


# --- Testes Inválidos ---
# Desativa a saída por erro para os testes inválidos, pois esperamos que eles falhem.
set +e

echo -e "${RED}--- INICIANDO CASOS DE TESTE INVÁLIDOS ---${NC}"
echo "Estes programas devem gerar erros durante a análise pelo Cmantic."
echo "--------------------------------------------"

for test_file in "$INVALID_DIR"/*.cmt; do
    if [ -f "$test_file" ]; then
        echo ""
        echo -e "${YELLOW}>> Testando arquivo inválido: ${test_file} (espera-se um erro)...${NC}"
        $EXECUTABLE "$test_file"
        echo "--------------------------------------------"
    fi
done
echo ""


echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}      BATERIA DE TESTES FINALIZADA       ${NC}"
echo -e "${BLUE}=========================================${NC}"