#include "stdlib/std_json.h"
#include "interpreter.h"
#include "error.h"
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

static char *json_trim(char *s)
{
    while (
        *s &&
        isspace((unsigned char)*s)
    )
    {
        s++;
    }

    size_t len = strlen(s);

    while (
        len > 0 &&
        isspace(
            (unsigned char)s[len - 1]
        )
    )
    {
        s[--len] = '\0';
    }

    return s;
}

static int is_json_number(
    const char *s
)
{
    if (!s || !*s)
        return 0;

    int dot = 0;

    int i = 0;

    if (
        s[0] == '-' ||
        s[0] == '+'
    )
    {
        i++;
    }

    for (; s[i]; i++)
    {
        if (s[i] == '.')
        {
            if (dot)
                return 0;

            dot = 1;

            continue;
        }

        if (!isdigit(
                (unsigned char)s[i]
            ))
        {
            return 0;
        }
    }

    return 1;
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

if (
    strcmp(node->function_name, "json_parse") == 0
)
{
    *handled = 1;

    if (node->arg_count != 1) {

        shriji_error(
            E_PARSE_02,
            "json_parse",
            "1 cheez deni hogi",
            "example: json_parse(\"123\")"
        );

        return value_null();
    }

    Value textv =
        eval(node->args[0], env, rt);

    if (
        textv.type != VAL_STRING ||
        !textv.string
    ) {
        value_free(&textv);
        return value_null();
    }

    char *s =
        textv.string;

    if (
        strcmp(s, "true") == 0
    ) {
        value_free(&textv);
        return value_bool(1);
    }

    if (
        strcmp(s, "false") == 0
    ) {
        value_free(&textv);
        return value_bool(0);
    }

    if (
       strcmp(s, "null") == 0
    ) {
        value_free(&textv);
        return value_null();
    }

    if (
        is_json_number(s)
    )
    {
        if (strchr(s, '.'))
        {
            double n =
                atof(s);

            value_free(&textv);

            return value_number(n);
        }

        long long n =
            atoll(s);

        value_free(&textv);

        return value_int(n);
    }

    size_t len =
        strlen(s);

    if (
        len >= 2 &&
        s[0] == '"' &&
        s[len - 1] == '"'
    )
    {
        char *tmp =
            malloc(len - 1);

        if (!tmp) {

            value_free(&textv);

            return value_null();
        }

        memcpy(
            tmp,
            s + 1,
            len - 2
        );

        tmp[len - 2] = '\0';

        Value out =
            value_string(tmp);

        free(tmp);

        value_free(&textv);

        return out;
    }

if (
    len >= 2 &&
    s[0] == '[' &&
    s[len - 1] == ']'
)
{
    char *inner =
        malloc(len - 1);

    if (!inner) {

        value_free(&textv);

        return value_null();
    }

    memcpy(
        inner,
        s + 1,
        len - 2
    );

    inner[len - 2] = '\0';

    int count = 1;

    for (char *p = inner; *p; p++)
    {
        if (*p == ',')
            count++;
    }

    Value *items =
        malloc(sizeof(Value) * count);

    if (!items) {

        free(inner);
        value_free(&textv);

        return value_null();
    }

    int idx = 0;

    char *start = inner;

    for (char *p = inner;; p++)
    {
        if (*p == ',' || *p == '\0')
        {
            char old = *p;
                  *p = '\0';

             char *token =
                   json_trim(start);

            if (is_json_number(token))
            {
                if (strchr(token, '.'))
                    items[idx++] =
                        value_number(
                         atof(token)
                        );
                else
                    items[idx++] =
                        value_int(
                          atoll(token)
                        );
            }

else if (
     strcmp(token, "true") == 0
)
{
    items[idx++] =
        value_bool(1);
}
else if (
    strcmp(token, "false") == 0
)
{
    items[idx++] =
        value_bool(0);
}
else if (
    strcmp(token, "null") == 0
)
{
    items[idx++] =
        value_null();
}

else
{

     size_t token_len =
    strlen(token);

if (
    token_len >= 2 &&
    token[0] == '"' &&
    token[token_len - 1] == '"'
)
{
    char *tmp =
        malloc(token_len - 1);

    if (tmp)
    {
        memcpy(
            tmp,
            token + 1,
            token_len - 2
        );

        tmp[token_len - 2] =
            '\0';

        items[idx++] =
            value_string(tmp);

        free(tmp);
    }
}

}

            *p = old;

            if (old == '\0')
                break;

            start = p + 1;
        }
    }

    free(inner);
    value_free(&textv);

    return value_list(
        items,
        idx
    );
}

if (
    len >= 2 &&
    s[0] == '{' &&
    s[len - 1] == '}'
)
{
    char *inner =
        malloc(len - 1);

    if (!inner) {

        value_free(&textv);

        return value_null();
    }

    memcpy(
        inner,
        s + 1,
        len - 2
    );

    inner[len - 2] = '\0';

    char *colon =
        strchr(inner, ':');

    if (!colon)
    {
        free(inner);
        value_free(&textv);

        return value_null();
    }

    *colon = '\0';

    char *key =
        json_trim(inner);

    char *val =
        json_trim(colon + 1);

    size_t key_len =
        strlen(key);

    if (
        key_len < 2 ||
        key[0] != '"' ||
        key[key_len - 1] != '"'
    )
    {
        free(inner);
        value_free(&textv);

        return value_null();
    }

    Value *keys =
        malloc(sizeof(Value));

    Value *vals =
        malloc(sizeof(Value));

    if (!keys || !vals)
    {
        if (keys) free(keys);
        if (vals) free(vals);

        free(inner);
        value_free(&textv);

        return value_null();
    }

    char keybuf[256];

    memcpy(
        keybuf,
        key + 1,
        key_len - 2
    );

    keybuf[key_len - 2] =
        '\0';

    keys[0] =
        value_string(keybuf);

if (
    is_json_number(val)
)
{
    if (strchr(val, '.'))
    {
        vals[0] =
            value_number(
                atof(val)
            );
    }
    else
    {
        vals[0] =
            value_int(
                atoll(val)
            );
    }
}
else if (
    strcmp(val, "true") == 0
)
{
    vals[0] =
        value_bool(1);
}
else if (
    strcmp(val, "false") == 0
)
{
    vals[0] =
        value_bool(0);
}
else if (
    strcmp(val, "null") == 0
)
{
    vals[0] =
        value_null();
}
else
{

    size_t val_len =
        strlen(val);

    if (
        val_len >= 2 &&
        val[0] == '"' &&
        val[val_len - 1] == '"'
    )
    {
        char *tmp =
            malloc(val_len - 1);

        memcpy(
            tmp,
            val + 1,
            val_len - 2
        );

        tmp[val_len - 2] =
            '\0';

        vals[0] =
            value_string(tmp);

        free(tmp);
    }
    else
    {
        free(inner);
        free(keys);
        free(vals);
        value_free(&textv);

        return value_null();
    }
}

free(inner);
value_free(&textv);

return value_dict(
    keys,
    vals,
    1
);
}

value_free(&textv);

shriji_error(
    E_PARSE_02,
    "json_parse",
    "invalid json",
    "example: json_parse(\"123\")"
);

return value_null();

}

    return value_null();
}
