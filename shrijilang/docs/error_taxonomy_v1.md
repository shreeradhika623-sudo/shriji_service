# SHRIJI ERROR TAXONOMY V1

## VARIABLE ERRORS

E_VAR_UNDEFINED

Example:
bolo x

Status:
Improve

--------------------------------------------------

## FUNCTION ERRORS

E_FUNC_NOT_FOUND

Example:
bolo maxx(10)

Status:
Rewrite

--------------------------------------------------

E_FUNC_MISSING_ARG

Example:
abs()

Status:
Rewrite

--------------------------------------------------

E_FUNC_EXTRA_ARG

Example:
floor(10,20)

Status:
Rewrite

--------------------------------------------------

E_FUNC_WRONG_TYPE

Example:
abs("radhe")

Status:
Rewrite

--------------------------------------------------

## TYPE ERRORS

E_TYPE_MISMATCH

Example:
"radhe" + 10

Status:
Improve

--------------------------------------------------

## RUNTIME ERRORS

E_DIVIDE_BY_ZERO

Example:
10 / 0

Status:
Freeze

--------------------------------------------------

## STRUCTURE ERRORS

E_MISSING_BRACE

Status:
Freeze

--------------------------------------------------

E_EXTRA_BRACE

Status:
Rewrite

--------------------------------------------------

E_MISSING_PAREN

Status:
Improve

--------------------------------------------------

E_EXTRA_PAREN

Status:
Rewrite

--------------------------------------------------

## OPERATOR ERRORS

E_DOUBLE_OPERATOR

Status:
Freeze

--------------------------------------------------

E_OPERATOR_AT_END

Status:
Freeze

--------------------------------------------------

E_MISSING_LEFT_OPERAND

Status:
Rewrite

--------------------------------------------------

## EXPRESSION ERRORS

E_EMPTY_EXPRESSION

Status:
Rewrite

--------------------------------------------------

## ARGUMENT LIST ERRORS

E_MISSING_COMMA

Status:
Freeze

--------------------------------------------------

## GENERIC ERRORS

E_UNKNOWN

Status:
Last Resort Only
