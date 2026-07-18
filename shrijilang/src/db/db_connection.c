#include <stdio.h>

#include "db.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE CONNECTION
 * ------------------------------------------------------------
 * Responsibility:
 *     - Open database connection
 *     - Close database connection
 *
 * NOTE:
 *     Do NOT execute SQL here.
 *     SQL execution belongs to db_execute.c
 * ------------------------------------------------------------
 */

sqlite3 *db_open(const char *filename)
{
    sqlite3 *db = NULL;

    int rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK)
    {
        printf("Database Open Failed: %s\n",
               sqlite3_errmsg(db));

        sqlite3_close(db);

        return NULL;
    }

    return db;
}

void db_close(sqlite3 *db)
{
    if (db != NULL)
    {
        sqlite3_close(db);
    }
}
