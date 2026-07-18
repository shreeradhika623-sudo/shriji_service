#ifndef STD_DB_H
#define STD_DB_H

#include "runtime.h"
#include "value.h"
#include "ast.h"
#include "env.h"
#include "std_db_step.h"

/*
 * ------------------------------------------------------------
 * SHRIJI STANDARD DATABASE LIBRARY
 * ------------------------------------------------------------
 */

Value std_sqlite_open(
    ShrijiRuntime *rt,
    const char *path);

Value std_sqlite_close(
    ShrijiRuntime *rt,
    Value db);

Value std_sqlite_execute(
    ShrijiRuntime *rt,
    Value db,
    const char *sql);

Value std_sqlite_query(
    ShrijiRuntime *rt,
    Value db,
    const char *sql);

Value std_sqlite_prepare(
    ShrijiRuntime *rt,
    Value db,
    const char *sql);

 Value std_sqlite_finalize(
    ShrijiRuntime *rt,
    Value stmt);

Value std_sqlite_bind_int(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    int value);

Value std_sqlite_bind_double(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    double value);

Value std_sqlite_bind_text(
    ShrijiRuntime *rt,
    Value stmt,
    int index,
    const char *text);

Value std_sqlite_bind_null(
    ShrijiRuntime *rt,
    Value stmt,
    int index);

Value std_sqlite_step(
    ShrijiRuntime *rt,
    Value stmt);

Value std_sqlite_reset(
    ShrijiRuntime *rt,
    Value stmt);

Value std_db_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled);

void std_db_register(
    ShrijiRuntime *rt);

#endif
