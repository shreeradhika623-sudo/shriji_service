#include "std_db_bind.h"

#include "std_db.h"

#include "interpreter.h"

#include <string.h>

/*
 * ------------------------------------------------------------
 * SHRIJI STANDARD DATABASE BIND
 * ------------------------------------------------------------
 * Responsibility:
 *      sqlite_bind_*() dispatcher.
 * ------------------------------------------------------------
 */

Value std_db_bind_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled)
{
    (void)node;
    (void)env;
    (void)rt;

    *handled = 0;

    /*
     * Next:
     *
     * sqlite_bind_int()
     * sqlite_bind_double()
     * sqlite_bind_text()
     * sqlite_bind_null()
     */

        if (strcmp(node->function_name, "sqlite_bind_int") == 0)
    {
        *handled = 1;

        if (node->arg_count != 3)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value index =
            eval(node->args[1], env, rt);

        Value value =
            eval(node->args[2], env, rt);

        Value result =
            std_sqlite_bind_int(
                rt,
                stmt,
                (int)value_as_number(index),
                (int)value_as_number(value));

        value_free(&stmt);
        value_free(&index);
        value_free(&value);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_bind_double") == 0)
    {
        *handled = 1;

        if (node->arg_count != 3)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value index =
            eval(node->args[1], env, rt);

        Value value =
            eval(node->args[2], env, rt);

        Value result =
            std_sqlite_bind_double(
                rt,
                stmt,
                (int)value_as_number(index),
                value_as_number(value));

        value_free(&stmt);
        value_free(&index);
        value_free(&value);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_bind_text") == 0)
    {
        *handled = 1;

        if (node->arg_count != 3)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value index =
            eval(node->args[1], env, rt);

        Value text =
            eval(node->args[2], env, rt);

        Value result =
            std_sqlite_bind_text(
                rt,
                stmt,
                (int)value_as_number(index),
                text.string);

        value_free(&stmt);
        value_free(&index);
        value_free(&text);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_bind_null") == 0)
    {
        *handled = 1;

        if (node->arg_count != 2)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value index =
            eval(node->args[1], env, rt);

        Value result =
            std_sqlite_bind_null(
                rt,
                stmt,
                (int)value_as_number(index));

        value_free(&stmt);
        value_free(&index);

        return result;
    }

    return value_null();
}

