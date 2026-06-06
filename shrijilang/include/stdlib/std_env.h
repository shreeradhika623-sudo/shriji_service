#ifndef STD_ENV_H
#define STD_ENV_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_env_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
