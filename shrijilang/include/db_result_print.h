#ifndef DB_RESULT_PRINT_H
#define DB_RESULT_PRINT_H

#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT PRINTER
 * ------------------------------------------------------------
 * Responsibility:
 *      Print DBResult for debugging.
 *
 * Never:
 *      Execute SQL.
 *      Modify DBResult.
 *      Allocate memory.
 * ------------------------------------------------------------
 */

void db_result_print(
    const DBResult *result);

#endif
