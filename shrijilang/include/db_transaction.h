#ifndef DB_TRANSACTION_H
#define DB_TRANSACTION_H

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE TRANSACTION
 * ------------------------------------------------------------
 * Responsibility:
 *      Manage database transactions.
 *
 * Supported:
 *      BEGIN
 *      COMMIT
 *      ROLLBACK
 *
 * Never:
 *      Execute arbitrary SQL.
 *      Open database.
 *      Close database.
 * ------------------------------------------------------------
 */

int db_begin(
    sqlite3 *db);

int db_commit(
    sqlite3 *db);

int db_rollback(
    sqlite3 *db);

#endif
