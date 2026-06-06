#ifndef SHRIJI_STD_MATH_H
#define SHRIJI_STD_MATH_H

#include "value.h"
#include "ast.h"
#include "env.h"
#include "runtime.h"

Value std_math_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
