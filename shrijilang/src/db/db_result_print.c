#include <stdio.h>

#include "db_result_print.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT PRINTER
 * ------------------------------------------------------------
 * Responsibility:
 *      Print DBResult.
 * ------------------------------------------------------------
 */

void db_result_print(
    const DBResult *result)
{
    if (result == NULL)
    {
        return;
    }

    printf("\n");

    printf("Rows    : %d\n",
           result->row_count);

    printf("Columns : %d\n",
           result->column_count);

    printf("\n");

    for (int r = 0; r < result->row_count; r++)
    {
        printf("Row %d\n", r + 1);

        printf("----------------------\n");

        for (int c = 0; c < result->rows[r].cell_count; c++)
        {
            printf("%s\n",
                   result->rows[r].cells[c].text);
        }

        printf("\n");
    }
}
