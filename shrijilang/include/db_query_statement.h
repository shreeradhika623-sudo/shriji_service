#ifndef DB_QUERY_STATEMENT_H
#define DB_QUERY_STATEMENT_H

#include "db_statement.h"
#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute SELECT statements using prepared statements.
 *
 * Never:
 *      Use sqlite3_exec().
 *      Use SQLite callbacks.
 *      Open/Close database.
 * ------------------------------------------------------------
 */

DBResult *db_query_statement(
    sqlite3 *db,
    const char *sql);

#endif
