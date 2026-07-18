#ifndef DB_RESET_H
#define DB_RESET_H

#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESET
 * ------------------------------------------------------------
 * Responsibility:
 *      Reset prepared statements for reuse.
 *
 * Never:
 *      Prepare statements.
 *      Bind values.
 *      Execute statements.
 *      Finalize statements.
 * ------------------------------------------------------------
 */

int db_reset(
    sqlite3_stmt *stmt);

#endif
