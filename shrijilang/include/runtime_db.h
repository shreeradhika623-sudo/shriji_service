#ifndef RUNTIME_DB_H
#define RUNTIME_DB_H

#include "runtime.h"
#include "db.h"
#include "db_result.h"

/*
 * ------------------------------------------------------------
 * SHRIJI RUNTIME DATABASE API
 * ------------------------------------------------------------
 * Responsibility:
 *      Runtime-facing database operations.
 *
 * Never:
 *      Parse SQL.
 *      Know SQLite internals.
 * ------------------------------------------------------------
 */

    sqlite3 *runtime_db_open(
    ShrijiRuntime *rt,
    const char *path);

void runtime_db_close(
    ShrijiRuntime *rt,
    sqlite3 *db);

int runtime_db_execute(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql);

DBResult *runtime_db_query(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql);

    sqlite3_stmt *runtime_db_prepare(
    ShrijiRuntime *rt,
    sqlite3 *db,
    const char *sql);

int runtime_db_bind_int(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    int value);

int runtime_db_bind_double(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    double value);

int runtime_db_bind_text(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index,
    const char *text);

int runtime_db_bind_null(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt,
    int index);

int runtime_db_step(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt);

int runtime_db_reset(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt);

void runtime_db_finalize(
    ShrijiRuntime *rt,
    sqlite3_stmt *stmt);

#endif
