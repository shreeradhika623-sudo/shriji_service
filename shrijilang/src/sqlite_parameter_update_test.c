#include <stdio.h>

#include "../include/db.h"
#include "../include/db_statement.h"
#include "../include/db_bind.h"
#include "../include/db_execute_statement.h"
#include "../include/db_execute.h"

int main(void)
{
    sqlite3 *db =
        db_open("sqlite_parameter_update_test.db");

    if (db == NULL)
    {
        return 1;
    }

    printf("Database Opened Successfully\n");

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
        "VALUES('Prepared_User', 40);")
    != SQLITE_OK)
{
    db_close(db);
    return 1;
}


    sqlite3_stmt *stmt =
        db_prepare(
            db,
            "UPDATE users SET age = ? WHERE name = ?;");

    if (stmt == NULL)
    {
        db_close(db);
        return 1;
    }

    if (db_bind_int(
            stmt,
            1,
            45) != SQLITE_OK)
    {
        db_finalize(stmt);
        db_close(db);
        return 1;
    }

    if (db_bind_text(
            stmt,
            2,
            "Prepared_User") != SQLITE_OK)
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

    printf("Prepared UPDATE Successful\n");

    db_finalize(stmt);

    db_close(db);

    printf("Database Closed Successfully\n");

    return 0;
}
