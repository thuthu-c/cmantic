#!/bin/bash

# ============================================================================
# Script para executar a bateria de testes do Compilador Cmantic
# ============================================================================

# --- Configuração ---
# Nome do seu executável gerado pelo make/cmake
EXECUTABLE="./cmantic"
# Diretórios dos casos de teste
VALID_DIR="tests/valid"
INVALID_DIR="tests/invalid"

# --- Cores para facilitar a leitura (opcional) ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # Sem Cor

# --- Verificação de Existência do Executável ---
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Erro: O executável '$EXECUTABLE' não foi encontrado!${NC}"
    echo "Por favor, compile o projeto antes de executar os testes."
    exit 1
fi

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}  INICIANDO BATERIA DE TESTES DO CMANTIC ${NC}"
echo -e "${BLUE}=========================================${NC}"
echo ""

# --- Testes Válidos ---
echo -e "${GREEN}--- INICIANDO CASOS DE TESTE VÁLIDOS ---${NC}"
echo "Estes programas devem ser analisados sem erros."
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Declaração de variáveis (com/sem tipo, atribuição e reatribuição)${NC}"
$EXECUTABLE "$VALID_DIR/program_var_decl.cmt"
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Declaração de procedimentos (com variáveis de escopo)${NC}"
$EXECUTABLE "$VALID_DIR/program_procedure_decl.cmt"
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Declaração e atribuição de registros (structs)${NC}"
$EXECUTABLE "$VALID_DIR/program_register_decl.cmt"
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Expressões (lógicas, relacionais, aritméticas)${NC}"
$EXECUTABLE "$VALID_DIR/program_expressions.cmt"
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Blocos de código (if, while, unless, case)${NC}"
$EXECUTABLE "$VALID_DIR/program_code_blocks.cmt"
echo "------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Programa de exemplo: Swap${NC}"
$EXECUTABLE "$VALID_DIR/program_swap.cmt"
echo "------------------------------------------"
echo ""



# --- Testes Inválidos ---
echo -e "${RED}--- INICIANDO CASOS DE TESTE INVÁLIDOS ---${NC}"
echo "Estes programas devem gerar erros durante a análise."
echo "--------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Declaração de variável duplicada (inválido)${NC}"
$EXECUTABLE "$INVALID_DIR/program_duplicate_var.cmt"
echo "--------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Declaração de variável com mudança de tipo (inválido)${NC}"
$EXECUTABLE "$INVALID_DIR/program_type_change.cmt"
echo "--------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Acesso a variável fora de escopo (inválido)${NC}"
$EXECUTABLE "$INVALID_DIR/program_out_of_scope.cmt"
echo "--------------------------------------------"
echo ""

echo -e "${YELLOW}>> Testando: Acesso a variável inexistente (inválido)${NC}"
$EXECUTABLE "$INVALID_DIR/program_inexistent_var.cmt"
echo "--------------------------------------------"
echo ""


echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}      BATERIA DE TESTES FINALIZADA       ${NC}"
echo -e "${BLUE}=========================================${NC}"