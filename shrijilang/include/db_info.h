#ifndef DB_INFO_H
#define DB_INFO_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE INFO
 * ------------------------------------------------------------
 * Responsibility:
 *      Provide execution information.
 *
 * Supported:
 *      Last inserted row id.
 *      Rows changed.
 *
 * Never:
 *      Execute SQL.
 *      Print.
 * ------------------------------------------------------------
 */

sqlite3_int64 db_last_insert_id(
    sqlite3 *db);

int db_changes(
    sqlite3 *db);

#endif
