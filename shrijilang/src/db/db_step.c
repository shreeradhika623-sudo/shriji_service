#include "db_step.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STEP
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute prepared statements.
 * ------------------------------------------------------------
 */

int db_step(
    sqlite3_stmt *stmt)
{
    return sqlite3_step(stmt);
}
