#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <math.h>

#define MAX_IMPORT_DEPTH 256

static char import_stack[MAX_IMPORT_DEPTH][256];
static int import_depth = 0;

#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/ast.h"
#include "../include/env.h"
#include "../include/error.h"
#include "../include/state.h"
#include "../include/event.h"
#include "../include/command.h"
#include "../include/value.h"
#include "../include/ai_router.h"

#include "../include/smriti_personal.h"
#include "../include/smriti_session.h"

#include "../include/runtime.h"

#include "../include/user_config.h"
#include "../include/log_mode.h"

#ifdef SHRIJI_ENABLE_MASTER_TOKENS
#include "lang/token_master.h"
#endif

/*──────────────────────────────────────────────
  helper: unescape string like "a\\nb" -> actual newline
  supports: \n \t \r \\ \"
──────────────────────────────────────────────*/
static char *unescape_string(const char *s)
{
    if (!s) return NULL;

    size_t n = strlen(s);
    char *out = (char *)malloc(n + 1);
    if (!out) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        if (s[i] == '\\' && i + 1 < n) {
            char c = s[i + 1];
            if (c == 'n')      { out[j++] = '\n'; i++; continue; }
            else if (c == 't') { out[j++] = '\t'; i++; continue; }
            else if (c == 'r') { out[j++] = '\r'; i++; continue; }
            else if (c == '\\'){ out[j++] = '\\'; i++; continue; }
            else if (c == '"') { out[j++] = '"';  i++; continue; }
        }
        out[j++] = s[i];
    }

    out[j] = '\0';
    return out;
}
/*──────────────────────────────────────────────────────────────
 | SHRIJI TRUTH DIARY — SINGLE SOURCE OF FACT
 *──────────────────────────────────────────────────────────────*/
ShrijiTruthDiary SHRIJI_DIARY = {0};

/*──────────────────────────────────────────────────────────────
 | STATE DECISION HOOK
 *──────────────────────────────────────────────────────────────*/
static int state_allows_execution(ShrijiRuntime *rt)
{
    if (!rt) return 0;

    if (rt->state.safety == STATE_CRITICAL) {
        return 0;
    }
    return 1;
}

/*──────────────────────────────────────────────────────────────
 | SAFE DIVISION
 *──────────────────────────────────────────────────────────────*/
static double safe_div(double a, double b, ShrijiRuntime *rt)
{
    if (b == 0) {
        event_fire(EVENT_ERROR, "division by zero");

        shriji_error(
            E_RUNTIME_DIV_ZERO,
            "division",
            "0 se divide nahi kar sakte",
            "denominator 0 nahi hona chahiye"
        );

        if (rt)
         rt->error_flag = 1;
        return 0;
    }

    return a / b;
}

static const char* type_name(ValueType t)
{

    switch (t) {

        case VAL_STRING:
            return "String (Text)";

        case VAL_INT:
            return "Integer (Whole Number)";

        case VAL_NUMBER:
            return "Float (Decimal Number)";

        case VAL_BOOL:
            return "Boolean (Sahi/Galat Value)";

        case VAL_LIST:
            return "List";

        case VAL_FUNCTION:
            return "Function";

        case VAL_DICT:
            return "Dictionary";

        case VAL_NULL:
            return "Null";

        default:
            return "Unknown";
    }
}

/*──────────────────────────────────────────────────────────────
 | SAFE MODULO
 *──────────────────────────────────────────────────────────────*/
static double safe_mod(double a, double b)
{
    if (b == 0) {

        event_fire(EVENT_ERROR, "modulo by zero");

        shriji_error(
            E_RUNTIME_DIV_ZERO,
            "modulo",
            "0 se modulo nahi kar sakte",
            "denominator 0 nahi hona chahiye"
        );

        return 0;
    }

    return fmod(a, b);
}

/* YAHAA SE NAYA FUNCTION START */

static int value_equals(Value a, Value b)
{
  if (
    (a.type == VAL_INT || a.type == VAL_NUMBER) &&
    (b.type == VAL_INT || b.type == VAL_NUMBER)
   ) {
       /* numeric compare */
   }
   else if (a.type != b.type) {
     return 0;
    }

    switch (a.type) {

    case VAL_NUMBER:

    if (b.type == VAL_NUMBER)
        return a.number == b.number;

    if (b.type == VAL_INT)
        return a.number == b.integer;

    return 0;

 case VAL_INT:

    if (b.type == VAL_INT)
        return a.integer == b.integer;

    if (b.type == VAL_NUMBER)
        return a.integer == b.number;

    return 0;

    case VAL_BOOL:
    return a.boolean == b.boolean;

    case VAL_STRING:

            if (!a.string || !b.string)
                return 0;

            return strcmp(a.string, b.string) == 0;

        case VAL_NULL:
            return 1;

        default:
            return 0;
    }
}
/*──────────────────────────────────────────────────────────────
 | Value → number helper
 *──────────────────────────────────────────────────────────────*/
static const char *strip_quotes(const char *s)
{
    if (!s) return "";

    while (*s == ' ' || *s == '\t')
        s++;

    size_t len = strlen(s);

    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
        static char buf[1024];
        size_t n = len - 2;
        if (n >= sizeof(buf)) n = sizeof(buf) - 1;

        memcpy(buf, s + 1, n);
        buf[n] = '\0';
        return buf;
    }

    return s;
}

