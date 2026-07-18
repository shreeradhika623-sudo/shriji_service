#ifndef DB_EXECUTE_H
#define DB_EXECUTE_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE EXECUTION
 * ------------------------------------------------------------
 * Responsibility:
 *     Execute SQL statements that do not return rows.
 *
 * Examples:
 *     CREATE TABLE
 *     INSERT
 *     UPDATE
 *     DELETE
 *
 * NOTE:
 *     SELECT queries belong to db_query.c
 * ------------------------------------------------------------
 */

int db_execute(
    sqlite3 *db,
    const char *sql);

#endif
