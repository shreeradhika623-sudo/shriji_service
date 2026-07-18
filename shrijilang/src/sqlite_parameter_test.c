#include <stdio.h>
#include "../include/db.h"
#include "../include/db_statement.h"
#include "../include/db_bind.h"
#include "../include/db_execute_statement.h"
#include "../include/db_execute.h"
int main(void)
{
    sqlite3 *db =
        db_open("sqlite_parameter_test.db");

    if (db == NULL)
    {
        return 1;
    }

        printf("Database Opened Successfully\n");

db_execute(
    db,
    "DROP TABLE IF EXISTS users;");

db_execute(
    db,
    "CREATE TABLE users("
    "id INTEGER PRIMARY KEY, "
    "name TEXT, "
    "age INTEGER);");

sqlite3_stmt *stmt =
    db_prepare(
        db,
        "INSERT INTO users(name, age) VALUES(?, ?);");

    if (stmt == NULL)
    {
        db_close(db);
        return 1;
    }

    if (db_bind_text(
            stmt,
            1,
            "Prepared_User") != SQLITE_OK)
    {
        db_finalize(stmt);
        db_close(db);
        return 1;
    }

    if (db_bind_int(
            stmt,
            2,
            40) != SQLITE_OK)
    {
        db_finalize(stmt);
        db_close(db);
        return 1;
    }

    if (db_execute_statement(stmt) != SQLITE_OK)
    {
        db_finalize(stmt);
        db_close(db);
        return 1;
    }

    printf("Prepared INSERT Successful\n");

    db_finalize(stmt);

    db_close(db);

    printf("Database Closed Successfully\n");

    return 0;
}
