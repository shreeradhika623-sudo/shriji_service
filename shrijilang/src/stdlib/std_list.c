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

/*
--------------------------------------------------
JOIN / JODO
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "join") == 0 ||
    strcmp(node->function_name, "jodo") == 0
)
{
    *handled = 1;

    if (node->arg_count != 2) {

      shriji_error(
    E_PARSE_02,
    "join",
    "2 argument chahiye",
    "udaharan: join(list, value)"
   );
        return value_null();
    }

    Value listv = eval(node->args[0], env, rt);
    Value item  = eval(node->args[1], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);
        value_free(&item);

       shriji_error(
    E_PARSE_02,
    "join",
    "pehla argument list hona chahiye",
    "udaharan: join(list, value)"
   );

        return value_null();
    }

    int new_count = listv.count + 1;

    Value *items = malloc(sizeof(Value) * new_count);

    for (int i = 0; i < listv.count; i++) {
        items[i] = value_copy(listv.items[i]);
    }

    items[listv.count] = value_copy(item);

    value_free(&item);
    value_free(&listv);

    return value_list(items, new_count);
}

/*
--------------------------------------------------
REMOVE / HATAO
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "remove") == 0 ||
    strcmp(node->function_name, "hatao") == 0
)
{
    *handled = 1;

    if (node->arg_count != 2) {

     shriji_error(
    E_PARSE_02,
    "remove",
    "2 argument chahiye",
    "udaharan: remove(list, value)"
);
        return value_null();
    }

    Value listv = eval(node->args[0], env, rt);
    Value target = eval(node->args[1], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);
        value_free(&target);

       shriji_error(
    E_PARSE_02,
    "remove",
    "pehla argument list hona chahiye",
    "udaharan: remove(list, value)"
   );
        return value_null();
    }

    int keep = 0;

    for (int i = 0; i < listv.count; i++) {

        int match = 0;

        if (
            listv.items[i].type == VAL_NUMBER &&
            target.type == VAL_NUMBER &&
            listv.items[i].number == target.number
        ) {
            match = 1;
        }

        if (!match)
            keep++;
    }

    Value *items = malloc(sizeof(Value) * keep);

    int pos = 0;

    for (int i = 0; i < listv.count; i++) {

        int match = 0;

        if (
            listv.items[i].type == VAL_NUMBER &&
            target.type == VAL_NUMBER &&
            listv.items[i].number == target.number
        ) {
            match = 1;
        }

        if (!match)
            items[pos++] =
                value_copy(listv.items[i]);
    }

    value_free(&listv);
    value_free(&target);

    return value_list(items, keep);
}

    return value_null();
}
