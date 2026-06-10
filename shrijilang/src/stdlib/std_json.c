#include "stdlib/std_json.h"
#include "interpreter.h"
#include "error.h"
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

static int hex_value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'f')
        return 10 + (c - 'a');

    if (c >= 'A' && c <= 'F')
        return 10 + (c - 'A');

    return -1;
}

static int utf8_encode(
    unsigned int cp,
    char *out
)
{
    if (cp <= 0x7F) {
        out[0] = cp;
        return 1;
    }

    if (cp <= 0x7FF) {
        out[0] = 0xC0 | (cp >> 6);
        out[1] = 0x80 | (cp & 0x3F);
        return 2;
    }

    out[0] = 0xE0 | (cp >> 12);
    out[1] = 0x80 | ((cp >> 6) & 0x3F);
    out[2] = 0x80 | (cp & 0x3F);

    return 3;
}

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

static char *
find_top_level_comma(
    char *s
)
{
    char *start = s;

    int obj_depth = 0;
    int arr_depth = 0;
    int in_string = 0;

    for (; *s; s++)
    {
        if (
            *s == '"' &&
            (
                s == start ||
                s[-1] != '\\'
            )
        )
        {
            in_string =
                !in_string;

            continue;
        }

        if (in_string)
            continue;

        if (*s == '{')
            obj_depth++;
        else if (*s == '}')
            obj_depth--;
        else if (*s == '[')
            arr_depth++;
        else if (*s == ']')
            arr_depth--;
        else if (
            *s == ',' &&
            obj_depth == 0 &&
            arr_depth == 0
        )
        {
            return s;
        }
    }

    return NULL;
}

static char *
find_top_level_colon(
    char *s
)
{
    char *start = s;

    int obj_depth = 0;
    int arr_depth = 0;
    int in_string = 0;

    for (; *s; s++)
    {
        if (
            *s == '"' &&
            (
                s == start ||
                s[-1] != '\\'
            )
        )
        {
            in_string =
                !in_string;

            continue;
        }

        if (in_string)
            continue;

        if (*s == '{')
            obj_depth++;
        else if (*s == '}')
            obj_depth--;
        else if (*s == '[')
            arr_depth++;
        else if (*s == ']')
            arr_depth--;
        else if (
            *s == ':' &&
            obj_depth == 0 &&
            arr_depth == 0
        )
        {
            return s;
        }
    }

    return NULL;
}

static Value
parse_json_value(
    char *s
);

static Value
parse_json_object(
    char *s
)
{

    size_t len =
        strlen(s);

    if (
        len < 2 ||
        s[0] != '{' ||
        s[len - 1] != '}'
    )
    {
        return value_null();
    }

    if (
        strcmp(s, "{}") == 0
    )
    {
        return value_dict(
            NULL,
            NULL,
            0
        );
    }

    char *inner =
        malloc(len - 1);

    if (!inner)
    {
        return value_null();
    }

    memcpy(
        inner,
        s + 1,
        len - 2
    );

    inner[len - 2] =
        '\0';

if (inner[0] == '\0')
{
    free(inner);

    return value_dict(
        NULL,
        NULL,
        0
    );
}

int count = 1;

for (char *p = inner; *p; p++)
{
    if (*p == ',')
        count++;
}

Value *keys =
    malloc(sizeof(Value) * count);

Value *vals =
    malloc(sizeof(Value) * count);

if (!keys || !vals)
{
    if (keys) free(keys);
    if (vals) free(vals);

    free(inner);

    return value_null();
}

char *pair = inner;

int idx = 0;

for (;;)
{
    char *colon =
        find_top_level_colon(
            pair
        );

    if (!colon)
    {
        free(inner);
        free(keys);
        free(vals);

        return value_null();
    }

    *colon = '\0';

    char *key =
        json_trim(pair);

    char *comma =
        find_top_level_comma(
            colon + 1
        );

    char *next_pair = NULL;

    if (comma)
    {
        next_pair = comma + 1;
        *comma = '\0';
    }

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
        free(keys);
        free(vals);

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

    keys[idx] =
        value_string(keybuf);

    Value parsed =
        parse_json_value(val);

    if (
        parsed.type == VAL_NULL &&
        strcmp(val, "null") != 0
    )
    {
        free(inner);
        free(keys);
        free(vals);

        return value_null();
    }

    vals[idx] =
        parsed;

    idx++;

    if (!next_pair)
        break;

    pair = next_pair;
}

free(inner);

return value_dict(
    keys,
    vals,
    idx
);

}

