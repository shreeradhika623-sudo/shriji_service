#ifndef DB_RESULT_CONVERTER_H
#define DB_RESULT_CONVERTER_H

#include "db_result.h"
#include "value.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT CONVERTER
 * ------------------------------------------------------------
 * Responsibility:
 *      Convert DBResult into Shriji Value.
 *
 * Never:
 *      Execute SQL.
 *      Open database.
 *      Close database.
 * ------------------------------------------------------------
 */

Value db_result_to_value(
    DBResult *result);

#endif
