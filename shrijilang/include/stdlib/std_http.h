#ifndef SHRIJI_STD_HTTP_H
#define SHRIJI_STD_HTTP_H

#include "value.h"
#include "ast.h"
#include "env.h"
#include "runtime.h"

Value std_http_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
