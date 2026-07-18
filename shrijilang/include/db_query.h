#ifndef DB_QUERY_H
#define DB_QUERY_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY
 * ------------------------------------------------------------
 * Responsibility:
 *     Execute SQL SELECT queries.
 *
 * NOTE:
 *     CREATE / INSERT / UPDATE / DELETE
 *     belong to db_execute.c
 * ------------------------------------------------------------
 */

int db_query(
    sqlite3 *db,
    const char *sql,
    int (*callback)(void *, int, char **, char **),
    void *data);

#endif
