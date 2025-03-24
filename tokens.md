/** Expressões terminais */
PROGRAM -> "program"
BEGIN -> "begin"
END -> "end"
VAR -> "var"
PROCEDURE -> "procedure"
STRUCT -> "struct"
IN -> "in"
NOT -> "not"
NEW -> "new"
REF -> "ref"
DEREF -> "deref"

SEMICOLON -> ";"
COLON -> ":"
COMMA -> ","
ASSIGN -> ":="
DOT -> "."

LEFT_BRACKET -> "["
RIGHT_BRACKET -> "]"
LEFT_PARENTHESIS -> "("
RIGHT_PARENTHESIS -> ")"
LEFT_BRACES -> "{"
RIGHT_BRACES -> "}"

OR_LOGIC -> "||"
AND_LOGIC -> "&&"
LESS_THAN -> "<"
LESS_THAN_EQUAL -> "<="
GREATER_THAN -> ">"
GREATER_THAN_EQUAL -> ">="
EQUAL -> "="
DIFFERENT -> "<>"

PLUS -> "+"
MINUS -> "-"
MULTUPLY -> "*"
DIVIDE -> "/"
POWER -> "^"

FLOAT -> "float"
INT -> "int"
STRING -> "string"
BOOL -> "bool"
TRUE -> "true"
FALSE -> "false"
NULL -> "null"

IF -> "if"
THEN -> "then"
ELSE -> "else"
FI -> "fi"
WHILE -> "while"
DO -> "do"
OD -> "od"
RETURN -> "return"
UNLESS -> "unless"
CASE -> "case"
OF -> "of"
ESAC -> "esac"
OTHERWISE -> "otherwise"

/** Expressões regulares */
NAME -> [a-zA-Z][a-zA-Z0-9_]*
COMMENT -> (//.*\n) \** Isto significa que começa com //, depois pode vir qlqr caractere zero ou mais vezes e depois o fim de linha  */
           |  (\(* (.|\n)* *\)) |** Isto significa que começa com (*, depois pode vir qlqr caracetere ou \n zero ou mais vezes e depois *) */
INT_LITERAL -> [0-9]+
FLOAT_LITERAL -> [0-9]+\.[0-9]+([Ee][-+][0-9]{2})? /** Pode ser 1221.1212 ou 1212.e+22 ou 1212.e-22 */
STRING_LITERAL -> "^[\n\r]+"
BOOL_LITERAL -> TRUE | FALSE