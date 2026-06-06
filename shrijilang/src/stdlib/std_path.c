#include "stdlib/std_path.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <sys/stat.h>

Value std_path_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    (void)env;
    (void)rt;

    *handled = 0;

    /* EXISTS */

    if (
        strcmp(node->function_name, "exists") == 0 ||
        strcmp(node->function_name, "hai") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "exists",
                "1 cheez deni hogi",
                "example: exists(\"file.txt\")"
            );

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "exists",
                "text dena hoga",
                "example: exists(\"file.txt\")"
            );

            return value_null();
        }

        struct stat st;

        int ok =
            stat(pathv.string, &st) == 0;

        value_free(&pathv);

        return value_bool(ok);
    }

    /* IS_FILE */

    if (
        strcmp(node->function_name, "is_file") == 0 ||
        strcmp(node->function_name, "file_hai") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "is_file",
                "1 cheez deni hogi",
                "example: is_file(\"photo.jpg\")"
            );

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "is_file",
                "text dena hoga",
                "example: is_file(\"photo.jpg\")"
            );

            return value_null();
        }

        struct stat st;

        int ok =
            stat(pathv.string, &st) == 0 &&
            S_ISREG(st.st_mode);

        value_free(&pathv);

        return value_bool(ok);
    }

    /* IS_DIR */

    if (
        strcmp(node->function_name, "is_dir") == 0 ||
        strcmp(node->function_name, "folder_hai") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "is_dir",
                "1 cheez deni hogi",
                "example: is_dir(\"docs\")"
            );

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "is_dir",
                "text dena hoga",
                "example: is_dir(\"docs\")"
            );

            return value_null();
        }

        struct stat st;

        int ok =
            stat(pathv.string, &st) == 0 &&
            S_ISDIR(st.st_mode);

        value_free(&pathv);

        return value_bool(ok);
    }


    /* BASENAME */

    if (
        strcmp(node->function_name, "basename") == 0 ||
        strcmp(node->function_name, "naam") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "basename",
                "1 cheez deni hogi",
                "example: naam(\"photo.jpg\")"
            );

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "basename",
                "text dena hoga",
                "example: naam(\"photo.jpg\")"
            );

            return value_null();
        }

        const char *name = strrchr(pathv.string, '/');

        if (name)
            name++;
        else
            name = pathv.string;

        Value out = value_string(name);

        value_free(&pathv);

        return out;
    }

    /* EXTENSION */

    if (
        strcmp(node->function_name, "extension") == 0 ||
        strcmp(node->function_name, "vistar") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "extension",
                "1 cheez deni hogi",
                "example: vistar(\"photo.jpg\")"
            );

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (
            pathv.type != VAL_STRING ||
            !pathv.string
        ) {
            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "extension",
                "text dena hoga",
                "example: vistar(\"photo.jpg\")"
            );

            return value_null();
        }

        const char *dot = strrchr(pathv.string, '.');

        Value out;

        if (
            !dot ||
            dot == pathv.string ||
            *(dot + 1) == '\0'
        ) {
            out = value_string("");
        }
        else {
            out = value_string(dot + 1);
        }

        value_free(&pathv);

        return out;
    }

    return value_null();
}
