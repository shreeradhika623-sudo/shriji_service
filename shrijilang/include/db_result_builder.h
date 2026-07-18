#ifndef DB_RESULT_BUILDER_H
#define DB_RESULT_BUILDER_H

#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT BUILDER
 * ------------------------------------------------------------
 * Responsibility:
 *      Build DBResult objects from database callbacks.
 *
 * Never:
 *      Execute SQL.
 *      Open/Close database.
 *      Manage database connections.
 * ------------------------------------------------------------
 */

int db_result_add_row(DBResult *result);

int db_result_add_cell(
    DBResult *result,
    int row,
    const char *text);

int db_result_add_null_cell(
    DBResult *result,
    int row);

int db_result_set_column_name(
    DBResult *result,
    int column,
    const char *name);
#endif
