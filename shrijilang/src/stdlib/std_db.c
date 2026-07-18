#include <string.h>

#include "runtime_db.h"
#include "db_handle.h"
#include "value.h"
#include "db_result_converter.h"
#include "env.h"
#include "interpreter.h"
#include "std_db_connection.h"
#include "std_db_query.h"
#include "std_db_statement.h"
#include "db_statement.h"
#include "db_statement_handle.h"
#include "std_db_step.h"
#include "db_bind.h"
#include "std_db_bind.h"

/*
 * ------------------------------------------------------------
 * SHRIJI STANDARD DATABASE LIBRARY
 * ------------------------------------------------------------
 * Responsibility:
 *      Register database functions.
 * ------------------------------------------------------------
 */

    Value std_sqlite_bind_int(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    int value)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT ||
        stmt.statement == NULL ||
        stmt.statement->statement == NULL)
    {
        return value_bool(0);
    }

    return value_bool(
        db_bind_int(
            stmt.statement->statement,
            index,
            value) == SQLITE_OK);
}

Value std_sqlite_bind_double(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    double value)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT ||
        stmt.statement == NULL ||
        stmt.statement->statement == NULL)
    {
        return value_bool(0);
    }

    return value_bool(
        db_bind_double(
            stmt.statement->statement,
            index,
            value) == SQLITE_OK);
}

Value std_sqlite_bind_text(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    const char *text)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT ||
        stmt.statement == NULL ||
        stmt.statement->statement == NULL ||
        text == NULL)
    {
        return value_bool(0);
    }

    return value_bool(
        db_bind_text(
            stmt.statement->statement,
            index,
            text) == SQLITE_OK);
}

Value std_sqlite_bind_null(
    ShrijiRuntime *rt,
    Value stmt,
    int index)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT ||
        stmt.statement == NULL ||
        stmt.statement->statement == NULL)
    {
        return value_bool(0);
    }

    return value_bool(
        db_bind_null(
            stmt.statement->statement,
            index) == SQLITE_OK);
}


Value std_db_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled)
{
    (void)env;

Value result =
    std_db_connection_call(
        node,
        env,
        rt,
        handled);

if (*handled)
{
    return result;
}

    *handled = 0;

    result =
    std_db_query_call(
        node,
        env,
        rt,
        handled);

if (*handled)
{
    return result;
}

        result =
        std_db_statement_call(
            node,
            env,
            rt,
            handled);

    if (*handled)
    {
        return result;
    }

        result =
        std_db_bind_call(
            node,
            env,
            rt,
            handled);

    if (*handled)
    {
        return result;
    }

        result =
        std_db_step_call(
            node,
            env,
            rt,
            handled);

    if (*handled)
    {
        return result;
    }

      return value_null();
}

    void std_db_register(
        ShrijiRuntime *rt)
{
    (void)rt;

    /*
     * Future:
     *
     * sqlite_open()
     * sqlite_close()
     * sqlite_exec()
     * sqlite_query()
     */
}
