#include "runtime_db.h"

#include "db.h"
#include "db_execute.h"
#include "db_query_statement.h"

#include "db_statement.h"
#include "db_bind.h"
#include "db_step.h"
#include "db_reset.h"

/*
 * ------------------------------------------------------------
 * SHRIJI RUNTIME DATABASE API
 * ------------------------------------------------------------
 * Responsibility:
 *      Bridge Runtime and Database layer.
 * ------------------------------------------------------------
 */

sqlite3 *runtime_db_open(
    ShrijiRuntime *rt,
    const char *path)
{
    (void)rt;

    return db_open(path);
}

void runtime_db_close(
    ShrijiRuntime *rt,
    sqlite3 *db)
{
    (void)rt;

    db_close(db);
}

int runtime_db_execute(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql)
{
    (void)rt;

    return db_execute(
        db,
        sql);
}

DBResult *runtime_db_query(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql)
{
    (void)rt;

    return db_query_statement(
        db,
        sql);
}

//----------------------------------------------------------------

sqlite3_stmt *runtime_db_prepare(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql)
{
    (void)rt;

    return db_prepare(
        db,
        sql);
}

int runtime_db_bind_int(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    int value)
{
    (void)rt;

    return db_bind_int(
        stmt,
        index,
        value);
}

int runtime_db_bind_double(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    double value)
{
    (void)rt;

    return db_bind_double(
        stmt,
        index,
        value);
}

int runtime_db_bind_text(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    const char *text)
{
    (void)rt;

    return db_bind_text(
        stmt,
        index,
        text);
}

int runtime_db_bind_null(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index)
{
    (void)rt;

    return db_bind_null(
        stmt,
        index);
}

int runtime_db_step(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt)
{
    (void)rt;

    return db_step(stmt);
}

int runtime_db_reset(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt)
{
    (void)rt;

    return db_reset(stmt);
}

void runtime_db_finalize(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt)
{
    (void)rt;

    db_finalize(stmt);
}
