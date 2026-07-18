#include <stdio.h>

#include "../include/db.h"
#include "../include/db_statement.h"
#include "../include/db_bind.h"
#include "../include/db_step.h"
#include "../include/db_execute.h"

int main(void)
{
    sqlite3 *db = db_open("sqlite_prepare_test.db");

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
    "id INTEGER PRIMARY KEY,"
    "name TEXT,"
    "age INTEGER"
    ");");

    const char *sql =
        "INSERT INTO users(name, age) "
        "VALUES(?, ?);";

    sqlite3_stmt *stmt =
        db_prepare(
            db,
            sql);

    if (stmt == NULL)
    {
        db_close(db);
        return 1;
    }

    if (db_bind_text(
            stmt,
            1,
            "Hukum") != SQLITE_OK)
    {
        printf("Bind Text Failed\n");

        db_finalize(stmt);

        db_close(db);

        return 1;
    }

    if (db_bind_int(
            stmt,
            2,
            30) != SQLITE_OK)
    {
        printf("Bind Int Failed\n");

        db_finalize(stmt);

        db_close(db);

        return 1;
    }

    int rc = db_step(stmt);

    if (rc != SQLITE_DONE)
    {
        printf("Step Failed\n");

        db_finalize(stmt);

        db_close(db);

        return 1;
    }

    printf("Prepared Statement Executed Successfully\n");

    db_finalize(stmt);

    db_close(db);

    printf("Database Closed Successfully\n");

    return 0;
}
