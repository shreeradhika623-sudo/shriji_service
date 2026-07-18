#include "std_db_query.h"

#include "runtime_db.h"
#include "db_handle.h"
#include "db_result_converter.h"

#include "std_db.h"

#include "interpreter.h"

#include <string.h>

    Value std_sqlite_execute(
    ShrijiRuntime *rt,
    Value db,
    const char *sql)
{

    if (db.type != VAL_DATABASE)
    {
        return value_bool(0);
    }

    DBHandle *handle =
        db.database;

    if (handle == NULL)
    {
        return value_bool(0);
    }

    int rc =
        runtime_db_execute(
            rt,
            handle->connection,
            sql);

    return value_bool(
        rc == SQLITE_OK);
}

    Value std_sqlite_query(
    ShrijiRuntime *rt,
    Value db,
    const char *sql)
{
    if (db.type != VAL_DATABASE)
    {
        return value_null();
    }

    DBHandle *handle =
        db.database;

    if (handle == NULL)
    {
        return value_null();
    }

    DBResult *result =
        runtime_db_query(
            rt,
            handle->connection,
            sql);


Value value =
    db_result_to_value(
        result);

    db_result_free(
    result);

    return value;
}



Value std_db_query_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled)
{
    *handled = 0;

    if (strcmp(node->function_name, "sqlite_execute") == 0)
    {
        *handled = 1;

        if (node->arg_count != 2)
        {
            return value_null();
        }

        Value db =
            eval(node->args[0], env, rt);

        Value sql =
            eval(node->args[1], env, rt);

        Value result =
            std_sqlite_execute(
                rt,
                db,
                sql.string);

        value_free(&db);
        value_free(&sql);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_query") == 0)
    {
        *handled = 1;

        if (node->arg_count != 2)
        {
            return value_null();
        }

        Value db =
            eval(node->args[0], env, rt);

        Value sql =
            eval(node->args[1], env, rt);

        Value result =
            std_sqlite_query(
                rt,
                db,
                sql.string);

        value_free(&db);
        value_free(&sql);

        return result;
    }

    return value_null();
}
