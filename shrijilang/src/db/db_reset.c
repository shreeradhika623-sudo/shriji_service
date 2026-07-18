#include "db_reset.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESET
 * ------------------------------------------------------------
 * Responsibility:
 *      Reset prepared statements.
 * ------------------------------------------------------------
 */

int db_reset(
    sqlite3_stmt *stmt)
{
    return sqlite3_reset(stmt);
}
