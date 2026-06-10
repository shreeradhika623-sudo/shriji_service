#define _POSIX_C_SOURCE 200809L

#include "stdlib/std_env.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <stdlib.h>

Value std_env_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /* GETENV */

    if (
        strcmp(node->function_name, "getenv") == 0 ||
        strcmp(node->function_name, "mahaul_lo") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

 shriji_arg_count_error(
    "getenv",
    1,
    node->arg_count
);

            return value_null();
        }

        Value keyv = eval(node->args[0], env, rt);

        if (
            keyv.type != VAL_STRING ||
            !keyv.string
        ) {
            value_free(&keyv);

shriji_arg_type_error(
    "getenv",
    "string"
);

            return value_null();
        }

        const char *value = getenv(keyv.string);

        Value out;

        if (value)
            out = value_string(value);
        else
            out = value_string("");

        value_free(&keyv);

        return out;
    }

    /* SETENV */

    if (
        strcmp(node->function_name, "setenv") == 0 ||
        strcmp(node->function_name, "mahaul_rakho") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 2) {

shriji_arg_count_error(
    "setenv",
    2,
    node->arg_count
);

            return value_null();
        }

        Value keyv = eval(node->args[0], env, rt);
        Value valv = eval(node->args[1], env, rt);

        if (
            keyv.type != VAL_STRING ||
            !keyv.string
        ) {
            value_free(&keyv);
            value_free(&valv);

shriji_arg_type_error(
    "setenv",
    "string"
);

            return value_null();
        }

        if (
            valv.type != VAL_STRING ||
            !valv.string
        ) {
            value_free(&keyv);
            value_free(&valv);

shriji_arg_type_error(
    "setenv",
    "string"
);

            return value_null();
        }

#ifdef _WIN32
        int result = _putenv_s(
            keyv.string,
            valv.string
        );
#else
        int result = setenv(
            keyv.string,
            valv.string,
            1
        );
#endif

        value_free(&keyv);
        value_free(&valv);

        return value_bool(result == 0);
    }

    return value_null();
}
