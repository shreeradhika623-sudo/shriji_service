#ifndef STD_RANDOM_H
#define STD_RANDOM_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_random_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
