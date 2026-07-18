#include <stdio.h>

#include "../include/db.h"
#include "../include/db_execute.h"
#include "../include/db_transaction.h"

int main(void)
{
    sqlite3 *db = db_open("sqlite_commit_test.db");

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

    if (db_begin(db) != SQLITE_OK)
    {
        db_close(db);
        return 1;
    }

    printf("Transaction Started\n");

    if (db_execute(
            db,
            "INSERT INTO users(name, age) VALUES('Commit_User', 50);")
        != SQLITE_OK)
    {
        db_rollback(db);
        db_close(db);
        return 1;
    }

    printf("Insert Success\n");

    if (db_commit(db) != SQLITE_OK)
    {
        db_close(db);
        return 1;
    }

    printf("Transaction Committed\n");

    db_close(db);

    printf("Database Closed Successfully\n");

    return 0;
}
