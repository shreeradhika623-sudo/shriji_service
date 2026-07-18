#ifndef DB_EXECUTE_STATEMENT_H
#define DB_EXECUTE_STATEMENT_H

#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE EXECUTE STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute prepared statements.
 *
 * Never:
 *      Prepare statements.
 *      Bind values.
 *      Reset statements.
 *      Finalize statements.
 * ------------------------------------------------------------
 */

int db_execute_statement(
    sqlite3_stmt *stmt);

#endif
