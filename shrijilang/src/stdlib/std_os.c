#include "stdlib/std_os.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define mkdir(path, mode) _mkdir(path)
#define rmdir _rmdir
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

Value std_os_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /* MKDIR */

    if (
        strcmp(node->function_name, "mkdir") == 0 ||
        strcmp(node->function_name, "folder_banao") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

shriji_arg_count_error(
    "mkdir",
    1,
    node->arg_count
);

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

shriji_arg_type_error(
    "mkdir",
    "string"
);

            return value_null();
        }

#ifdef _WIN32
        int result = mkdir(pathv.string, 0);
#else
        int result = mkdir(pathv.string, 0755);
#endif

        if (result != 0) {

#ifdef _WIN32
            if (_access(pathv.string, 0) == 0)
#else
            if (access(pathv.string, F_OK) == 0)
#endif
            {
                value_free(&pathv);
                return value_bool(1);
            }
        }

        value_free(&pathv);

        return value_bool(result == 0);
    }

    /* RMDIR */

    if (
        strcmp(node->function_name, "rmdir") == 0 ||
        strcmp(node->function_name, "folder_hatao") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

shriji_arg_count_error(
    "rmdir",
    1,
    node->arg_count
);

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

shriji_arg_type_error(
    "rmdir",
    "string"
);

            return value_null();
        }

        int result = rmdir(pathv.string);

        value_free(&pathv);

        return value_bool(result == 0);
    }

    /* CWD */

    if (
        strcmp(node->function_name, "cwd") == 0 ||
        strcmp(node->function_name, "yahi") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 0) {

shriji_arg_count_error(
    "cwd",
    0,
    node->arg_count
);

            return value_null();
        }

        char buf[4096];

        if (!getcwd(buf, sizeof(buf))) {
            return value_null();
        }

        return value_string(buf);
    }

    /* SYSTEM */

    if (
        strcmp(node->function_name, "system") == 0 ||
        strcmp(node->function_name, "chalao") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

shriji_arg_count_error(
    "system",
    1,
    node->arg_count
);

            return value_null();
        }

        Value cmdv = eval(node->args[0], env, rt);

        if (
            cmdv.type != VAL_STRING ||
            !cmdv.string
        ) {
            value_free(&cmdv);

shriji_arg_type_error(
    "system",
    "string"
);

            return value_null();
        }

        int result = system(cmdv.string);

        value_free(&cmdv);

        return value_int(result);
    }

    return value_null();
}
