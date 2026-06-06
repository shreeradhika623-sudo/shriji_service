#ifndef STD_TIME_H
#define STD_TIME_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_time_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
