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

case VAL_DICT:
{
    json_append_char(
        buf,
        len,
        cap,
        '{'
    );

    for (int i = 0; i < v.dict_count; i++)
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

        Value key =
            v.dict_keys[i];

        if (
            key.type == VAL_STRING &&
            key.string
        )
        {
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
                key.string
            );

            json_append_char(
                buf,
                len,
                cap,
                '"'
            );
        }
        else
        {
            json_append(
                buf,
                len,
                cap,
                "\"\""
            );
        }

        json_append_char(
            buf,
            len,
            cap,
            ':'
        );

        json_stringify_value(
            v.dict_values[i],
            buf,
            len,
            cap
        );
    }

    json_append_char(
        buf,
        len,
        cap,
        '}'
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

if (
    strcmp(node->function_name, "json_write") == 0 ||
    strcmp(node->function_name, "json_file_likho") == 0
)
{
    *handled = 1;

    if (node->arg_count != 2) {

        shriji_error(
            E_PARSE_02,
            "json_write",
            "2 cheez deni hogi",
            "example: json_file_likho(\"data.json\", data)"
        );

        return value_null();
    }

    Value pathv =
        eval(node->args[0], env, rt);

    Value datav =
        eval(node->args[1], env, rt);

    if (
        pathv.type != VAL_STRING ||
        !pathv.string
    ) {
        value_free(&pathv);
        value_free(&datav);

        return value_bool(0);
    }

    size_t cap = 256;
    size_t len = 0;

    char *buf =
        malloc(cap);

    if (!buf) {

        value_free(&pathv);
        value_free(&datav);

        return value_bool(0);
    }

    buf[0] = '\0';

    json_stringify_value(
        datav,
        &buf,
        &len,
        &cap
    );

    FILE *fp =
        fopen(pathv.string, "wb");

    if (!fp) {

        free(buf);

        value_free(&pathv);
        value_free(&datav);

        return value_bool(0);
    }

    fwrite(
        buf,
        1,
        strlen(buf),
        fp
    );

    fclose(fp);

    free(buf);

    value_free(&pathv);
    value_free(&datav);

    return value_bool(1);
}

if (
    strcmp(node->function_name, "json_read") == 0 ||
    strcmp(node->function_name, "json_padho") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "json_read",
            "1 cheez deni hogi",
            "example: json_padho(\"data.json\")"
        );

        return value_null();
    }

    Value pathv =
        eval(node->args[0], env, rt);

    if (
        pathv.type != VAL_STRING ||
        !pathv.string
    ) {
        value_free(&pathv);
        return value_null();
    }

    FILE *fp =
        fopen(pathv.string, "rb");

    if (!fp) {

        value_free(&pathv);

        return value_null();
    }

    fseek(fp, 0, SEEK_END);

    long sz = ftell(fp);

    rewind(fp);

    char *buf =
        malloc((size_t)sz + 1);

    if (!buf) {

        fclose(fp);
        value_free(&pathv);

        return value_null();
    }

    size_t read_bytes =
        fread(
            buf,
            1,
            (size_t)sz,
            fp
        );

    buf[read_bytes] = '\0';

    fclose(fp);

    Value out =
        value_string(buf);

    free(buf);

    value_free(&pathv);

    return out;
}

    return value_null();
}
