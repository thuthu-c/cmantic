## Lista de Atributos por produção

| Simbolo    | Atributo | Descrição
| -------- | ------- | ------- |
| PROGRAM  | valid    | _Sintetizado_: Programa correto
| DECL_LIST |   scope   | _Sintetizado_: Conjunto de pares (name, tipo) de variáveis declaradas
| DECL |   value   | _Sintetizado_: Pare (name, tipo) da variável declarada 
| VAR_DECL  | value  | _Sintetizado_: Par (name, tipo) referente à variável declarada
| PROC_DECL |   scope   | _Sintetizado_: Conjunto de pares (name, tipo) de variáveis declaradas 
| REC_DECL |   scope   | _Sintetizado_: Conjunto de pares (name, tipo) de variáveis declaradas 
| PARAMFIELD_DECL |  value  | _Sintetizado_: Par (name, tipo) referente à variável declarada
| STMT_LIST |  scope  | _Sintetizado_: Conjunto de pares (name, tipo) de variáveis declaradas 
| STMT |  scope  | _Herdado_: Conjunto de pares (name, tipo) de variáveis declaradas
| ASSIGN_STMT |  value  | _Sintetizado_: Par (name, tipo) referente à variável declarada
| IF_STMT |  scope  | _Herdado_: Conjunto de pares (name, tipo) de variáveis declaradas 
| WHILE_STMT |  scope  | _Herdado_: Conjunto de pares (name, tipo) de variáveis declaradas 
| RETURN_STMT |  type | _Sintetizado_: Tipo da expressão retornada
| CALL_STMT |  valid  | _Sintetizado_: Tipos das expressões correspondem aos tipos declarados no procedimento
| CALL_STMT |  type | _Sintetizado_: Tipo do procedimento
| EXP |  valid  |  _Sintetizado_: Tipos das sub-expressões são equivalentes
| EXP |  type  |  _Sintetizado_: Tipo resultante da expressão
| VAR |  value  | _Sintetizado_: Par (name, tipo) referente à variável declarada
| REF_VAR | type  | _Sintetizado_: Tipo resultante
| DEREF_VAR | value  | _Sintetizado_: Par (name, tipo) referente à variável declarada
| NEW_NAME | type | _Sintetizado_: Tipo respectivo ao identificador
| TYPE |  type  | _Sintetizado_: Tipo descrito
| ARITH_OP |  valid  | _Sintetizado_: Tipos das expressões utilizadas são equivalentes
| LOG_OP |  valid  | _Sintetizado_: Tipos das expressões utilizadas são equivalentes
| REL_OP |  valid  | _Sintetizado_: Tipos das expressões utilizadas são equivalentes