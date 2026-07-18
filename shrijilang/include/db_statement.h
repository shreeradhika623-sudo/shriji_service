#ifndef DB_STATEMENT_H
#define DB_STATEMENT_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Prepare SQL statements.
 *
 * Never:
 *      Bind values.
 *      Execute statements.
 *      Close database.
 * ------------------------------------------------------------
 */

sqlite3_stmt *db_prepare(
    sqlite3 *db,
    const char *sql);

void db_finalize(
    sqlite3_stmt *stmt);

#endif