static int is_import_active(const char *path)
{
    for (int i = 0; i < import_depth; i++)
    {
        if (strcmp(import_stack[i], path) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/*──────────────────────────────────────────────────────────────
 | MAIN EVALUATOR
 *──────────────────────────────────────────────────────────────*/
Value shriji_execute_line(const char *line, Env *env, ShrijiRuntime *rt)
{
    (void)env;

    if (!line || !*line) return value_null();

    while (*line == ' ' || *line == '\t') line++;
    if (*line == '\0') return value_null();


ASTNode *node = parse_program(line);

/* DO NOT RESET error_reported */
if (!node || error_reported)
{
    if (rt) {
        rt->error_flag = 1;
    }
    return value_null();
}

/* EXECUTE AST */
Value result = eval(node, env, rt);
return result;

}

Value eval(ASTNode *node, Env *env, ShrijiRuntime *rt)
{
     /* HARD STOP ONLY FOR FATAL PARSER ERRORS */
     if (error_reported)
           return value_null();

  /* runtime return stop */
     if (rt &&
            rt->return_flag)
 {
            return value_null();
 }

    static int state_initialized = 0;

    if (!state_initialized) {
        state_init(&rt->state);
        state_initialized = 1;
    }

    if (!state_allows_execution(rt) || !node)
        return value_null();

    /* 🧠 GLOBAL STEP COUNTER */
    if (node->type != AST_WHILE &&
        node->type != AST_BREAK &&
        node->type != AST_CONTINUE &&
        node->type != AST_BLOCK &&
        node->type != AST_PROGRAM) {
        rt->state.steps_used++;
    }


    if (rt->state.steps_used > rt->state.max_steps) {
        shriji_error(
            E_PARSE_02,
            "runtime",
            "execution limit exceeded",
            "possible infinite loop detected"
        );
        rt->state.safety = STATE_CRITICAL;
        return value_null();
    }



switch (node->type) {

case AST_BREAK:
    if (rt->loop_depth <= 0) {
        shriji_error(
            E_RUNTIME_01,
            "break",
            "loop ke bahar rukja allowed nahi hai",
            "rukja sirf while loop ke andar use karein"
        );
        return value_null();
    }

    rt->break_flag = 1;
    return value_null();

case AST_CONTINUE:

     if (rt->loop_depth <= 0) {
        shriji_error(
        E_RUNTIME_01,
        "continue",
        "loop ke bahar continue allowed nahi hai",
        "continue sirf while loop ke andar use karein"
    );
    return value_null();
}
    rt->continue_flag = 1;
    return value_null();


case AST_RETURN: {

    Value v = value_null();

    if (node->return_expr)
        v = eval(node->return_expr, env, rt);

    if (rt) {

        rt->return_flag = 1;

        value_free(&rt->return_value);

        rt->return_value = value_copy(v);
    }

    value_free(&v);

    return value_null();
}

case AST_UNARY:
{
    ASTNode *cur = node;
    int sign = 1;

    while (cur && cur->type == AST_UNARY) {

        if (cur->op[0] == '-')
            sign *= -1;

        cur = cur->left;
    }

    Value v = eval(cur, env, rt);

    if (v.type == VAL_INT) {

        v.integer = v.integer * sign;

        return v;
    }

    if (v.type == VAL_NUMBER) {

        v.number = v.number * sign;

        return v;
    }

    return value_null();
}

/*────────────────────────────────────────
 | INC / DEC (++ / --)
 *────────────────────────────────────────*/

case AST_INC: {

    /* only identifiers allowed */
    if (!node->left || node->left->type != AST_IDENTIFIER) {
        return value_null();
    }

    const char *name = node->left->name;

    Value old = env_get(env, name);

    if (old.type != VAL_NUMBER) {
        return value_null();
    }

    Value newv = old;
    newv.number = old.number + 1;

    env_set(env, name, newv);

    if (node->is_prefix)
        return newv;
    else
        return old;
}

case AST_DEC: {

    /* only identifiers allowed */
    if (!node->left || node->left->type != AST_IDENTIFIER) {
        return value_null();
    }

    const char *name = node->left->name;

    Value old = env_get(env, name);

    if (old.type != VAL_NUMBER) {
        return value_null();
    }

    Value newv = old;
    newv.number = old.number - 1;

    env_set(env, name, newv);

    if (node->is_prefix)
        return newv;
    else
        return old;
}

    /*──────────────────────────────────────────────
      FUNCTIONS
    ──────────────────────────────────────────────*/

    case AST_FUNCTION: {
        /* store function AST node into env */
        env_set(env, node->function_name, value_function(node));
        return value_null();
    }

case AST_RACHNA: {
    env_set(env, node->rachna_name, value_function(node));
    return value_null();
}

case AST_CALL: {

/*────────────────────────────
  STACK GUARD (ENTRY)
────────────────────────────*/
if (rt->call_depth >= 500) {

    shriji_error(
        E_RUNTIME_01,
        "recursion",
        "function khud ko bahut baar call kar raha hai",
        "safe limit: 500"
    );

    rt->error_flag = 1;

    return value_null();
}

rt->call_depth++;


   /*──────────────────────────────────────────────
      BUILT-IN FUNCTIONS (FILE I/O)
      padho("file")                -> returns string
      likho("file", "text")        -> overwrite write -> returns 1/0
      jodo("file", "text")         -> append write   -> returns 1/0

       polish:
      - supports escape sequences: \n \t \r \\ \"
    ──────────────────────────────────────────────*/

    /* READ */
    if (strcmp(node->function_name, "padho") == 0) {

        if (node->arg_count != 1) {
            shriji_error(
                E_PARSE_02,
                "padho",
                "argument count mismatch",
                "use: padho(\"file.txt\")"
            );
            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {
            value_free(&pathv);
            shriji_error(
                E_PARSE_02,
                "padho",
                "file path must be string",
                "use: padho(\"file.txt\")"
            );
            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

FILE *fp = fopen(path, "rb");
if (!fp) {
    value_free(&pathv);

    shriji_error(
        E_PARSE_02,
        "padho",
        "file not found",
        "check path or create file first"
    );

    return value_string("");
}
        fseek(fp, 0, SEEK_END);
        long sz = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (sz < 0) sz = 0;
        if (sz > 1024 * 1024) sz = 1024 * 1024; /* 1MB limit v1 */

        char *buf = (char *)malloc((size_t)sz + 1);
        if (!buf) {
            fclose(fp);
            value_free(&pathv);
           import_depth--;
            return value_null();
        }

        size_t nread = fread(buf, 1, (size_t)sz, fp);
        buf[nread] = '\0';

        fclose(fp);
        value_free(&pathv);

        Value out = value_string(buf);
        free(buf);
        return out;
    }

    /* WRITE (overwrite) */
    if (strcmp(node->function_name, "likho") == 0) {

        if (node->arg_count != 2) {
            shriji_error(
                E_PARSE_02,
                "likho",
                "argument count mismatch",
                "use: likho(\"file.txt\", \"data\")"
            );
            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);
        Value datav = eval(node->args[1], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {
            value_free(&pathv);
            value_free(&datav);
            shriji_error(
                E_PARSE_02,
                "likho",
                "file path must be string",
                "use: likho(\"file.txt\", \"data\")"
            );
            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

        const char *data = "";
        char tmp[128];
        tmp[0] = '\0';

        char *tmp_data = NULL;

        if (datav.type == VAL_STRING && datav.string) {
            tmp_data = unescape_string(strip_quotes(datav.string));
            data = tmp_data ? tmp_data : "";
        } else if (datav.type == VAL_NUMBER) {
            snprintf(tmp, sizeof(tmp), "%g", datav.number);
            data = tmp;
        }

        FILE *fp = fopen(path, "wb");
        if (!fp) {
            if (tmp_data) free(tmp_data);
            value_free(&pathv);
            value_free(&datav);
            return value_number(0);
        }

        fwrite(data, 1, strlen(data), fp);
        fclose(fp);

        if (tmp_data) free(tmp_data);

        value_free(&pathv);
        value_free(&datav);

        return value_number(1);
    }

    /* APPEND */
    if (strcmp(node->function_name, "jodo") == 0) {

        if (node->arg_count != 2) {
            shriji_error(
                E_PARSE_02,
                "jodo",
                "argument count mismatch",
                "use: jodo(\"file.txt\", \"data\")"
            );
            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);
        Value datav = eval(node->args[1], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {
            value_free(&pathv);
            value_free(&datav);
            shriji_error(
                E_PARSE_02,
                "jodo",
                "file path must be string",
                "use: jodo(\"file.txt\", \"data\")"
            );
            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

        const char *data = "";
        char tmp[128];
        tmp[0] = '\0';

        char *tmp_data = NULL;

        if (datav.type == VAL_STRING && datav.string) {
            tmp_data = unescape_string(strip_quotes(datav.string));
            data = tmp_data ? tmp_data : "";
        } else if (datav.type == VAL_NUMBER) {
            snprintf(tmp, sizeof(tmp), "%g", datav.number);
            data = tmp;
        }

        FILE *fp = fopen(path, "ab");
        if (!fp) {
            if (tmp_data) free(tmp_data);
            value_free(&pathv);
            value_free(&datav);
            return value_number(0);
        }

        fwrite(data, 1, strlen(data), fp);
        fclose(fp);

        if (tmp_data) free(tmp_data);

        value_free(&pathv);
        value_free(&datav);

        return value_number(1);
    }

/*──────────────────────────────────────────────
  MATH BUILTINS
──────────────────────────────────────────────*/

if (
    strcmp(node->function_name, "floor") == 0 ||
    strcmp(node->function_name, "purna") == 0
)
{
    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "floor",
            "1 argument required",
            "use: floor(x)"
        );

        return value_null();
    }

    Value v = eval(node->args[0], env, rt);

    double n = 0;

    if (v.type == VAL_INT)
        n = v.integer;

    else if (v.type == VAL_NUMBER)
        n = v.number;

    else {

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "floor",
            "number required",
            "use numeric value"
        );

        return value_null();
    }

    value_free(&v);

    return value_int((int)floor(n));
}

if (
    strcmp(node->function_name, "ceil") == 0 ||
    strcmp(node->function_name, "upar") == 0
)
{
    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "ceil",
            "1 argument required",
            "use: ceil(x)"
        );

        return value_null();
    }

    Value v = eval(node->args[0], env, rt);

    double n = 0;

    if (v.type == VAL_INT)
        n = v.integer;

    else if (v.type == VAL_NUMBER)
        n = v.number;

    else {

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "ceil",
            "number required",
            "use numeric value"
        );

        return value_null();
    }

    value_free(&v);

    return value_int((int)ceil(n));
}


if (
    strcmp(node->function_name, "round") == 0 ||
    strcmp(node->function_name, "gol") == 0
)
{
    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "round",
            "1 argument required",
            "use: round(x)"
        );

        return value_null();
    }

    Value v = eval(node->args[0], env, rt);

    double n = 0;

    if (v.type == VAL_INT)
        n = v.integer;

    else if (v.type == VAL_NUMBER)
        n = v.number;

    else {

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "round",
            "number required",
            "use numeric value"
        );

        return value_null();
    }

    value_free(&v);

    return value_int((int)round(n));
}

 
 if (
    strcmp(node->function_name, "abs") == 0 ||
    strcmp(node->function_name, "nirpeksh") == 0
)
{
    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "abs",
            "1 argument required",
            "use: abs(x)"
        );

        return value_null();
    }

    Value v = eval(node->args[0], env, rt);

    double n = 0;

    if (v.type == VAL_INT)
        n = v.integer;

    else if (v.type == VAL_NUMBER)
        n = v.number;

    else {

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "abs",
            "number required",
            "use numeric value"
        );

        return value_null();
    }

  if (v.type == VAL_INT) {

    value_free(&v);

    return value_int((int)fabs(n));
}

value_free(&v);

return value_number(fabs(n));

}


   /*──────────────────────────────────────────────
      NORMAL FUNCTION CALL
    ──────────────────────────────────────────────*/