static Value
json_parse_array(
    char *s
)
{
    size_t len =
        strlen(s);

    if (
        len < 2 ||
        s[0] != '[' ||
        s[len - 1] != ']'
    )
    {
        return value_null();
    }

    char *inner =
        malloc(len - 1);

    if (!inner)
    {
        return value_null();
    }

    memcpy(
        inner,
        s + 1,
        len - 2
    );

    inner[len - 2] =
        '\0';

if (inner[0] == '\0')
{
    free(inner);

    return value_list(
        NULL,
        0
    );
}

    int count = 1;

    for (char *p = inner; *p; p++)
    {
        if (*p == ',')
            count++;
    }

    Value *items =
        malloc(sizeof(Value) * count);

    if (!items)
    {
        free(inner);
        return value_null();
    }

    int idx = 0;

char *start = inner;

for (;;)
{
    char *comma =
        find_top_level_comma(
            start
        );

    char *end =
        comma
            ? comma
            : start + strlen(start);

    char old = *end;
    *end = '\0';

char *token =
    json_trim(start);

if (token[0] == '\0')
{
    free(inner);
    free(items);

    return value_null();
}

Value parsed =
    parse_json_value(token);

items[idx++] =
    parsed;

    *end = old;

    if (!comma)
        break;

    start = comma + 1;
}

    free(inner);

    return value_list(
        items,
        idx
    );
}

static Value
parse_json_value(
    char *s
)
{
s = json_trim(s);
    if (
        strcmp(s, "true") == 0
    )
    {
        return value_bool(1);
    }

    if (
        strcmp(s, "false") == 0
    )
    {
        return value_bool(0);
    }

    if (
        strcmp(s, "null") == 0
    )
    {
        return value_null();
    }

    if (
        is_json_number(s)
    )
    {
        if (strchr(s, '.'))
        {
            return value_number(
                atof(s)
            );
        }

        return value_int(
            atoll(s)
        );
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

        if (!tmp)
        {
            return value_null();
        }

        memcpy(
            tmp,
            s + 1,
            len - 2
        );

        tmp[len - 2] =
            '\0';

char decoded[1024];
int di = 0;

for (
    int si = 0;
    tmp[si] != '\0' &&
    di < (int)sizeof(decoded) - 1;
    si++
)
{
    if (
        tmp[si] == '\\' &&
        tmp[si + 1] == 'u'
    )
    {
        int h1 =
            hex_value(tmp[si + 2]);
        int h2 =
            hex_value(tmp[si + 3]);
        int h3 =
            hex_value(tmp[si + 4]);
        int h4 =
            hex_value(tmp[si + 5]);

        if (
            h1 >= 0 &&
            h2 >= 0 &&
            h3 >= 0 &&
            h4 >= 0
        )
        {
            unsigned int cp =
                (h1 << 12) |
                (h2 << 8)  |
                (h3 << 4)  |
                h4;

            char utf8[4];

            int bytes =
                utf8_encode(
                    cp,
                    utf8
                );

            for (
                int k = 0;
                k < bytes;
                k++
            )
            {
                decoded[di++] =
                    utf8[k];
            }

            si += 5;
            continue;
        }
    }

    decoded[di++] =
        tmp[si];
}

decoded[di] = '\0';

Value out =
    value_string(decoded);

free(tmp);

return out;

}

if (
    len >= 2 &&
    s[0] == '{' &&
    s[len - 1] == '}'
)
{
    return parse_json_object(s);
}

if (
    len >= 2 &&
    s[0] == '[' &&
    s[len - 1] == ']'
)
{
    return json_parse_array(s);
}

return value_null();
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

shriji_arg_count_error(
    "json_stringify",
    1,
    node->arg_count
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

shriji_arg_count_error(
    "json_write",
    2,
    node->arg_count
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

shriji_arg_count_error(
    "json_read",
    1,
    node->arg_count
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

shriji_arg_count_error(
    "json_parse",
    1,
    node->arg_count
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

Value primitive =
    parse_json_value(s);

if (
    primitive.type != VAL_NULL
)
{
    value_free(&textv);
    return primitive;
}

size_t len =
    strlen(s);

if (
    len >= 2 &&
    s[0] == '[' &&
    s[len - 1] == ']'
)
{
    value_free(&textv);

    return json_parse_array(s);
}

if (
    len >= 2 &&
    s[0] == '{' &&
    s[len - 1] == '}'
)
{
    value_free(&textv);

    return parse_json_object(s);
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

for (char *p = inner;;)
{
    char *comma =
        find_top_level_comma(p);

    if (!comma)
        break;

    count++;

    p = comma + 1;
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


if (token[0] == '\0')
{
    free(inner);
    free(items);

    return value_null();
}

Value parsed =
    parse_json_value(token);

      items[idx++] =
            parsed;

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
