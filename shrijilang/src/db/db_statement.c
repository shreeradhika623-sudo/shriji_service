#include <stdio.h>

#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Prepare and destroy SQLite statements.
 * ------------------------------------------------------------
 */

sqlite3_stmt *db_prepare(
    sqlite3 *db,
    const char *sql)
{
    sqlite3_stmt *stmt = NULL;

    int rc = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        NULL);

    if (rc != SQLITE_OK)
    {
        printf("Database Prepare Error: %s\n",
               sqlite3_errmsg(db));

        return NULL;
    }

    return stmt;
}

void db_finalize(
    sqlite3_stmt *stmt)
{
    if (stmt != NULL)
    {
        sqlite3_finalize(stmt);
    }
}