Value fnv = env_get(env, node->function_name);

if (fnv.type != VAL_FUNCTION) {

char err[256];

snprintf(
    err,
    sizeof(err),
    "'%s' function nahi mila.",
    node->function_name
);

shriji_error(
    E_RUNTIME_FUNCTION_NOT_FOUND,
    "call",
    err,
    "Pehle function banaiye."
);

    return value_null();
}


ASTNode *fn = fnv.function;


  /* validate arg count */
int expected_args = 0;

if (fn->type == AST_RACHNA)
    expected_args = fn->rachna_param_count;

else if (fn->type == AST_FUNCTION)
    expected_args = fn->param_count;

if (expected_args != node->arg_count) {

    char err[256];
    char hint[256];

    snprintf(
        err,
        sizeof(err),
        "'%s' ko %d arguments chahiye the, lekin %d mile.",
        node->function_name,
        expected_args,
        node->arg_count
    );

    snprintf(
        hint,
        sizeof(hint),
        "Sahi number ke arguments pass kijiye."
    );

    shriji_error(
        E_PARSE_02,
        node->function_name,
        err,
        hint
    );

    rt->call_depth--;

    return value_null();
}

    /* save outer return state (nested calls safe) */
    int old_return_flag = rt->return_flag;
    Value old_return_value = rt->return_value;

    rt->return_flag = 0;
    rt->return_value = value_null();

    /* new call scope */
    env_push_scope(env);

    /* bind params */
