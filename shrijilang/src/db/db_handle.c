#include <stdlib.h>

#include "db_handle.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE HANDLE
 * ------------------------------------------------------------
 * Responsibility:
 *      Create and destroy database handles.
 * ------------------------------------------------------------
 */

DBHandle *db_handle_create(
    sqlite3 *connection)
{
    DBHandle *handle =
        malloc(sizeof(DBHandle));

    if (handle == NULL)
    {
        return NULL;
    }

    handle->connection =
        connection;

    return handle;
}

void db_handle_free(
    DBHandle *handle)
{
    if (handle == NULL)
    {
        return;
    }

    free(handle);
}
