#include <stdlib.h>

#include "db_statement_handle.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STATEMENT HANDLE
 * ------------------------------------------------------------
 * Responsibility:
 *      Create and destroy statement handles.
 * ------------------------------------------------------------
 */

DBStatementHandle *db_statement_handle_create(
    sqlite3_stmt *statement)
{
    DBStatementHandle *handle =
        malloc(sizeof(DBStatementHandle));

    if (handle == NULL)
    {
        return NULL;
    }

    handle->statement =
        statement;

    return handle;
}

void db_statement_handle_free(
    DBStatementHandle *handle)
{
    if (handle == NULL)
    {
        return;
    }

    free(handle);
}
