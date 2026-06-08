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
    (
        listv.items[i].type == VAL_INT ||
        listv.items[i].type == VAL_NUMBER
    ) &&
    (
        target.type == VAL_INT ||
        target.type == VAL_NUMBER
    )
)
{
    double a =
        (listv.items[i].type == VAL_INT)
            ? listv.items[i].integer
            : listv.items[i].number;

    double b =
        (target.type == VAL_INT)
            ? target.integer
            : target.number;

    if (a == b)
        match = 1;
}

if (
    listv.items[i].type == VAL_STRING &&
    target.type == VAL_STRING &&
    listv.items[i].string &&
    target.string &&
    strcmp(
        listv.items[i].string,
        target.string
    ) == 0
)
{
    match = 1;
}

if (
    listv.items[i].type == VAL_BOOL &&
    target.type == VAL_BOOL &&
    listv.items[i].boolean ==
    target.boolean
)
{
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
        (
            listv.items[i].type == VAL_INT ||
            listv.items[i].type == VAL_NUMBER
        ) &&
        (
            target.type == VAL_INT ||
            target.type == VAL_NUMBER
        )
    )
    {
        double a =
            (listv.items[i].type == VAL_INT)
                ? listv.items[i].integer
                : listv.items[i].number;

        double b =
            (target.type == VAL_INT)
                ? target.integer
                : target.number;

        if (a == b)
            match = 1;
    }

if (
    listv.items[i].type == VAL_STRING &&
    target.type == VAL_STRING &&
    listv.items[i].string &&
    target.string &&
    strcmp(
        listv.items[i].string,
        target.string
    ) == 0
)
{
    match = 1;
}

if (
    listv.items[i].type == VAL_BOOL &&
    target.type == VAL_BOOL &&
    listv.items[i].boolean ==
    target.boolean
)
{
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

/*
--------------------------------------------------
CONTAINS / SHAMIL
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "contains") == 0 ||
    strcmp(node->function_name, "shamil") == 0
)
{
    *handled = 1;

    if (node->arg_count != 2) {

        shriji_error(
            E_PARSE_02,
            "contains",
            "2 argument chahiye",
            "udaharan: contains(list, value)"
        );

        return value_null();
    }

    Value listv =
        eval(node->args[0], env, rt);

    Value target =
        eval(node->args[1], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);
        value_free(&target);

        return value_bool(0);
    }

    for (int i = 0; i < listv.count; i++)
    {
        int match = 0;

        if (
            (
                listv.items[i].type == VAL_INT ||
                listv.items[i].type == VAL_NUMBER
            ) &&
            (
                target.type == VAL_INT ||
                target.type == VAL_NUMBER
            )
        )
        {
            double a =
                (listv.items[i].type == VAL_INT)
                    ? listv.items[i].integer
                    : listv.items[i].number;

            double b =
                (target.type == VAL_INT)
                    ? target.integer
                    : target.number;

            if (a == b)
                match = 1;
        }

        if (
            listv.items[i].type == VAL_STRING &&
            target.type == VAL_STRING &&
            listv.items[i].string &&
            target.string &&
            strcmp(
                listv.items[i].string,
                target.string
            ) == 0
        )
        {
            match = 1;
        }

        if (
            listv.items[i].type == VAL_BOOL &&
            target.type == VAL_BOOL &&
            listv.items[i].boolean ==
            target.boolean
        )
        {
            match = 1;
        }

        if (match)
        {
            value_free(&listv);
            value_free(&target);

            return value_bool(1);
        }
    }

    value_free(&listv);
    value_free(&target);

    return value_bool(0);
}

/*
--------------------------------------------------
POP / NIKALO
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "pop") == 0 ||
    strcmp(node->function_name, "nikalo") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "pop",
            "1 argument chahiye",
            "udaharan: pop(list)"
        );

        return value_null();
    }

    Value listv =
        eval(node->args[0], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);

        shriji_error(
            E_PARSE_02,
            "pop",
            "list chahiye",
            "udaharan: pop(list)"
        );

        return value_null();
    }

    if (listv.count <= 0) {

        value_free(&listv);

        return value_list(
            NULL,
            0
        );
    }

    int new_count =
        listv.count - 1;

    Value *items =
        malloc(
            sizeof(Value) *
            new_count
        );

    for (
        int i = 0;
        i < new_count;
        i++
    )
    {
        items[i] =
            value_copy(
                listv.items[i]
            );
    }

    value_free(&listv);

    return value_list(
        items,
        new_count
    );
}

/*
--------------------------------------------------
REVERSE / ULTA
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "reverse") == 0 ||
    strcmp(node->function_name, "ulta") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "reverse",
            "1 argument chahiye",
            "udaharan: reverse(list)"
        );

        return value_null();
    }

    Value listv =
        eval(node->args[0], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);

        shriji_error(
            E_PARSE_02,
            "reverse",
            "list chahiye",
            "udaharan: reverse(list)"
        );

        return value_null();
    }

    Value *items =
        malloc(
            sizeof(Value) *
            listv.count
        );

    if (!items)
    {
        value_free(&listv);
        return value_null();
    }

    for (
        int i = 0;
        i < listv.count;
        i++
    )
    {
        items[i] =
            value_copy(
                listv.items[
                    listv.count - 1 - i
                ]
            );
    }

    int count =
        listv.count;

    value_free(&listv);

    return value_list(
        items,
        count
    );
}

/*
--------------------------------------------------
SORT / SAJAO
--------------------------------------------------
*/

if (
    strcmp(node->function_name, "sort") == 0 ||
    strcmp(node->function_name, "sajao") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "sort",
            "1 argument chahiye",
            "udaharan: sort(list)"
        );

        return value_null();
    }

    Value listv =
        eval(node->args[0], env, rt);

    if (listv.type != VAL_LIST) {

        value_free(&listv);

        shriji_error(
            E_PARSE_02,
            "sort",
            "list chahiye",
            "udaharan: sort(list)"
        );

        return value_null();
    }

    Value *items =
        malloc(
            sizeof(Value) *
            listv.count
        );

    if (!items)
    {
        value_free(&listv);
        return value_null();
    }

    for (
        int i = 0;
        i < listv.count;
        i++
    )
    {
        items[i] =
            value_copy(
                listv.items[i]
            );
    }

    for (
        int i = 0;
        i < listv.count - 1;
        i++
    )
    {
        for (
            int j = i + 1;
            j < listv.count;
            j++
        )
        {
            double a;
            double b;

            if (
                items[i].type == VAL_INT
            )
                a = items[i].integer;
            else if (
                items[i].type == VAL_NUMBER
            )
                a = items[i].number;
            else
                continue;

            if (
                items[j].type == VAL_INT
            )
                b = items[j].integer;
            else if (
                items[j].type == VAL_NUMBER
            )
                b = items[j].number;
            else
                continue;

            if (a > b)
            {
                Value temp =
                    items[i];

                items[i] =
                    items[j];

                items[j] =
                    temp;
            }
        }
    }

    int count =
        listv.count;

    value_free(&listv);

    return value_list(
        items,
        count
    );
}
    return value_null();
}
