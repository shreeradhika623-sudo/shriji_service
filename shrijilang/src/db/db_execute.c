#include <stdio.h>

#include "db_execute.h"
#include "db_statement.h"
#include "db_step.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE EXECUTION
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute SQL statements.
 *
 * Supported:
 *      CREATE
 *      INSERT
 *      UPDATE
 *      DELETE
 *
 * NOTE:
 *      SELECT queries belong to db_query.c
 * ------------------------------------------------------------
 */

int db_execute(
    sqlite3 *db,
    const char *sql)
{
    sqlite3_stmt *stmt =
        db_prepare(
            db,
            sql);

    if (stmt == NULL)
    {
        return SQLITE_ERROR;
    }

    int rc =
        db_step(stmt);

    db_finalize(stmt);

    if (rc != SQLITE_DONE)
    {
        printf("Database Execute Error: %s\n",
               sqlite3_errmsg(db));

        return rc;
    }

    return SQLITE_OK;
}
