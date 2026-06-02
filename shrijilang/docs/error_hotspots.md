# ERROR HOTSPOTS

E_PARSE_INVALID_TOKEN

Locations:
parser.c:208
parser.c:256
parser.c:320
...
parser.c:1608

Current Meaning:
Too Many Meanings

Future Split:
E_EXTRA_BRACE
E_EXTRA_PAREN
E_EMPTY_EXPRESSION
E_UNEXPECTED_TOKEN
E_MISSING_LEFT_OPERAND

Current Meaning:
Too Many Meanings

Observed Subtypes:

1. Invalid Character
2. Invalid Assignment Start
3. Unknown Statement
4. Missing Right Operand
5. Empty Expression
6. Extra Parenthesis
7. Extra Brace
8. Unexpected Token

Priority:
HIGHEST

--------------------------------------------------

E_PARSE_02

Locations:
parser.c:624
interpreter.c:274
...
interpreter.c:1848

Current Meaning:
Too Many Meanings

Future Split:
E_FUNC_MISSING_ARG
E_FUNC_EXTRA_ARG
E_FUNC_WRONG_TYPE
E_FUNC_ARG_COUNT_MISMATCH
E_EXPECTED_PAREN

E_PARSE_INVALID_TOKEN

Root Location:
src/parser.c:1608

Current Behavior:
Fallback for parse_primary()

Observed Cases:

1. Extra )
2. Extra }
3. Empty Expression
4. Missing Left Operand
5. Unexpected Token

Status:
Needs Split

Priority:
Highest
