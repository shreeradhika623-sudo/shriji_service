#include <stdio.h>

#include "../include/db.h"
#include "../include/db_execute.h"
#include "../include/db_query.h"
#include "../include/db_result.h"
#include "../include/db_query_callback.h"
#include "../include/db_result_print.h"

int main(void)
{
    sqlite3 *db = db_open("shop.db");

    if (db == NULL)
    {
        return 1;
    }

    char *errmsg = NULL;
    int rc;

    printf("Database Opened Successfully\n");

    /* --------------------------------------------------------- */
    /* CREATE TABLE                                               */
    /* --------------------------------------------------------- */

    const char *create_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "age INTEGER"
        ");";

    rc = db_execute(
            db,
            create_sql);

    if (rc != SQLITE_OK)
    {
        db_close(db);
        return 1;
    }

    printf("Table Created Successfully\n");

    /* --------------------------------------------------------- */
    /* INSERT                                                     */
    /* --------------------------------------------------------- */

    const char *insert_sql =
        "INSERT INTO users(name, age) "
        "VALUES('Hukum', 30);";

    rc = db_execute(
            db,
            insert_sql);

    if (rc != SQLITE_OK)
    {
        db_close(db);
        return 1;
    }

    printf("Data Inserted Successfully\n");

    /* --------------------------------------------------------- */
    /* SELECT                                                     */
    /* --------------------------------------------------------- */

    const char *select_sql =
        "SELECT * FROM users;";

    DBResult *result = db_result_create();

  if (result == NULL)
  {
     db_close(db);
     return 1;
  }

  rc = db_query(
       db,
       select_sql,
       db_query_callback,
       result);

    db_result_print(result);

    if (rc != SQLITE_OK)
{
    db_result_free(result);

    db_close(db);

    return 1;
}


/* --------------------------------------------------------- */
/* CLEANUP                                                    */
/* --------------------------------------------------------- */

    db_result_free(result);

/* --------------------------------------------------------- */
/* CLOSE                                                      */
/* --------------------------------------------------------- */

db_close(db);

printf("Database Closed Successfully\n");

    return 0;
}
