#include <stdlib.h>

#include "db_query_statement.h"
#include "db_result_builder.h"
#include "db_statement.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY STATEMENT
 * ------------------------------------------------------------
 * Responsibility:
 *      Execute SELECT queries using prepared statements.
 * ------------------------------------------------------------
 */

DBResult *db_query_statement(
    sqlite3 *db,
    const char *sql)
{
    sqlite3_stmt *stmt =
        db_prepare(
            db,
            sql);

    if (stmt == NULL)
    {
        return NULL;
    }

    DBResult *result =
        db_result_create();

    if (result == NULL)
    {
        db_finalize(stmt);

        return NULL;
    }

    result->column_count =
        sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        if (db_result_add_row(result) != 0)
        {
            db_finalize(stmt);

            db_result_free(result);

            return NULL;
        }

        int row =
            result->row_count - 1;

        for (int c = 0;
             c < result->column_count;
             c++)
        {

                int column_type =
                sqlite3_column_type(
                    stmt,
                    c);

            int add_result;

            if (column_type == SQLITE_NULL)
            {
                add_result =
                    db_result_add_null_cell(
                        result,
                        row);
            }
            else
            {
                const unsigned char *value =
                    sqlite3_column_text(
                        stmt,
                        c);

                add_result =
                    db_result_add_cell(
                        result,
                        row,
                        (const char *)value);
            }

            if (add_result != 0)


            {
                db_finalize(stmt);

                db_result_free(result);

                return NULL;
            }
        }
    }

    db_finalize(stmt);

    return result;
}
