#include "stdlib/std_file.h"
#include "interpreter.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *strip_quotes(const char *s)
{
    if (!s)
        return "";

    while (*s == ' ' || *s == '\t')
        s++;

    size_t len = strlen(s);

    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {

        static char buf[1024];

        size_t n = len - 2;

        if (n >= sizeof(buf))
            n = sizeof(buf) - 1;

        memcpy(buf, s + 1, n);

        buf[n] = '\0';

        return buf;
    }

    return s;
}

static char *unescape_string(const char *s)
{
    if (!s)
        return NULL;

    size_t n = strlen(s);

    char *out = malloc(n + 1);

    if (!out)
        return NULL;

    size_t j = 0;

    for (size_t i = 0; i < n; i++) {

        if (s[i] == '\\' && i + 1 < n) {

            char c = s[i + 1];

            if (c == 'n') {
                out[j++] = '\n';
                i++;
                continue;
            }

            if (c == 't') {
                out[j++] = '\t';
                i++;
                continue;
            }

            if (c == 'r') {
                out[j++] = '\r';
                i++;
                continue;
            }

            if (c == '\\') {
                out[j++] = '\\';
                i++;
                continue;
            }

            if (c == '"') {
                out[j++] = '"';
                i++;
                continue;
            }
        }

        out[j++] = s[i];
    }

    out[j] = '\0';

    return out;
}

Value std_file_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /* PADHO */

    if (strcmp(node->function_name, "padho") == 0) {

        *handled = 1;

        if (node->arg_count != 1) {

shriji_arg_count_error(
    "padho",
    1,
    node->arg_count
);

            return value_null();
        }

        Value pathv = eval(node->args[0], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {
            value_free(&pathv);

shriji_arg_type_error(
    "padho",
    "string"
);

            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

        FILE *fp = fopen(path, "rb");

        if (!fp) {

            value_free(&pathv);

            shriji_error(
                E_PARSE_02,
                "padho",
                "file not found",
                "check path or create file first"
            );

            return value_string("");
        }

        fseek(fp, 0, SEEK_END);
        long sz = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (sz < 0)
            sz = 0;

        if (sz > 1024 * 1024)
            sz = 1024 * 1024;

        char *buf = malloc((size_t)sz + 1);

        if (!buf) {

            fclose(fp);
            value_free(&pathv);

            return value_null();
        }

        size_t nread = fread(buf, 1, (size_t)sz, fp);

        buf[nread] = '\0';

        fclose(fp);
        value_free(&pathv);

        Value out = value_string(buf);

        free(buf);

        return out;
    }

    if (strcmp(node->function_name, "likho") == 0) {

        *handled = 1;

        if (node->arg_count != 2)
            return value_null();

        Value pathv = eval(node->args[0], env, rt);
        Value datav = eval(node->args[1], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {

            value_free(&pathv);
            value_free(&datav);

            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

        const char *data = "";
        char tmp[128] = {0};

        char *tmp_data = NULL;

        if (datav.type == VAL_STRING && datav.string) {

            tmp_data = unescape_string(
                strip_quotes(datav.string)
            );

            data = tmp_data ? tmp_data : "";
        }
        else if (datav.type == VAL_NUMBER) {

            snprintf(
                tmp,
                sizeof(tmp),
                "%g",
                datav.number
            );

            data = tmp;
        }

        FILE *fp = fopen(path, "wb");

        if (!fp) {

            if (tmp_data)
                free(tmp_data);

            value_free(&pathv);
            value_free(&datav);

            return value_number(0);
        }

        fwrite(data, 1, strlen(data), fp);

        fclose(fp);

        if (tmp_data)
            free(tmp_data);

        value_free(&pathv);
        value_free(&datav);

        return value_number(1);
    }


    if (strcmp(node->function_name, "jodo") == 0) {

        *handled = 1;

        if (node->arg_count != 2)
            return value_null();

        Value pathv = eval(node->args[0], env, rt);
        Value datav = eval(node->args[1], env, rt);

        if (pathv.type != VAL_STRING || !pathv.string) {

            value_free(&pathv);
            value_free(&datav);

            return value_null();
        }

        const char *path = strip_quotes(pathv.string);

        const char *data = "";
        char tmp[128] = {0};

        char *tmp_data = NULL;

        if (datav.type == VAL_STRING && datav.string) {

            tmp_data = unescape_string(
                strip_quotes(datav.string)
            );

            data = tmp_data ? tmp_data : "";
        }
        else if (datav.type == VAL_NUMBER) {

            snprintf(
                tmp,
                sizeof(tmp),
                "%g",
                datav.number
            );

            data = tmp;
        }

        FILE *fp = fopen(path, "ab");

        if (!fp) {

            if (tmp_data)
                free(tmp_data);

            value_free(&pathv);
            value_free(&datav);

            return value_number(0);
        }

        fwrite(data, 1, strlen(data), fp);

        fclose(fp);

        if (tmp_data)
            free(tmp_data);

        value_free(&pathv);
        value_free(&datav);

        return value_number(1);
    }
    return value_null();
}
