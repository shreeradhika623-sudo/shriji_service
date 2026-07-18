#ifndef STD_DB_CONNECTION_H
#define STD_DB_CONNECTION_H

#include "runtime.h"
#include "value.h"
#include "ast.h"
#include "env.h"

Value std_db_connection_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled);

#endif