for (int i = 0; i < expected_args; i++) {

    ASTNode *p;

    if (fn->type == AST_RACHNA)
        p = fn->rachna_params[i];
    else
        p = fn->params[i];

    Value av = eval(node->args[i], env, rt);

    env_set(env, p->name, av);
}

    /* run body */
ASTNode *body;

if (fn->type == AST_RACHNA)
    body = fn->rachna_body;
else
    body = fn->body;

Value result = eval(body, env, rt);

if (rt->return_flag) {

    value_free(&result);

    result = value_copy(rt->return_value);

    value_free(&rt->return_value);

    rt->return_value = value_null();
}
    /* end call scope */
    env_pop_scope(env);

    /* restore outer return state */
    rt->return_flag = old_return_flag;
    rt->return_value = old_return_value;

   rt->call_depth--;
    return result;
}

/*──────────────────────────────────────────────
      CORE VALUES
    ──────────────────────────────────────────────*/
case AST_NUMBER:

    if (node->is_int) {

     return value_int((long long)node->number_value);
    }

    return value_number(node->number_value);

case AST_STRING:
    return value_string(node->string_value);

case AST_BOOL:
    return value_bool(node->bool_value);

case AST_LIST: {
    int n = node->element_count;

    if (n <= 0 || !node->elements) {
        return value_list(NULL, 0);
    }

    Value *items = (Value *)malloc(sizeof(Value) * n);
    if (!items) return value_null();

    for (int i = 0; i < n; i++) {

        Value ev = eval(node->elements[i], env, rt);

        /* ownership transfer */
        items[i] = ev;
    }

    return value_list(items, n);
}

case AST_DICT: {
        int n = node->dict_count;

        if (n <= 0 || !node->dict_keys || !node->dict_values) {
            return value_dict(NULL, NULL, 0);
        }

        Value *keys = (Value *)malloc(sizeof(Value) * n);
        Value *vals = (Value *)malloc(sizeof(Value) * n);

        if (!keys || !vals) {
            if (keys) free(keys);
            if (vals) free(vals);
            return value_null();
        }

        for (int i = 0; i < n; i++) {
            Value kv = eval(node->dict_keys[i], env, rt);
            Value vv = eval(node->dict_values[i], env, rt);

            keys[i] = value_copy(kv);
            vals[i] = value_copy(vv);

            value_free(&kv);
            value_free(&vv);
        }

        return value_dict(keys, vals, n);
    }

