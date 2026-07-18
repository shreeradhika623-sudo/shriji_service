#ifndef DB_BIND_H
#define DB_BIND_H

#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE BIND
 * ------------------------------------------------------------
 * Responsibility:
 *      Bind values to prepared statements.
 *
 * Supported:
 *      Integer
 *      Double
 *      Text
 *      Null
 *
 * Never:
 *      Prepare statements.
 *      Execute statements.
 *      Finalize statements.
 * ------------------------------------------------------------
 */

int db_bind_int(
    sqlite3_stmt *stmt,
    int index,
    int value);

int db_bind_double(
    sqlite3_stmt *stmt,
    int index,
    double value);

int db_bind_text(
    sqlite3_stmt *stmt,
    int index,
    const char *text);

int db_bind_null(
    sqlite3_stmt *stmt,
    int index);

#endif
