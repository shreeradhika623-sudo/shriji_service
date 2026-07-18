#include <stdio.h>

#include "db_bind.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE BIND
 * ------------------------------------------------------------
 * Responsibility:
 *      Bind values to SQLite statements.
 * ------------------------------------------------------------
 */

int db_bind_int(
    sqlite3_stmt *stmt,
    int index,
    int value)
{
    return sqlite3_bind_int(
        stmt,
        index,
        value);
}

int db_bind_double(
    sqlite3_stmt *stmt,
    int index,
    double value)
{
    return sqlite3_bind_double(
        stmt,
        index,
        value);
}

int db_bind_text(
    sqlite3_stmt *stmt,
    int index,
    const char *text)
{
    return sqlite3_bind_text(
        stmt,
        index,
        text,
        -1,
        SQLITE_TRANSIENT);
}

int db_bind_null(
    sqlite3_stmt *stmt,
    int index)
{
    return sqlite3_bind_null(
        stmt,
        index);
}
