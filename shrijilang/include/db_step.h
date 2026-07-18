#ifndef DB_STEP_H
#define DB_STEP_H

#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STEP
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute prepared statements.
 *
 * Never:
 *      Prepare statements.
 *      Bind values.
 *      Finalize statements.
 * ------------------------------------------------------------
 */

int db_step(
    sqlite3_stmt *stmt);

#endif
