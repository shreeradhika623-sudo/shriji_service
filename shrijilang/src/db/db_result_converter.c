#include <stdlib.h>

#include "db_result_converter.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT CONVERTER
 * ------------------------------------------------------------
 * Responsibility:
 *      Convert DBResult into Value.
 * ------------------------------------------------------------
 */

Value db_result_to_value(
    DBResult *result)
{
    if (result == NULL)
    {
        return value_null();
    }

    if (result->row_count == 0)
    {
        return value_list(NULL, 0);
    }

    Value *rows =
        malloc(sizeof(Value) * result->row_count);

    if (rows == NULL)
    {
        return value_null();
    }

    for (int r = 0; r < result->row_count; r++)
    {
        DBRow *db_row =
            &result->rows[r];

        Value *cells =
            malloc(sizeof(Value) * db_row->cell_count);

        if (cells == NULL)
        {
            for (int i = 0; i < r; i++)
            {
                value_free(&rows[i]);
            }

            free(rows);

            return value_null();
        }

        for (int c = 0; c < db_row->cell_count; c++)
        {
          if (db_row->cells[c].is_null)
{
    cells[c] = value_null();
}
else
{
    cells[c] =
        value_string(
            db_row->cells[c].text);
}

        }

        rows[r] =
            value_list(
                cells,
                db_row->cell_count);
    }

    return value_list(
        rows,
        result->row_count);
}
