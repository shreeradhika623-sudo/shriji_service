#include "stdlib/std_json.h"
#include "interpreter.h"
#include "error.h"
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

static void json_append(
    char **buf,
    size_t *len,
    size_t *cap,
    const char *text
);

static void json_append_char(
    char **buf,
    size_t *len,
    size_t *cap,
    char c
);

static void json_stringify_value(
    Value v,
    char **buf,
    size_t *len,
    size_t *cap
);

static void json_append(
    char **buf,
    size_t *len,
    size_t *cap,
    const char *text
)
{
    if (!text)
        return;

    size_t add = strlen(text);

    while ((*len + add + 1) > *cap) {

        *cap *= 2;

        char *tmp =
            realloc(*buf, *cap);

        if (!tmp)
            return;

        *buf = tmp;
    }

    memcpy(
        *buf + *len,
        text,
        add
    );

    *len += add;

    (*buf)[*len] = '\0';
}

static void json_append_char(
    char **buf,
    size_t *len,
    size_t *cap,
    char c
)
{
    while ((*len + 2) > *cap) {

        *cap *= 2;

        char *tmp =
            realloc(*buf, *cap);

        if (!tmp)
            return;

        *buf = tmp;
    }

    (*buf)[(*len)++] = c;
    (*buf)[*len] = '\0';
}

static void json_stringify_value(
    Value v,
    char **buf,
    size_t *len,
    size_t *cap
)
{
    char tmp[128];

    switch (v.type)
    {
        case VAL_NULL:

            json_append(
                buf,
                len,
                cap,
                "null"
            );

            return;

        case VAL_BOOL:

            json_append(
                buf,
                len,
                cap,
                v.boolean
                    ? "true"
                    : "false"
            );

            return;

        case VAL_INT:

            snprintf(
                tmp,
                sizeof(tmp),
                "%lld",
                v.integer
            );

            json_append(
                buf,
                len,
                cap,
                tmp
            );

            return;

        case VAL_NUMBER:

            snprintf(
                tmp,
                sizeof(tmp),
                "%g",
                v.number
            );

            json_append(
                buf,
                len,
                cap,
                tmp
            );

            return;

        case VAL_STRING:

            json_append_char(
                buf,
                len,
                cap,
                '"'
            );

            json_append(
                buf,
                len,
                cap,
                v.string
                    ? v.string
                    : ""
            );

            json_append_char(
                buf,
                len,
                cap,
                '"'
            );

            return;

 case VAL_LIST:
{
    json_append_char(
        buf,
        len,
        cap,
        '['
    );

    for (int i = 0; i < v.count; i++)
    {
        if (i > 0)
        {
            json_append_char(
                buf,
                len,
                cap,
                ','
            );
        }

        json_stringify_value(
            v.items[i],
            buf,
            len,
            cap
        );
    }

    json_append_char(
        buf,
        len,
        cap,
        ']'
    );

    return;
}

        default:

            json_append(
                buf,
                len,
                cap,
                "null"
            );

            return;
    }
}

Value std_json_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    (void)node;
    (void)env;
    (void)rt;

    *handled = 0;

if (
    strcmp(node->function_name, "json_stringify") == 0 ||
    strcmp(node->function_name, "json_banao") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "json_stringify",
            "1 cheez deni hogi",
            "example: json_banao(data)"
        );

        return value_null();
    }

    Value v =
        eval(node->args[0], env, rt);

    size_t cap = 256;
    size_t len = 0;

    char *buf =
        malloc(cap);

    if (!buf) {

        value_free(&v);

        return value_null();
    }

    buf[0] = '\0';

    json_stringify_value(
        v,
        &buf,
        &len,
        &cap
    );

    Value out =
        value_string(buf);

    free(buf);

    value_free(&v);

    return out;
}

    return value_null();
}
