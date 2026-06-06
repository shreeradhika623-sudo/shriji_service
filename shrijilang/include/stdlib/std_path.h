#ifndef STD_PATH_H
#define STD_PATH_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_path_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
