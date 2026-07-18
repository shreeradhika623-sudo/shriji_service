#ifndef DB_HANDLE_H
#define DB_HANDLE_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE HANDLE
 * ------------------------------------------------------------
 * Responsibility:
 *      Own a database connection object.
 *
 * Never:
 *      Execute SQL.
 *      Prepare statements.
 *      Manage transactions.
 *      Print.
 * ------------------------------------------------------------
 */

typedef struct
{
    sqlite3 *connection;

} DBHandle;

DBHandle *db_handle_create(
    sqlite3 *connection);

void db_handle_free(
    DBHandle *handle);

#endif
