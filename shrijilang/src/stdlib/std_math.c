#include "stdlib/std_math.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <math.h>

Value std_math_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /* FLOOR */

    if (
        strcmp(node->function_name, "floor") == 0 ||
        strcmp(node->function_name, "purna") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1)
            return value_null();

        Value v = eval(node->args[0], env, rt);

        double n;

        if (v.type == VAL_INT)
            n = v.integer;
        else if (v.type == VAL_NUMBER)
            n = v.number;
        else {
            value_free(&v);
            return value_null();
        }

        value_free(&v);

        return value_int((int)floor(n));
    }

    /* CEIL */

    if (
        strcmp(node->function_name, "ceil") == 0 ||
        strcmp(node->function_name, "upar") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "ceil",
                "1 argument required",
                "use: ceil(x)"
            );

            return value_null();
        }

        Value v = eval(node->args[0], env, rt);

        double n = 0;

        if (v.type == VAL_INT)
            n = v.integer;

        else if (v.type == VAL_NUMBER)
            n = v.number;

        else {

            value_free(&v);

            shriji_error(
                E_PARSE_02,
                "ceil",
                "number required",
                "use numeric value"
            );

            return value_null();
        }

        value_free(&v);

        return value_int((int)ceil(n));
    }

    /* ROUND */

    if (
        strcmp(node->function_name, "round") == 0 ||
        strcmp(node->function_name, "gol") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "round",
                "1 argument required",
                "use: round(x)"
            );

            return value_null();
        }

        Value v = eval(node->args[0], env, rt);

        double n = 0;

        if (v.type == VAL_INT)
            n = v.integer;

        else if (v.type == VAL_NUMBER)
            n = v.number;

        else {

            value_free(&v);

            shriji_error(
                E_PARSE_02,
                "round",
                "number required",
                "use numeric value"
            );

            return value_null();
        }

        value_free(&v);

        return value_int((int)round(n));
    }

    /* ABS */

    if (
        strcmp(node->function_name, "abs") == 0 ||
        strcmp(node->function_name, "nirpeksh") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "abs",
                "1 argument required",
                "use: abs(x)"
            );

            return value_null();
        }

        Value v = eval(node->args[0], env, rt);

        double n = 0;

        if (v.type == VAL_INT)
            n = v.integer;

        else if (v.type == VAL_NUMBER)
            n = v.number;

        else {

            value_free(&v);

            shriji_error(
                E_PARSE_02,
                "abs",
                "number required",
                "use numeric value"
            );

            return value_null();
        }

        if (v.type == VAL_INT) {

            value_free(&v);

            return value_int((int)fabs(n));
        }

        value_free(&v);

        return value_number(fabs(n));
    }

    return value_null();
}
