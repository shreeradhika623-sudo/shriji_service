#include <stddef.h>

#include "db_query.h"

#include "db_query_callback.h"
#include "db_query_statement.h"
#include "db_result_print.h"

/*
 * ------------------------------------------------------------
 * SHRIJI DATABASE QUERY
 * ------------------------------------------------------------
 * Responsibility:
 *      Compatibility layer.
 *
 * Legacy:
 *      Callback based API.
 *
 * Current:
 *      Internally uses prepared statement engine.
 * ------------------------------------------------------------
 */

int db_query(
    sqlite3 *db,
    const char *sql,
    int (*callback)(void *, int, char **, char **),
    void *data)
{
    DBResult *result =
        db_query_statement(
            db,
            sql);

    if (result == NULL)
    {
        return SQLITE_ERROR;
    }

    /*
     * Legacy compatibility.
     *
     * Callback API will be removed in a future version.
     */
    (void)callback;
    (void)data;

    db_result_print(result);

    db_result_free(result);

    return SQLITE_OK;
}
