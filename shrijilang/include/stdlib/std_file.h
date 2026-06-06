#ifndef SHRIJI_STD_FILE_H
#define SHRIJI_STD_FILE_H

#include "value.h"
#include "ast.h"
#include "env.h"
#include "runtime.h"

Value std_file_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
);

#endif