case AST_INDEX: {

    Value tv = eval(node->index_target, env, rt);
    Value iv = eval(node->index_expr, env, rt);

    /*──────────────────────────────────────────────
      LIST INDEXING: a[0]
    ──────────────────────────────────────────────*/
    if (tv.type == VAL_LIST) {

        if (!tv.items) {
            value_free(&tv);
            value_free(&iv);
            return value_null();
        }

   if (iv.type != VAL_NUMBER &&
    iv.type != VAL_INT) {

   shriji_error(
    E_RUNTIME_INDEX_ERROR,
    "list",
    "List index out of range",
    "example: a[0]"
);

    value_free(&tv);
    value_free(&iv);
    return value_null();
}

long long idx;

if (iv.type == VAL_INT)
    idx = iv.integer;
else
    idx = (long long)iv.number;

value_free(&iv);

if (idx < 0 || idx >= tv.count) {

    shriji_error(
        E_RUNTIME_01,
        "list",
        "List index out of range",
        "example: a[0]"
    );

    value_free(&tv);
    return value_null();
}

Value out = value_copy(tv.items[(int)idx]);
value_free(&tv);
return out;

    }

    /*──────────────────────────────────────────────
      DICT INDEXING: d["a"]
    ──────────────────────────────────────────────*/
    if (tv.type == VAL_DICT) {

        if (iv.type != VAL_STRING || !iv.string) {
            shriji_error(
                E_RUNTIME_01,
                "dict",
                "dictionary ki key string honi chahiye",
                "example: d[\"a\"]"
            );
            value_free(&tv);
            value_free(&iv);
            return value_null();
        }

        for (int i = 0; i < tv.dict_count; i++) {

            Value k = tv.dict_keys[i];

            if (k.type == VAL_STRING &&
                strcmp(k.string, iv.string) == 0) {

                Value out = value_copy(tv.dict_values[i]);
                value_free(&tv);
                value_free(&iv);
                return out;
            }
        }

        shriji_error(
            E_RUNTIME_01,
            "dict",
            "dictionary me ye key maujood nahi hai",
            "example: d[\"a\"]"
        );
        value_free(&tv);
        value_free(&iv);
        return value_null();
    }

    /*──────────────────────────────────────────────
      UNSUPPORTED TARGET
    ──────────────────────────────────────────────*/
    value_free(&tv);
    value_free(&iv);
    return value_null();
}

case AST_INDEX_UPDATE: {

    if (node->index_target->type == AST_INDEX)
    {
        ASTNode *t = node->index_target;

        if (t->index_target)
        {
        }

        if (t->index_expr)
        {
        }
    }

    const char *var_name = NULL;

    /* direct: x[0] */
    if (node->index_target->type == AST_IDENTIFIER)
    {
        var_name = node->index_target->name;
    }

    /* nested: x["nums"][0] */
    else if (node->index_target->type == AST_INDEX)
    {
        ASTNode *inner = node->index_target;

        if (inner->index_target &&
            inner->index_target->type == AST_IDENTIFIER)
        {
            var_name = inner->index_target->name;
        }
    }

    if (!var_name)
    {
        return value_null();
    }

    /* fetch container directly from env */
    Value tv = env_get(env, var_name);


    Value iv = eval(node->index_expr, env, rt);
    Value vv = eval(node->index_value, env, rt);

/* nested: x["nums"][0] = value */
    if (node->index_target->type == AST_INDEX)
    {
        ASTNode *outer = node->index_target;

        Value keyv = eval(outer->index_expr, env, rt);

        if (tv.type == VAL_DICT &&
            keyv.type == VAL_STRING)
        {
            for (int i = 0; i < tv.dict_count; i++)
            {
                Value k = tv.dict_keys[i];

                if (k.type == VAL_STRING &&
                    strcmp(k.string, keyv.string) == 0)
                {
                    Value *target = &tv.dict_values[i];

                    if (target->type == VAL_LIST &&
                        iv.type == VAL_NUMBER)
                    {
                        int idx = (int)iv.number;

                        if (idx >= 0 &&
                            idx < target->count)
                        {
                            value_free(&target->items[idx]);

                            target->items[idx] =
                                value_copy(vv);

                            env_set(env, var_name, tv);

                            value_free(&keyv);
                            value_free(&tv);
                            value_free(&iv);
                            value_free(&vv);

                            return value_null();
                        }
                    }
                }
            }
        }

        value_free(&keyv);
    }

    /*──────────────────────────────────────────────
      LIST INDEX UPDATE: a[0] = value
    ──────────────────────────────────────────────*/
    if (tv.type == VAL_LIST) {

        if (iv.type != VAL_NUMBER) goto cleanup;

        long long idx = iv.number;
        if (idx < 0 || idx >= tv.count) goto cleanup;

        value_free(&tv.items[(int)idx]);
        tv.items[(int)idx] = value_copy(vv);

        /* WRITE BACK */
       env_set(env, var_name, tv);

           value_free(&tv);
           value_free(&iv);
           value_free(&vv);

           return value_null();
    }

    /*──────────────────────────────────────────────
      DICT INDEX UPDATE: d["a"] = value
    ──────────────────────────────────────────────*/
    if (tv.type == VAL_DICT) {

        if (iv.type != VAL_STRING || !iv.string) goto cleanup;

        /* update if exists */
        for (int i = 0; i < tv.dict_count; i++) {
            Value k = tv.dict_keys[i];
            if (k.type == VAL_STRING && strcmp(k.string, iv.string) == 0) {

                value_free(&tv.dict_values[i]);
                tv.dict_values[i] = value_copy(vv);

                env_set(env, var_name, tv);
                value_free(&iv);
                value_free(&iv);
                value_free(&vv);
                return value_null();
            }
        }

        /* append new key */
        tv.dict_keys = realloc(tv.dict_keys,
                               sizeof(Value) * (tv.dict_count + 1));
        tv.dict_values = realloc(tv.dict_values,
                                 sizeof(Value) * (tv.dict_count + 1));

        tv.dict_keys[tv.dict_count]   = value_copy(iv);
        tv.dict_values[tv.dict_count] = value_copy(vv);
        tv.dict_count++;

        env_set(env, var_name, tv);
        value_free(&iv);
        value_free(&iv);
        value_free(&vv);
        return value_null();
    }

cleanup:
    value_free(&tv);
    value_free(&iv);
    value_free(&vv);
    return value_null();
}

