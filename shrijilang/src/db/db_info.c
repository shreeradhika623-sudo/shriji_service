#include "db_info.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE INFO
 * ------------------------------------------------------------
 * Responsibility:
 *      Wrap SQLite information APIs.
 * ------------------------------------------------------------
 */

sqlite3_int64 db_last_insert_id(
    sqlite3 *db)
{
    return sqlite3_last_insert_rowid(db);
}

int db_changes(
    sqlite3 *db)
{
    return sqlite3_changes(db);
}
