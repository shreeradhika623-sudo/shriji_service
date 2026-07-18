#ifndef DB_H
#define DB_H

#include "sqlite3.h"

/*
 * SHRIJI DATABASE LAYER
 * ---------------------
 * Entire project will access SQLite only through this API.
 */

sqlite3 *db_open(const char *filename);

void db_close(sqlite3 *db);

#endif
