#include "stdlib/std_random.h"
#include "interpreter.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static int seeded = 0;

static void ensure_seeded(void)
{
    if (!seeded) {

        srand((unsigned)time(NULL));

        seeded = 1;
    }
}

Value std_random_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    (void)env;
    (void)rt;

    *handled = 0;

    /* RANDOM */

    if (
        strcmp(node->function_name, "random") == 0 ||
        strcmp(node->function_name, "koi_bhi") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 0) {

shriji_arg_count_error(
    "random",
    0,
    node->arg_count
);

            return value_null();
        }

        ensure_seeded();

        double r =
            (double)rand() /
            (double)RAND_MAX;

        return value_number(r);
    }

    /* RANDINT */

    if (
        strcmp(node->function_name, "randint") == 0 ||
        strcmp(node->function_name, "koi_bhi_ank") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 2) {

shriji_arg_count_error(
    "randint",
    2,
    node->arg_count
);

            return value_null();
        }

        Value minv = eval(node->args[0], env, rt);
        Value maxv = eval(node->args[1], env, rt);

        long long min = 0;
        long long max = 0;

        if (minv.type == VAL_INT)
            min = minv.integer;
        else {
            value_free(&minv);
            value_free(&maxv);

shriji_arg_type_error(
    "randint",
    "number"
);

            return value_null();
        }

        if (maxv.type == VAL_INT)
            max = maxv.integer;
        else {
            value_free(&minv);
            value_free(&maxv);

shriji_arg_type_error(
    "randint",
    "number"
);
            return value_null();
        }

        if (min > max) {

            value_free(&minv);
            value_free(&maxv);

            shriji_error(
                E_PARSE_02,
                "randint",
                "pehla ank chhota hona chahiye",
                "example: randint(1, 10)"
            );

            return value_null();
        }

        ensure_seeded();

        long long result =
            min +
            (rand() % (max - min + 1));

        value_free(&minv);
        value_free(&maxv);

        return value_int(result);
    }

    return value_null();
}