case AST_IDENTIFIER: {

    if (rt && rt->error_flag)
        return value_null();

    const char *name = node->name;

    if (env_exists(env, name)) {
        return env_get(env, name);
    }

    if (strcmp(name, "last") == 0) {
        return smriti_session_get_last();
    }

    const char *mem = smriti_personal_get(name);

    if (mem) {
        Value v;
        v.type = VAL_NUMBER;
        v.number = atof(mem);
        return v;
    }

  /*  FINAL ERROR */
shriji_error(
    E_RUNTIME_UNDEFINED_VAR,
    "runtime",
    "Variable abhi tak banaya nahi gaya.",
    "Variable use karne se pehle usse banaiye."
);

/*      fprintf(
    stderr,
    "HINT: pehle mavi %s = value likhiye\n",
    name
   );

*/
    if (rt)
        rt->error_flag = 1;

    return value_null();
}

case AST_ASSIGNMENT: {

    Value value = eval(node->value, env, rt);

    if (error_reported || rt->error_flag) {
        value_free(&value);
        return value_null();
    }

    /* CORRECT STORE */
    env_set(env, node->name, value);

    event_fire(EVENT_ASSIGNMENT, node->name);
    state_on_success(&rt->state);

    Value result = value_copy(value);

    value_free(&value);

    return result;
}

case AST_UPDATE: {

    if (node->name[0] != '\0') {

        if (!env_exists(env, node->name)) {
            shriji_error(
                E_ASSIGN_01,
                node->name,
                "variable not declared",
                "use mavi x = ... first"
            );
            return value_null();
        }

        Value value = eval(node->value, env, rt);

        /* FIXED: use env_update */
        env_update(env, node->name, value);

        event_fire(EVENT_ASSIGNMENT, node->name);
        state_on_success(&rt->state);

        return value;
    }

    shriji_error(
        E_ASSIGN_01,
        "update",
        "invalid update target",
        "use: x = expr"
    );

    return value_null();
}

