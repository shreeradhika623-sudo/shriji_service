#include "stdlib/std_dict.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <stdlib.h>

Value std_dict_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /*──────────────────────────────────────────────
      KEYS
    ──────────────────────────────────────────────*/
    if (
        strcmp(node->function_name, "keys") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "keys",
                "keys ko ek shabdkosh chahiye",
                "udaharan: keys(user)"
            );

            return value_null();
        }

        Value v = eval(node->args[0], env, rt);

        if (v.type != VAL_DICT) {

            value_free(&v);

            shriji_error(
                E_PARSE_02,
                "keys",
                "sirf shabdkosh ki keys nikali ja sakti hain",
                "udaharan: keys(user)"
            );

            return value_null();
        }

        int n = v.dict_count;

        Value *items = malloc(sizeof(Value) * n);

        for (int i = 0; i < n; i++) {
            items[i] = value_copy(v.dict_keys[i]);
        }

        value_free(&v);

        return value_list(items, n);
    }

/*──────────────────────────────────────────────
  VALUES / MAAN / MOOLYA
──────────────────────────────────────────────*/
if (
    strcmp(node->function_name, "maan") == 0 ||
    strcmp(node->function_name, "moolya") == 0 ||
    strcmp(node->function_name, "values") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "maan",
            "maan ko ek shabdkosh chahiye",
            "udaharan: maan(user)"
        );

        return value_null();
    }

    Value v = eval(node->args[0], env, rt);

    if (v.type != VAL_DICT) {

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "maan",
            "sirf shabdkosh ke maan nikale ja sakte hain",
            "udaharan: maan(user)"
        );

        return value_null();
    }

    int n = v.dict_count;

    Value *items = malloc(sizeof(Value) * n);

    for (int i = 0; i < n; i++) {
        items[i] = value_copy(v.dict_values[i]);
    }

    value_free(&v);

    return value_list(items, n);
}

/*──────────────────────────────────────────────
  HAI_KEY / HAS_KEY
──────────────────────────────────────────────*/
if (
    strcmp(node->function_name, "hai_key") == 0 ||
    strcmp(node->function_name, "has_key") == 0
)
{
    *handled = 1;

    if (node->arg_count != 2) {

        shriji_error(
            E_PARSE_02,
            "has_key",
            "has_key ko 2 maan chahiye",
            "udaharan: has_key(user, \"naam\")"
        );

        return value_null();
    }

    Value dictv = eval(node->args[0], env, rt);
    Value keyv  = eval(node->args[1], env, rt);

    if (dictv.type != VAL_DICT) {

        value_free(&dictv);
        value_free(&keyv);

        shriji_error(
            E_PARSE_02,
            "has_key",
            "pehla maan dictionary hona chahiye",
            "udaharan: has_key(user, \"naam\")"
        );

        return value_null();
    }

    if (keyv.type != VAL_STRING) {

        value_free(&dictv);
        value_free(&keyv);

        shriji_error(
            E_PARSE_02,
            "has_key",
            "key string honi chahiye",
            "udaharan: has_key(user, \"naam\")"
        );

        return value_null();
    }

    for (int i = 0; i < dictv.dict_count; i++) {

        if (
            dictv.dict_keys[i].type == VAL_STRING &&
            dictv.dict_keys[i].string &&
            strcmp(
                dictv.dict_keys[i].string,
                keyv.string
            ) == 0
        ) {

            value_free(&dictv);
            value_free(&keyv);

            return value_bool(1);
        }
    }

    value_free(&dictv);
    value_free(&keyv);

    return value_bool(0);
}

     return value_null();
}


