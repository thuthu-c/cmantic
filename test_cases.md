# Listagem de casos de teste

## Válidos

- Declaração de variáveis:
    - Declaração :white_check_mark:
    - Declaração com tipos :white_check_mark:
    - Declaração com atribuição :white_check_mark:
    - Atribuição :x: (Dependente dos procedimentos)
    - Reatribuição :x: (Dependente dos procedimentos)

- Declaração de procedimentos:
    - Declaração :x:
    - Declaração de variáveis no escopo :x:

- Declaração de registros:
    - Declaração :white_check_mark:
    - Atribuição :x:

- Expressões:
    - Expressões lógicas :white_check_mark:
    - Expressões relacionais :white_check_mark:
    - Expressões aritmétricas :white_check_mark:
    - Demais expressões :white_check_mark:

- Blocos: (Todos dependentes dos procedimentos)
    - If :x:
    - While :x:
    - Unless :x:
    - Case :x:

## Inválidos

- Declaração de variáveis:
    - Declaração duplicada :white_check_mark:
    - Mudança de tipo :x: (Dependente dos procedimentos)

- Declaração de procedimentos:
    - Acesso de variáveis fora do escopo :x:

- Expressões:
    - Acesso a variável inexistente :white_check_mark::x: