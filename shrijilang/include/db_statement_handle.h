#ifndef DB_STATEMENT_HANDLE_H
#define DB_STATEMENT_HANDLE_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STATEMENT HANDLE
 * ------------------------------------------------------------
 * Responsibility:
 *      Own a prepared statement object.
 *
 * Never:
 *      Open database.
 *      Execute SQL.
 *      Bind values.
 *      Print.
 * ------------------------------------------------------------
 */

typedef struct
{
    sqlite3_stmt *statement;

} DBStatementHandle;

DBStatementHandle *db_statement_handle_create(
    sqlite3_stmt *statement);

void db_statement_handle_free(
    DBStatementHandle *handle);

#endif
