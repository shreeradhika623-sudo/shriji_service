#include <stdlib.h>

#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT
 * ------------------------------------------------------------
 * Responsibility:
 *     Create and destroy database result objects.
 * ------------------------------------------------------------
 */

DBResult *db_result_create(void)
{
    DBResult *result = calloc(
        1,
        sizeof(DBResult));

    return result;
}

void db_result_free(DBResult *result)
{
    if (result == NULL)
    {
        return;
    }

    for (int r = 0; r < result->row_count; r++)
    {
        DBRow *row = &result->rows[r];

        for (int c = 0; c < result->column_count; c++)
        {
            free(row->cells[c].text);
        }

        free(row->cells);
    }

    free(result->rows);

    free(result);
}
