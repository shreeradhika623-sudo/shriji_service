/*=============================================================
  SHRIJI GYAAN ENGINE — FINAL COMPLETE RULE SET
=============================================================*/

#include <stddef.h>
#include "../../include/error.h"

/*──────────────────────────────────────────────
  STRUCT
──────────────────────────────────────────────*/
typedef struct {
    int code;

    const char *module;
    const char *file;
    const char *function;

    const char *rule;
    const char *explain;
    const char *hint;

} GyaanRule;

/*=============================================================
   RULE DATABASE START
=============================================================*/
static GyaanRule GYAAN_RULES[] = {

/*──────────── PARSER CORE ────────────*/

{E_PARSE_OPERATOR_START,"parser","parser.c","parse_expression",
"expression cannot start with operator",
"operator se expression start nahi hota",
"example: 10 + 2"},

{E_PARSE_OPERATOR_END,"parser","parser.c","parse_expression",
"operator must have value after it",
"operator ke baad value missing hai",
"example: 10 + 2"},

{E_PARSE_DOUBLE_OPERATOR,"parser","parser.c","parse_expression",
"two operators cannot come together",
"do operator ek saath nahi aate",
"example: 10 + 2"},

{E_PARSE_OPERATOR_CHAIN,"parser","parser.c","parse_expression",
"operator chain is invalid",
"operator chain galat hai",
"example: 10 + 2"},

{E_PARSE_INVALID_TOKEN,"parser","parser.c","parse_statement",
"statement must start with valid token",
"line ki shuruaat galat token se hui hai",
"use: bolo / mavi / agar"},

{E_PARSE_BRACKET_MISSING,"parser","parser.c","parse_primary",
"closing bracket missing",
"bracket close nahi hua",
"example: (10 + 2)"},

/*──────────── PARSER ADVANCED ────────────*/

{E_PARSE_EXTRA_OPERATOR,"parser","parser.c","parse_expression",
"extra operator found",
"extra operator detect hua",
"example: 10 + 2"},

{E_PARSE_MISSING_OPERATOR,"parser","parser.c","parse_expression",
"operator missing between values",
"values ke beech operator missing hai",
"example: 10 + 2"},

{E_PARSE_UNMATCHED_PAREN,"parser","parser.c","parse_primary",
"parentheses mismatch",
"bracket match nahi hua",
"example: (10 + 2)"},

{E_PARSE_BRACKET_EXTRA,"parser","parser.c","parse_primary",
"extra closing bracket",
"extra bracket mila",
"bracket remove karein"},

{E_PARSE_MISSING_OPERAND,"parser","parser.c","parse_expression",
"operand missing",
"value missing hai operator ke liye",
"example: 10 + 2"},

/*──────────── ASSIGNMENT ────────────*/

{E_ASSIGN_01,"runtime","interpreter.c","AST_IDENTIFIER",
"variable must be declared before use",
"Aap jis variable ko use kar rahe hain, woh abhi tak banaya nahi gaya.",
"Example: mavi x = 10"},

{E_RUNTIME_UNDEFINED_VAR,"runtime","interpreter.c","AST_IDENTIFIER",
"variable must be declared before use",
"Aap jis variable ko use kar rahe hain, woh abhi tak banaya nahi gaya.",
"Example: mavi x = 10"},

{E_ASSIGN_02,"parser","parser.c","parse_assignment",
"assignment must have value",
"assignment me value missing hai",
"example: mavi x = 10"},

/*──────────── FUNCTION ────────────*/

{E_PARSE_01,"parser","parser.c","general",
"syntax error",
"syntax samajh nahi aaya",
"statement check karein"},

{E_PARSE_02,"system","multiple","general",
"invalid usage",
"Shri ne function ke liye alag number ke arguments expect kiye the.",
"Sahi number ke arguments pass kijiye."},

{E_RUNTIME_FUNCTION_NOT_FOUND,
 "runtime",
 "interpreter.c",
 "AST_CALL",
 "function not found",
 "Shri ko memory me is naam ka function nahi mila.",
 "Pehle function banaiye"},

{E_FUNCTION_NAME_INVALID,
 "parser",
 "parser.c",
 "parse_function",
 "function name missing",
 "function ka naam missing hai",
 "example: kaam add(a, b) { ... }"},

{E_FUNCTION_PARAM_INVALID,
 "parser",
 "parser.c",
 "parse_function",
 "function parameter syntax invalid",
 "function parameter ya argument format galat hai",
 "example: add(5, 6)"},


/*──────────── DICT / MAP ────────────*/

{E_DICT_KEY_INVALID,
 "parser",
 "parser.c",
 "parse_dict_literal",
 "dict key must be string",
 "dictionary key string honi chahiye",
 "example: {\"a\": 1, \"b\": 2}"},

/*──────────── CONTROL FLOW ────────────*/

{E_IF_01,"parser","parser.c","parse_if",
"invalid if condition",
"if condition galat hai",
"example: agar x > 0 { ... }"},

{E_RUNTIME_LOOP_LIMIT,"runtime","interpreter.c","AST_WHILE",
"loop exceeded safe limit",
"loop limit cross ho gaya",
"condition fix karein"},

/*──────────── DATA STRUCTURES ────────────*/

{E_RUNTIME_INDEX_ERROR,"runtime","interpreter.c","AST_INDEX",
"index out of bounds",
"index range ke bahar hai",
"example: a[0]"},

/*──────────── RUNTIME ────────────*/

{E_RUNTIME_DIV_ZERO,"runtime","interpreter.c","safe_div",
"division by zero not allowed",
"0 se divide nahi kar sakte",
"example: 10 / 2"},

{E_RUNTIME_TYPE_MISMATCH,"runtime","interpreter.c","AST_BINARY",
"type mismatch in expression",
"Shri ko expression me alag type ki values mili.",
"Dono taraf compatible values use kijiye."},

{E_RUNTIME_01,"runtime","interpreter.c","general",
"runtime error occurred",
"runtime me issue aaya",
"logic check karein"}

};

/*=============================================================
  🧠 RULE DATABASE END
=============================================================*/

/*──────────────────────────────────────────────
  COUNT
──────────────────────────────────────────────*/
static int GYAAN_COUNT =
sizeof(GYAAN_RULES) / sizeof(GYAAN_RULES[0]);

/*──────────────────────────────────────────────
  LOOKUP
──────────────────────────────────────────────*/
const GyaanRule* gyaan_lookup(int code)
{
    for (int i = 0; i < GYAAN_COUNT; i++) {
        if (GYAAN_RULES[i].code == code) {
            return &GYAAN_RULES[i];
        }
    }
    return NULL;
}
