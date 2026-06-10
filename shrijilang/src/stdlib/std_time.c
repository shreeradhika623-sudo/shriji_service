#include "stdlib/std_time.h"
#include "interpreter.h"
#include "error.h"

#include <time.h>
#include <string.h>

Value std_time_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    (void)env;
    (void)rt;

    *handled = 0;

    if (
        strcmp(node->function_name, "timestamp") == 0 ||
        strcmp(node->function_name, "samay_mudra") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 0) {

shriji_arg_count_error(
    "timestamp",
    0,
    node->arg_count
);

            return value_null();
        }

        time_t now = time(NULL);

        return value_int((long long)now);
    }


    /* DATE */

    if (
        strcmp(node->function_name, "date") == 0 ||
        strcmp(node->function_name, "dinank") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 0) {

shriji_arg_count_error(
    "date",
    0,
    node->arg_count
);

            return value_null();
        }

        time_t now = time(NULL);

        struct tm *tm_info = localtime(&now);

        if (!tm_info) {
            return value_null();
        }

        char buf[32];

        strftime(
            buf,
            sizeof(buf),
            "%Y-%m-%d",
            tm_info
        );

        return value_string(buf);
    }

    /* TIME */

    if (
        strcmp(node->function_name, "time") == 0 ||
        strcmp(node->function_name, "samay") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 0) {

shriji_arg_count_error(
    "time",
    0,
    node->arg_count
);

            return value_null();
        }

        time_t now = time(NULL);

        struct tm *tm_info = localtime(&now);

        if (!tm_info) {
            return value_null();
        }

        char buf[32];

        strftime(
            buf,
            sizeof(buf),
            "%H:%M:%S",
            tm_info
        );

        return value_string(buf);
    }

      return value_null();
}
