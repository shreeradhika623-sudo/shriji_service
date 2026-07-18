#include "std_db_statement.h"
#include "std_db.h"
#include "db_handle.h"
#include "db_statement.h"
#include "db_statement_handle.h"
#include "interpreter.h"

#include <string.h>

/*
 * ------------------------------------------------------------
 * SHRIJI STANDARD DATABASE STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Statement related APIs.
 * ------------------------------------------------------------
 */

Value std_sqlite_prepare(
    ShrijiRuntime *rt,
    Value db,
    const char *sql)
{
    (void)rt;

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

    sqlite3_stmt *stmt =
        db_prepare(
            handle->connection,
            sql);

    if (stmt == NULL)
    {
        return value_null();
    }

    DBStatementHandle *statement =
        db_statement_handle_create(
            stmt);

    if (statement == NULL)
    {
        db_finalize(stmt);

        return value_null();
    }

    return value_db_statement(
        statement);
}

Value std_sqlite_finalize(
    ShrijiRuntime *rt,
    Value stmt)
{
    (void)rt;

    if (stmt.type != VAL_DB_STATEMENT)
    {
        return value_null();
    }

    DBStatementHandle *statement =
        stmt.statement;

    if (statement == NULL)
    {
        return value_null();
    }

    db_finalize(
        statement->statement);

    db_statement_handle_free(
        statement);

    return value_null();
}



Value std_db_statement_call(
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
     * sqlite_prepare()
     * sqlite_finalize()
     */

        if (strcmp(node->function_name, "sqlite_prepare") == 0)
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
            std_sqlite_prepare(
                rt,
                db,
                sql.string);

        value_free(&db);
        value_free(&sql);

        return result;
    }

    if (strcmp(node->function_name, "sqlite_finalize") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1)
        {
            return value_null();
        }

        Value stmt =
            eval(node->args[0], env, rt);

        Value result =
            std_sqlite_finalize(
                rt,
                stmt);

        value_free(&stmt);

        return result;
    }

    return value_null();
}