case AST_BINARY: {

    /*  GLOBAL HARD STOP */
    if (error_reported || rt->error_flag)
        return value_null();

    /* LEFT */
    Value Lv = eval(node->left, env, rt);

    if (error_reported || rt->error_flag) {
        value_free(&Lv);
        return value_null();
    }

    /* RIGHT */
    Value Rv = eval(node->right, env, rt);

    if (error_reported || rt->error_flag) {
        value_free(&Lv);
        value_free(&Rv);
        return value_null();
    }

    char op = node->op[0];

/* ================= TYPE CHECK ================= */
if (
    Lv.type != Rv.type &&


   !(

    (Lv.type == VAL_INT && Rv.type == VAL_INT) ||

    (Lv.type == VAL_INT && Rv.type == VAL_NUMBER) ||

    (Lv.type == VAL_NUMBER && Rv.type == VAL_INT) ||

    (Lv.type == VAL_NUMBER && Rv.type == VAL_NUMBER)

)

) {

char err[256];

snprintf(
    err,
    sizeof(err),
    "%s aur %s ko '%c' ke saath use nahi kar sakte.",
    type_name(Lv.type),
    type_name(Rv.type),
    op
);

shriji_error(
    E_RUNTIME_TYPE_MISMATCH,
    "binary",
    err,
    "Dono taraf compatible values use kijiye."
);

value_free(&Lv);
value_free(&Rv);

return value_null();
}

    /* ================= LOGICAL ================= */
    if (op == '&') {
        int res = value_is_truthy(Lv) && value_is_truthy(Rv);
        value_free(&Lv);
        value_free(&Rv);
        return value_bool(res);
    }

    if (op == '|') {
        int res = value_is_truthy(Lv) || value_is_truthy(Rv);
        value_free(&Lv);
        value_free(&Rv);
        return value_bool(res);
    }

/* ================= EQUALITY ================= */
if (op == '=') {

    int result = value_equals(Lv, Rv);

    value_free(&Lv);
    value_free(&Rv);

    return value_bool(result);
}

if (op == '!') {

    int result = !value_equals(Lv, Rv);

    value_free(&Lv);
    value_free(&Rv);

    return value_bool(result);
}

/* ================= INT ================= */
if (

    (Lv.type == VAL_INT && Rv.type == VAL_INT) ||

    (Lv.type == VAL_INT && Rv.type == VAL_NUMBER) ||

    (Lv.type == VAL_NUMBER && Rv.type == VAL_INT) ||

    (Lv.type == VAL_NUMBER && Rv.type == VAL_NUMBER)

)

{

    double L = (Lv.type == VAL_INT) ? Lv.integer : Lv.number;
    double R = (Rv.type == VAL_INT) ? Rv.integer : Rv.number;

    value_free(&Lv);
    value_free(&Rv);

if (Lv.type == VAL_INT && Rv.type == VAL_INT) {

    int Li = (int)L;
    int Ri = (int)R;

    if (op == '+') return value_int(Li + Ri);
    if (op == '-') return value_int(Li - Ri);
    if (op == '*') return value_int(Li * Ri);

    if (op == '%') {

        if (Ri == 0) {

            shriji_error(
                E_RUNTIME_DIV_ZERO,
                "modulo",
                "0 se modulo nahi kar sakte",
                "denominator 0 nahi hona chahiye"
            );

            return value_null();
        }

        return value_int(Li % Ri);
    }
}


    if (op == '+') return value_number(L + R);
    if (op == '-') return value_number(L - R);
    if (op == '*') return value_number(L * R);

    if (op == '/') {

        if (R == 0) {
            shriji_error(
                E_RUNTIME_DIV_ZERO,
                "division",
                "0 se divide nahi kar sakte",
                "denominator 0 nahi hona chahiye"
            );
            return value_null();
        }
        return value_number(L / R);
    }
     if (op == '%') {

    if (R == 0) {

        shriji_error(
            E_RUNTIME_DIV_ZERO,
            "modulo",
            "0 se modulo nahi kar sakte",
            "denominator 0 nahi hona chahiye"
        );

        return value_null();
    }
    return value_number(safe_mod(L, R));

}

    if (op == '>') return value_bool(L > R);
    if (op == '<') return value_bool(L < R);
    if (op == 'G') return value_bool(L >= R);
    if (op == 'L') return value_bool(L <= R);
    if (op == '=') return value_bool(L == R);
    if (op == '!') return value_bool(L != R);

    return value_null();
}


    /* ================= UNSUPPORTED ================= */
    value_free(&Lv);
    value_free(&Rv);

    shriji_error(
        E_PARSE_02,
        "binary",
        "ye operation is type ke liye allowed nahi hai",
        "sirf number ya string supported hai"
    );

    rt->state.safety = STATE_CRITICAL;
    return value_null();
}


       case AST_NOT: {
    Value v = eval(node->left, env, rt);

    int truth = value_is_truthy(v);
    value_free(&v);

    return value_bool(!truth);
    }


case AST_IF: {
    Value condv = eval(node->condition, env, rt);

    Value result = value_null();

    if (value_is_truthy(condv)) {

        env_push_scope(env);

        result = eval(node->left, env, rt);

        env_pop_scope(env);
    }
    else if (node->else_block) {

        env_push_scope(env);

        result = eval(node->else_block, env, rt);

        env_pop_scope(env);
    }

    value_free(&condv);
    return result;
}



case AST_WHILE: {

    rt->loop_depth++;

    int local_guard = 0;

    while (1) {

        Value condv = eval(node->condition, env, rt);

        if (!value_is_truthy(condv)) {
            value_free(&condv);
            break;
        }

        value_free(&condv);

        rt->continue_flag = 0;

        eval(node->body, env, rt);

        if (rt->error_flag) {
           rt->loop_depth--;
            return value_null();
      }

        if (rt->return_flag) {
            rt->loop_depth--;
            return value_copy(rt->return_value);
        }

        if (rt->break_flag) {
            rt->break_flag = 0;
            break;
        }

        if (rt->continue_flag) {
            rt->continue_flag = 0;
            continue;
        }

        if (++local_guard > 1000000) {
            shriji_error(
                E_RUNTIME_01,
                "loop",
                "infinite loop detected",
                "use rukja or fix condition"
            );
            rt->state.safety = STATE_CRITICAL;
            break;
        }
    }

    rt->loop_depth--;
    return value_null();
}

case AST_BLOCK: {

    Value last = value_null();

    for (int i = 0; i < node->stmt_count; i++) {

        Value temp = eval(node->statements[i], env, rt);

        /* STOP immediately on runtime error */
        if (rt && rt->error_flag) {
            value_free(&temp);
            value_free(&last);
            return value_null();
        }

        value_free(&last);

        /* ownership transfer */
        last = temp;

        if (rt->return_flag ||
            rt->break_flag ||
            rt->continue_flag)
            break;
    }

    if (rt->return_flag)
        return value_copy(rt->return_value);

    return last;
}

