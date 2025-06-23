# Listagem de casos de teste

## Válidos

- Declaração de variáveis:
    - Atribuição :white_check_mark:
    - Atribuição com tipos :white_check_mark:
    - Reatribuição :x:


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
    - Mudança de tipo :x: (Dependentes dos procedimentos)

- Declaração de procedimentos:
    - Acesso de variáveis fora do escopo :x:

- Expressões:
    - Acesso a variável inexistente :white_check_mark::x: