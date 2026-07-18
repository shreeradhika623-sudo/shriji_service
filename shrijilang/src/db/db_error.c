#include "db_error.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE ERROR
 * ------------------------------------------------------------
 * Responsibility:
 *      Wrap SQLite error functions.
 * ------------------------------------------------------------
 */

const char *db_error(
    sqlite3 *db)
{
    return sqlite3_errmsg(db);
}

int db_error_code(
    sqlite3 *db)
{
    return sqlite3_errcode(db);
}
