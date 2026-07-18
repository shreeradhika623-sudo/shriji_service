#include "db_transaction.h"

#include "db_execute.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE TRANSACTION
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute transaction commands.
 * ------------------------------------------------------------
 */

int db_begin(
    sqlite3 *db)
{
    return db_execute(
        db,
        "BEGIN TRANSACTION;");
}

int db_commit(
    sqlite3 *db)
{
    return db_execute(
        db,
        "COMMIT;");
}

int db_rollback(
    sqlite3 *db)
{
    return db_execute(
        db,
        "ROLLBACK;");
}
