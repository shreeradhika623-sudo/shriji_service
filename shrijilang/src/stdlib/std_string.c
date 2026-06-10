#include "stdlib/std_string.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

Value std_string_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /* LOWER */

    if (
        strcmp(node->function_name, "lower") == 0 ||
        strcmp(node->function_name, "chhota") == 0
    )
    {
        *handled = 1;

if (node->arg_count != 1) {

    shriji_arg_count_error(
        "lower",
        1,
        node->arg_count
    );

    return value_null();
}

   Value v = eval(node->args[0], env, rt);

    if (v.type != VAL_STRING || !v.string) {

    value_free(&v);

shriji_arg_type_error(
    "lower",
    "string"
);

        return value_null();
        }

        size_t len = strlen(v.string);

        char *buf = malloc(len + 1);

        if (!buf) {

            value_free(&v);

            return value_null();
        }

        for (size_t i = 0; i < len; i++) {

            buf[i] = (char)tolower(
                (unsigned char)v.string[i]
            );
        }

        buf[len] = '\0';

        Value out = value_string(buf);

        free(buf);
        value_free(&v);

        return out;
    }


    /* UPPER */

    if (
        strcmp(node->function_name, "upper") == 0 ||
        strcmp(node->function_name, "bada") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 1) {

shriji_arg_count_error(
    "upper",
    1,
    node->arg_count
);

      return value_null();
      }

   Value v = eval(node->args[0], env, rt);

   if (v.type != VAL_STRING || !v.string) {

    value_free(&v);

shriji_arg_type_error(
    "upper",
    "string"
);

        return value_null();
        }


        size_t len = strlen(v.string);

        char *buf = malloc(len + 1);

        if (!buf) {

            value_free(&v);

            return value_null();
        }

        for (size_t i = 0; i < len; i++) {

            buf[i] = (char)toupper(
                (unsigned char)v.string[i]
            );
        }

        buf[len] = '\0';

        Value out = value_string(buf);

        free(buf);
        value_free(&v);

        return out;
    }

    /* TRIM */

    if (
        strcmp(node->function_name, "trim") == 0 ||
        strcmp(node->function_name, "saaf") == 0
    )
    {
        *handled = 1;

if (node->arg_count != 1) {

    shriji_arg_count_error(
        "trim",
        1,
        node->arg_count
    );

    return value_null();
}

   Value v = eval(node->args[0], env, rt);

   if (v.type != VAL_STRING || !v.string) {

    value_free(&v);

shriji_arg_type_error(
    "trim",
    "string"
);

        return value_null();
        }

        const char *s = v.string;

        while (*s && isspace((unsigned char)*s))
            s++;

        size_t len = strlen(s);

        while (
            len > 0 &&
            isspace((unsigned char)s[len - 1])
        )
        {
            len--;
        }

        char *buf = malloc(len + 1);

        if (!buf) {

            value_free(&v);

            return value_null();
        }

        memcpy(buf, s, len);

        buf[len] = '\0';

        Value out = value_string(buf);

        free(buf);
        value_free(&v);

        return out;
    }

    /* SPLIT */

     if (
         strcmp(node->function_name, "split") == 0 ||
         strcmp(node->function_name, "baanto") == 0
    )
    {
        *handled = 1;

         if (node->arg_count != 2) {

shriji_arg_count_error(
    "split",
    2,
    node->arg_count
);

      return value_null();
      }

        Value textv = eval(node->args[0], env, rt);
        Value sepv  = eval(node->args[1], env, rt);

        if (
            textv.type != VAL_STRING ||
            !textv.string ||
            sepv.type != VAL_STRING ||
            !sepv.string
        ) {

            value_free(&textv);
            value_free(&sepv);

shriji_arg_type_error(
    "split",
    "string"
);

            return value_null();
        }

        const char *text = textv.string;
        const char *sep  = sepv.string;

        size_t sep_len = strlen(sep);

        if (sep_len == 0) {

            value_free(&textv);
            value_free(&sepv);

            return value_list(NULL, 0);
        }

        if (strlen(text) == 0) {

            value_free(&textv);
            value_free(&sepv);

            return value_list(NULL, 0);
        }

        int count = 1;

        const char *p = text;

        while ((p = strstr(p, sep)) != NULL) {
            count++;
            p += sep_len;
        }

        Value *items = malloc(sizeof(Value) * count);

        if (!items) {

            value_free(&textv);
            value_free(&sepv);

            return value_null();
        }

        int idx = 0;

        const char *start = text;
        const char *found;

        while ((found = strstr(start, sep)) != NULL) {

            size_t len = (size_t)(found - start);

            char *token = malloc(len + 1);

            memcpy(token, start, len);
            token[len] = '\0';

            items[idx++] = value_string(token);

            free(token);

            start = found + sep_len;
        }

        items[idx++] = value_string(start);

        value_free(&textv);
        value_free(&sepv);

        return value_list(items, idx);
    }

    /* REPLACE */

     if (
         strcmp(node->function_name, "replace") == 0 ||
         strcmp(node->function_name, "badlo") == 0
    )

    {
        *handled = 1;

        if (node->arg_count != 3) {

shriji_arg_count_error(
    "replace",
    3,
    node->arg_count
);

            return value_null();
        }

        Value textv = eval(node->args[0], env, rt);
        Value oldv  = eval(node->args[1], env, rt);
        Value newv  = eval(node->args[2], env, rt);

        if (
            textv.type != VAL_STRING || !textv.string ||
            oldv.type  != VAL_STRING || !oldv.string ||
            newv.type  != VAL_STRING || !newv.string
        ) {

            value_free(&textv);
            value_free(&oldv);
            value_free(&newv);

shriji_arg_type_error(
    "replace",
    "string"
);

            return value_null();
        }

        const char *text = textv.string;
        const char *olds = oldv.string;
        const char *news = newv.string;

        size_t old_len = strlen(olds);
        size_t new_len = strlen(news);

        if (old_len == 0) {

            value_free(&textv);
            value_free(&oldv);
            value_free(&newv);

            shriji_error(
                E_PARSE_02,
                "replace",
                "old text cannot be empty",
                "second argument must not be empty"
            );

            return value_null();
        }

        int count = 0;

        const char *p = text;

        while ((p = strstr(p, olds)) != NULL) {
            count++;
            p += old_len;
        }

        size_t final_len =
            strlen(text) +
            ((size_t)count * (new_len - old_len));

        char *buf = malloc(final_len + 1);

        if (!buf) {

            value_free(&textv);
            value_free(&oldv);
            value_free(&newv);

            return value_null();
        }

        char *out = buf;

        const char *start = text;
        const char *found;

        while ((found = strstr(start, olds)) != NULL) {

            size_t chunk = (size_t)(found - start);

            memcpy(out, start, chunk);
            out += chunk;

            memcpy(out, news, new_len);
            out += new_len;

            start = found + old_len;
        }

        strcpy(out, start);

        Value result = value_string(buf);

        free(buf);

        value_free(&textv);
        value_free(&oldv);
        value_free(&newv);

        return result;
    }

    /* STARTSWITH */

    if (
        strcmp(node->function_name, "startswith") == 0 ||
        strcmp(node->function_name, "shuru_hota_hai") == 0
    )
    {
        *handled = 1;

        if (node->arg_count != 2) {

shriji_arg_count_error(
    "startswith",
    2,
    node->arg_count
);

            return value_null();
        }

        Value textv   = eval(node->args[0], env, rt);
        Value prefixv = eval(node->args[1], env, rt);

        if (
            textv.type != VAL_STRING ||
            !textv.string ||
            prefixv.type != VAL_STRING ||
            !prefixv.string
        ) {

            value_free(&textv);
            value_free(&prefixv);

shriji_arg_type_error(
    "startswith",
    "string"
);

            return value_null();
        }

        size_t text_len   = strlen(textv.string);
        size_t prefix_len = strlen(prefixv.string);

        int result = 0;

        if (prefix_len <= text_len) {

            result =
                strncmp(
                    textv.string,
                    prefixv.string,
                    prefix_len
                ) == 0;
        }

        value_free(&textv);
        value_free(&prefixv);

        return value_bool(result);
    }

    /* ENDSWITH */

    if (
        strcmp(node->function_name, "endswith") == 0 ||
        strcmp(node->function_name, "khatam_hota_hai") == 0
     )
    {
        *handled = 1;

        if (node->arg_count != 2) {

shriji_arg_count_error(
    "endswith",
    2,
    node->arg_count
);

            return value_null();
        }

        Value textv  = eval(node->args[0], env, rt);
        Value suffixv = eval(node->args[1], env, rt);

        if (
            textv.type != VAL_STRING ||
            !textv.string ||
            suffixv.type != VAL_STRING ||
            !suffixv.string
        ) {

            value_free(&textv);
            value_free(&suffixv);

shriji_arg_type_error(
    "endswith",
    "string"
);

            return value_null();
        }

        size_t text_len   = strlen(textv.string);
        size_t suffix_len = strlen(suffixv.string);

        int result = 0;

        if (suffix_len <= text_len) {

            result =
                strcmp(
                    textv.string +
                    text_len -
                    suffix_len,
                    suffixv.string
                ) == 0;
        }

        value_free(&textv);
        value_free(&suffixv);

        return value_bool(result);
    }

    return value_null();
}
