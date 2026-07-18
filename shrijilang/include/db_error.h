#ifndef DB_ERROR_H
#define DB_ERROR_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE ERROR
 * ------------------------------------------------------------
 * Responsibility:
 *      Provide database error information.
 *
 * Never:
 *      Print errors.
 *      Open database.
 *      Close database.
 * ------------------------------------------------------------
 */

const char *db_error(
    sqlite3 *db);

int db_error_code(
    sqlite3 *db);

#endif

