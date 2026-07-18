#ifndef DB_QUERY_CALLBACK_H
#define DB_QUERY_CALLBACK_H

#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY CALLBACK
 * ------------------------------------------------------------
 * Responsibility:
 *      Convert SQLite callback data into DBResult.
 *
 * Never:
 *      Execute SQL.
 *      Open database.
 *      Close database.
 * ------------------------------------------------------------
 */

int db_query_callback(
    void *data,
    int columns,
    char **values,
    char **names);

#endif
