#include "std_db_step.h"
#include "db_step.h"
#include "db_statement_handle.h"
#include "std_db.h"
#include "db_reset.h"
#include "interpreter.h"

#include <string.h>

/*
 * ------------------------------------------------------------
 * SHRIJI STANDARD DATABASE STEP
 * ------------------------------------------------------------
 * Responsibility:
 *      Step related APIs.
 * ------------------------------------------------------------
 */

Value std_sqlite_step(
    ShrijiRuntime *rt,
    Value stmt)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT)
    {
        return value_bool(0);
    }

    DBStatementHandle *statement =
        stmt.statement;

    if (statement == NULL)
    {
        return value_bool(0);
    }

    int rc =
        db_step(
            statement->statement);

    return value_bool(
        rc == SQLITE_ROW ||
        rc == SQLITE_DONE);
}

Value std_sqlite_reset(
    ShrijiRuntime *rt,
    Value stmt)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT)
    {
        return value_bool(0);
    }

    DBStatementHandle *statement =
        stmt.statement;

    if (statement == NULL)
    {
        return value_bool(0);
    }

    int rc =
        db_reset(
            statement->statement);

    return value_bool(
        rc == SQLITE_OK);
}


Value std_db_step_call(
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
     * sqlite_step()
     * sqlite_reset()
     */

    if (strcmp(node->function_name, "sqlite_step") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value result =
            std_sqlite_step(
                rt,
                stmt);

        value_free(&stmt);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_reset") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value result =
            std_sqlite_reset(
                rt,
                stmt);

        value_free(&stmt);

        return result;
    }

    return value_null();
}
