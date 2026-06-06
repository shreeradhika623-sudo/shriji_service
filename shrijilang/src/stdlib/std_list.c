#include "stdlib/std_list.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>

Value std_list_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    if (
        strcmp(node->function_name, "ginti") == 0 ||
        strcmp(node->function_name, "count") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "ginti",
                "1 argument required",
                "use: ginti(value)"
            );

            return value_null();
        }

        Value v = eval(node->args[0], env, rt);

        if (v.type == VAL_LIST) {

            int n = v.count;

            value_free(&v);

            return value_int(n);
        }

        if (v.type == VAL_DICT) {

            int n = v.dict_count;

            value_free(&v);

            return value_int(n);
        }

        if (v.type == VAL_STRING && v.string) {

           int n = (int)strlen(v.string);

            value_free(&v);

            return value_int(n);
        }

        value_free(&v);

        shriji_error(
            E_PARSE_02,
            "ginti",
            "list, dictionary ya string required",
            "use: ginti(list)"
        );

        return value_null();
    }

    return value_null();
}