case AST_PROGRAM: {

    Value last = value_null();

    for (int i = 0; i < node->stmt_count; i++) {

        Value temp = eval(node->statements[i], env, rt);

        if (rt && rt->error_flag) {
            value_free(&temp);
            return value_null();
        }

        value_free(&last);

        /* ownership transfer */
        last = temp;

        if (rt->break_flag || rt->continue_flag)
            break;
    }

    if (rt->return_flag)
        return value_copy(rt->return_value);

    return last;
}

case AST_IMPORT: {

    /* ENABLE ANALYSIS MODE */
    shriji_set_error_mode(ERROR_MODE_COLLECT);

    /* import "file.sri" */
    const char *path = node->name;

    if (is_import_active(path))
{
    shriji_error(
        E_PARSE_02,
        "import",
        "circular import detected",
        "file already importing"
    );

    shriji_print_all_errors();
    shriji_set_error_mode(ERROR_MODE_IMMEDIATE);

    return value_null();
}

    if (!path || !*path) {
        shriji_error(
            E_PARSE_02,
            "import",
            "empty import path",
            "use: import \"file.sri\""
        );
        shriji_set_error_mode(ERROR_MODE_IMMEDIATE);
        return value_null();
    }

    strncpy(import_stack[import_depth], path, 255);
import_stack[import_depth][255] = '\0';
import_depth++;

    /* read file */
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        shriji_error(
            E_PARSE_02,
            "import",
            "file not found",
            "check path or create file first"
        );
        shriji_set_error_mode(ERROR_MODE_IMMEDIATE);
        return value_null();
    }

    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (sz < 0) sz = 0;
    if (sz > 1024 * 1024) sz = 1024 * 1024;

    char *buf = (char *)malloc((size_t)sz + 1);
    if (!buf) {
        fclose(fp);
        shriji_set_error_mode(ERROR_MODE_IMMEDIATE);
        return value_null();
    }

    size_t nread = fread(buf, 1, (size_t)sz, fp);
    buf[nread] = '\0';
    fclose(fp);

    /*  FULL FILE PARSE */
    ASTNode *prog = parse_program(buf);
    free(buf);

    if (!prog) {
        shriji_error(
            E_PARSE_02,
            "import",
            "parse failed",
            "check full file syntax"
        );

        shriji_print_all_errors();
        shriji_set_error_mode(ERROR_MODE_IMMEDIATE);
        import_depth--;
        return value_null();
    }

     int old_export_count = rt->export_count;

      rt->export_count = 0;

       Env *module_env = new_env();
    /*  RUN FULL PROGRAM */
    Value result = eval(prog, module_env, rt);

   for (int i = 0; i < rt->export_count; i++)
{

    Value v = env_get(
        module_env,
        rt->exports[i]
    );

    env_set(
        env,
        rt->exports[i],
        v
    );
}

    /*  PRINT ALL ERRORS (ONE SHOT) */
    shriji_print_all_errors();

    /*  BACK TO NORMAL MODE */
    shriji_set_error_mode(ERROR_MODE_IMMEDIATE);

    rt->export_count = old_export_count;

         free_env(module_env);

         import_depth--;

         return result;
}

case AST_EXPORT:
{
    if (rt && rt->export_count < 256)
    {
        strncpy(
            rt->exports[rt->export_count],
            node->name,
            63
        );

        rt->exports[rt->export_count][63] = '\0';

        rt->export_count++;
    }

    return value_null();
}

case AST_COMMAND: {

    CommandType cmd = resolve_command(node->command_name);
    if (cmd == CMD_UNKNOWN) {
        shriji_error(
            E_PARSE_02,
            "command",
            "unknown command",
            "command not recognized"
        );
        return value_null();
    }

if (cmd == CMD_BOLO)
{
    if (error_reported)
        return value_null();

    Value v = value_null();

    if (node->value)
        v = eval(node->value, env, rt);

    if (rt->error_flag) {
        value_free(&v);
        return value_null();
    }

    if (rt) {
        rt->last_output_mode = OUTPUT_EXPLICIT;
    }

    smriti_session_set_last(v);

    //  FINAL FIX HERE
    value_print(v);
    printf("\n");
    fflush(stdout);

    value_free(&v);

    return value_null();
}

/* AI MODULES → ai_router (STEP-13 REAL OUTPUT) */
if (cmd == CMD_SAKHI || cmd == CMD_NIYU ||
    cmd == CMD_MIRA  || cmd == CMD_KAVYA) {

    Value v = value_null();
    if (node->value)
        v = eval(node->value, env , rt);

    const char *arg = "";
    char tmp[64] = {0};

    if (v.type == VAL_STRING && v.string)
        arg = strip_quotes(v.string);
    else if (v.type == VAL_NUMBER) {
        snprintf(tmp, sizeof(tmp), "%g", v.number);
        arg = tmp;
    }

    ShrijiBridgePacket pkt;
    pkt.text   = arg;
    pkt.lang   = SHRIJI_LANG_AUTO;
    pkt.source = SHRIJI_SRC_REPL;

    L3Response r = ai_router_dispatch(&pkt);
    if (r.text && *r.text)

    value_free(&v);
    return value_null();
}

    /* DEFAULT COMMAND */
    return value_number(execute_command(cmd));
}

default:
    return value_null();
}
}

