#ifndef STD_JSON_H
#define STD_JSON_H

#include "ast.h"
#include "env.h"
#include "runtime.h"
#include "value.h"

Value std_json_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
