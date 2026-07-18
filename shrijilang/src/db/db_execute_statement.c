#include "db_execute_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE EXECUTE STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute prepared statements.
 * ------------------------------------------------------------
 */

int db_execute_statement(
    sqlite3_stmt *stmt)
{
    int rc =
        sqlite3_step(stmt);

    if (rc == SQLITE_DONE)
    {
        return SQLITE_OK;
    }

    return rc;
}
