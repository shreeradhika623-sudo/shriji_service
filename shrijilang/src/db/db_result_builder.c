#include <stdlib.h>
#include <string.h>

#include "db_result_builder.h"


/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT BUILDER
 * ------------------------------------------------------------
 * Responsibility:
 *      Build DBResult objects.
 *
 * Future:
 *      Allocate rows.
 *      Allocate cells.
 *      Copy text.
 * ------------------------------------------------------------
 */

int db_result_add_row(DBResult *result)
{
    DBRow *rows = realloc(
        result->rows,
        sizeof(DBRow) * (result->row_count + 1));

    if (rows == NULL)
    {
        return -1;
    }

    result->rows = rows;

    DBRow *new_row =
        &result->rows[result->row_count];

    new_row->cell_count = 0;
    new_row->cells = NULL;

    result->row_count++;

    return 0;
}

//----------------------------------------------------------------------------


int db_result_add_cell(
    DBResult *result,
    int row,
    const char *text)
{
    DBRow *current_row =
        &result->rows[row];

    DBCell *cells = realloc(
        current_row->cells,
        sizeof(DBCell) * (current_row->cell_count + 1));

    if (cells == NULL)
    {
        return -1;
    }

    current_row->cells = cells;

    DBCell *new_cell =
        &current_row->cells[current_row->cell_count];

    new_cell->is_null = 0;

    size_t length = strlen(text);

    new_cell->text = malloc(length + 1);

    if (new_cell->text == NULL)
    {
        return -1;
    }

    strcpy(
        new_cell->text,
        text);

    current_row->cell_count++;

    return 0;
}

int db_result_add_null_cell(
    DBResult *result,
    int row)
{
    DBRow *current_row =
        &result->rows[row];

    DBCell *cells = realloc(
        current_row->cells,
        sizeof(DBCell) * (current_row->cell_count + 1));

    if (cells == NULL)
    {
        return -1;
    }

    current_row->cells = cells;

    DBCell *new_cell =
        &current_row->cells[current_row->cell_count];

    new_cell->text = NULL;
    new_cell->is_null = 1;

    current_row->cell_count++;

    return 0;
}
/* ───────────────────────────────────────────── */

int db_result_set_column_name(
    DBResult *result,
    int column,
    const char *name)
{
    if (result == NULL)
    {
        return -1;
    }

    if (column < 0 || column >= result->column_count)
    {
        return -1;
    }

    if (result->column_names == NULL)
    {
        result->column_names = calloc(
            result->column_count,
            sizeof(char *));

        if (result->column_names == NULL)
        {
            return -1;
        }
    }

    size_t length = strlen(name);

    result->column_names[column] =
        malloc(length + 1);

    if (result->column_names[column] == NULL)
    {
        return -1;
    }

    strcpy(
        result->column_names[column],
        name);

    return 0;
}
