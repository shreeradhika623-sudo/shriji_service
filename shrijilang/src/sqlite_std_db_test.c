#include <stdio.h>

#include "runtime.h"
#include "std_db.h"
#include "value.h"

int main(void)
{
    ShrijiRuntime rt;

    runtime_init(&rt);

    Value db =
        std_sqlite_open(
            &rt,
            "sqlite_std_db_test.db");

    if (db.type != VAL_DATABASE)
    {
        printf("Open Failed\n");
        return 1;
    }

    printf("Database Opened\n");

    Value ok;

ok = std_sqlite_execute(
    &rt,
    db,
    "DROP TABLE IF EXISTS users;");

value_free(&ok);

ok = std_sqlite_execute(
    &rt,
    db,
    "CREATE TABLE users("
    "id INTEGER,"
    "name TEXT);");

value_free(&ok);

ok = std_sqlite_execute(
    &rt,
    db,
    "INSERT INTO users VALUES(1,'Radha');");

value_free(&ok);

ok = std_sqlite_execute(
    &rt,
    db,
    "INSERT INTO users VALUES(2,'Krishna');");

value_free(&ok);

    Value rows =
        std_sqlite_query(
            &rt,
            db,
            "SELECT * FROM users;");

    printf("\nQuery Result:\n");

    value_print(rows);

    printf("\n");

    value_free(&rows);

    std_sqlite_close(
        &rt,
        db);

    printf("\nDatabase Closed\n");

    return 0;
}
