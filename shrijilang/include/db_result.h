#ifndef DB_RESULT_H
#define DB_RESULT_H

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE RESULT
 * ------------------------------------------------------------
 * Responsibility:
 *     Store rows returned by SELECT queries.
 * ------------------------------------------------------------
 */

typedef struct
{
    char *text;

    int is_null;

} DBCell;

typedef struct
{
    int cell_count;

    DBCell *cells;

} DBRow;

/*
 * ------------------------------------------------------------
 * MEMORY OWNERSHIP
 * ------------------------------------------------------------
 *
 * DBResult owns:
 *      column_names[]
 *      DBRow[]
 *
 * DBRow owns:
 *      DBCell[]
 *
 * DBCell owns:
 *      text
 *
 * Destroying DBResult must free the entire tree.
 * ------------------------------------------------------------
 */

typedef struct
{
    int row_count;

    int column_count;

    char **column_names;

    DBRow *rows;

} DBResult;

DBResult *db_result_create(void);

void db_result_free(DBResult *result);

#endif
