#ifndef STD_STRING_H
#define STD_STRING_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_string_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
