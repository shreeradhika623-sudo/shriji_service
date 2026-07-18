#include <stddef.h>

#include "db_query_callback.h"
#include "db_result_builder.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY CALLBACK
 * ------------------------------------------------------------
 * Responsibility:
 *      Receive SQLite rows and build DBResult.
 *
 * Future:
 *      Replace sqlite_test callback.
 * ------------------------------------------------------------
 */

int db_query_callback(
    void *data,
    int columns,
    char **values,
    char **names)
{


    if (data == NULL)
  {
    return 1;
   }

    DBResult *result = data;

    if (db_result_add_row(result) != 0)
    {
        return 1;
    }

    int row = result->row_count - 1;

    for (int i = 0; i < columns; i++)
    {

        if (values[i] == NULL)
        {
            if (db_result_add_null_cell(
                    result,
                    row) != 0)
            {
                return 1;
            }
        }
        else
        {
            if (db_result_add_cell(
                    result,
                    row,
                    values[i]) != 0)
            {
                return 1;
            }
        }

    }

    if (result->column_count == 0)
{
    result->column_count = columns;

    for (int i = 0; i < columns; i++)
    {
        if (db_result_set_column_name(
                result,
                i,
                names[i]) != 0)
        {
            return 1;
        }
    }
}

    result->column_count = columns;

    return 0;
}
