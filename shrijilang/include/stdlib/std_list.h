#ifndef SHRIJI_STD_LIST_H
#define SHRIJI_STD_LIST_H

#include "value.h"
#include "ast.h"
#include "env.h"
#include "runtime.h"

Value std_list_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
