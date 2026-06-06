#ifndef STD_OS_H
#define STD_OS_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_os_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
