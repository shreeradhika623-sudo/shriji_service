#include "std_db_connection.h"

#include "std_db.h"
#include "runtime_db.h"
#include "db_handle.h"
#include "interpreter.h"

#include <string.h>


    Value std_sqlite_open(
    ShrijiRuntime *rt,
    const char *path)
{
    sqlite3 *db =
        runtime_db_open(
            rt,
            path);

    if (db == NULL)
    {
        return value_null();
    }

    DBHandle *handle =
        db_handle_create(db);

    if (handle == NULL)
    {
        runtime_db_close(
            rt,
            db);

        return value_null();
    }

    return value_database(handle);
}

    Value std_sqlite_close(
    ShrijiRuntime *rt,
    Value db)
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

    runtime_db_close(
    rt,
    handle->connection);

    db_handle_free(handle);

    return value_null();
}


Value std_db_connection_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled)
{
    *handled = 0;

    if (strcmp(node->function_name, "sqlite_open") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1)
        {
            return value_null();
        }

        Value path =
            eval(node->args[0], env, rt);

        Value result =
            std_sqlite_open(
                rt,
                path.string);

        value_free(&path);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_close") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1)
        {
            return value_null();
        }

        Value db =
            eval(node->args[0], env, rt);

        Value result =
            std_sqlite_close(
                rt,
                db);

        value_free(&db);

        return result;
    }

    return value_null();
}
