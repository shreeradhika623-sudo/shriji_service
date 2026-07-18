#include <stdio.h>

#include "../include/db.h"
#include "../include/db_query_statement.h"
#include "../include/db_result.h"
#include "../include/db_result_print.h"
#include "../include/db_execute.h"

int main(void)
{
    sqlite3 *db =
        db_open("sqlite_prepare_select_test.db");

    if (db == NULL)
    {
        return 1;
    }

    if (db_execute(
        db,
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY,"
        "name TEXT,"
        "age INTEGER);")
    != SQLITE_OK)
{
    db_close(db);
    return 1;
}

if (db_execute(
        db,
        "DELETE FROM users;")
    != SQLITE_OK)
{
    db_close(db);
    return 1;
}

if (db_execute(
        db,
        "INSERT INTO users(name, age) "
        "VALUES('Select_Test_User', 33);")
    != SQLITE_OK)
{
    db_close(db);
    return 1;
}


    DBResult *result =
        db_query_statement(
            db,
            "SELECT * FROM users;");

    if (result == NULL)
    {
        db_close(db);

        return 1;
    }

    db_result_print(result);

    db_result_free(result);

    db_close(db);

    return 0;
}
