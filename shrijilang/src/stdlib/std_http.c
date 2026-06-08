#define _POSIX_C_SOURCE 200112L
#include "stdlib/std_http.h"
#include "interpreter.h"
#include "error.h"

#include <string.h>

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

static int parse_url(
    const char *url,
    char *host,
    size_t host_size,
    char *path,
    size_t path_size
)
{
    if (!url)
        return 0;

    const char *p = url;

    if (strncmp(p, "http://", 7) == 0) {
        p += 7;
    } else {
        return 0;
    }

    const char *slash = strchr(p, '/');

    if (!slash) {

        snprintf(
            host,
            host_size,
            "%s",
            p
        );

        snprintf(
            path,
            path_size,
            "/"
        );

        return 1;
    }

    size_t host_len =
        (size_t)(slash - p);

    if (host_len >= host_size)
        host_len = host_size - 1;

    memcpy(
        host,
        p,
        host_len
    );

    host[host_len] = '\0';

    snprintf(
        path,
        path_size,
        "%s",
        slash
    );

    return 1;
}

static int test_dns(const char *host)
{
    struct addrinfo hints;
    struct addrinfo *result = NULL;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(
        host,
        "80",
        &hints,
        &result
    );

    if (rc != 0)
        return 0;

    freeaddrinfo(result);

    return 1;
}

static int test_connect(const char *host)
{
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *rp;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(
        host,
        "80",
        &hints,
        &result
    );

    if (rc != 0)
        return 0;

    int connected = 0;

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        int sockfd = socket(
            rp->ai_family,
            rp->ai_socktype,
            rp->ai_protocol
        );

        if (sockfd < 0)
            continue;

        if (
            connect(
                sockfd,
                rp->ai_addr,
                rp->ai_addrlen
            ) == 0
        ) {
            connected = 1;
            close(sockfd);
            break;
        }

        close(sockfd);
    }

    freeaddrinfo(result);

    return connected;
}



static int extract_status_code(
    const char *response
)
{
    if (!response)
        return 0;

    int status = 0;

    if (
        sscanf(
            response,
            "HTTP/%*s %d",
            &status
        ) != 1
    ) {
        return 0;
    }

    return status;
}

static char *extract_body(
    const char *response
)
{
    if (!response)
        return NULL;

    const char *body =
        strstr(
            response,
            "\r\n\r\n"
        );

    if (!body)
        return NULL;

    body += 4;

    char *out =
        malloc(
            strlen(body) + 1
        );

    if (!out)
        return NULL;

    strcpy(out, body);

    return out;
}

static char *extract_headers(
    const char *response
)
{
    if (!response)
        return NULL;

    const char *start =
        strstr(
            response,
            "\r\n"
        );

    if (!start)
        return NULL;

    start += 2;

    const char *end =
        strstr(
            start,
            "\r\n\r\n"
        );

    if (!end)
        return NULL;

    size_t len =
        (size_t)(end - start);

    char *out =
        malloc(len + 1);

    if (!out)
        return NULL;

    memcpy(
        out,
        start,
        len
    );

    out[len] = '\0';

    return out;
}

static char *send_http_get(
    const char *host,
    const char *path
)
{
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *rp;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(
        host,
        "80",
        &hints,
        &result
    );

    if (rc != 0)
        return NULL;

    int sockfd = -1;

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(
            rp->ai_family,
            rp->ai_socktype,
            rp->ai_protocol
        );

        if (sockfd < 0)
            continue;

        if (
            connect(
                sockfd,
                rp->ai_addr,
                rp->ai_addrlen
            ) == 0
        ) {
            break;
        }

        close(sockfd);
        sockfd = -1;
    }

    freeaddrinfo(result);

    if (sockfd < 0)
        return NULL;

    char request[2048];

    snprintf(
        request,
        sizeof(request),
        "GET %s HTTP/1.0\r\n"
        "Host: %s\r\n"
        "\r\n",
        path,
        host
    );

    send(
        sockfd,
        request,
        strlen(request),
        0
    );

    char *response = malloc(65536);

    if (!response) {
        close(sockfd);
        return NULL;
    }

    int total = 0;

    while (1)
    {
        int n = recv(
            sockfd,
            response + total,
            65535 - total,
            0
        );

        if (n <= 0)
            break;

        total += n;

        if (total >= 65535)
            break;
    }

    response[total] = '\0';

    close(sockfd);

    return response;
}

static char *send_http_post(
    const char *host,
    const char *path,
    const char *data
)
{
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *rp;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(
        host,
        "80",
        &hints,
        &result
    );

    if (rc != 0)
        return NULL;

    int sockfd = -1;

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(
            rp->ai_family,
            rp->ai_socktype,
            rp->ai_protocol
        );

        if (sockfd < 0)
            continue;

        if (
            connect(
                sockfd,
                rp->ai_addr,
                rp->ai_addrlen
            ) == 0
        ) {
            break;
        }

        close(sockfd);
        sockfd = -1;
    }

    freeaddrinfo(result);

    if (sockfd < 0)
        return NULL;

    char request[8192];

    snprintf(
        request,
        sizeof(request),
        "POST %s HTTP/1.0\r\n"
        "Host: %s\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s",
        path,
        host,
        strlen(data),
        data
    );

    send(
        sockfd,
        request,
        strlen(request),
        0
    );

    char *response = malloc(65536);

    if (!response) {
        close(sockfd);
        return NULL;
    }

    int total = 0;

    while (1)
    {
        int n = recv(
            sockfd,
            response + total,
            65535 - total,
            0
        );

        if (n <= 0)
            break;

        total += n;

        if (total >= 65535)
            break;
    }

    response[total] = '\0';

    close(sockfd);

    return response;
}

Value std_http_call(
    ASTNode *node,
    Env *env,
    ShrijiRuntime *rt,
    int *handled
)
{
    *handled = 0;

    /*──────────────────────────────────────────────
      HTTP_GET
    ──────────────────────────────────────────────*/
    if (strcmp(node->function_name, "http_get") == 0)
    {
        *handled = 1;

        if (node->arg_count != 1) {

            shriji_error(
                E_PARSE_02,
                "http_get",
                "http_get ko ek URL chahiye",
                "udaharan: http_get(\"http://example.com\")"
            );

            return value_null();
        }

        Value urlv = eval(
            node->args[0],
            env,
            rt
        );

        if (
            urlv.type != VAL_STRING ||
            !urlv.string
        ) {
            value_free(&urlv);

            shriji_error(
                E_PARSE_02,
                "http_get",
                "URL string hona chahiye",
                "udaharan: http_get(\"http://example.com\")"
            );

            return value_null();
        }

        char host[256];
        char path[512];

        if (
            !parse_url(
                urlv.string,
                host,
                sizeof(host),
                path,
                sizeof(path)
            )
        ) {
            value_free(&urlv);

            shriji_error(
                E_PARSE_02,
                "http_get",
                "sirf http:// URL support hai",
                "udaharan: http_get(\"http://example.com\")"
            );

            return value_null();
        }

        if (!test_dns(host)) {

            value_free(&urlv);

            shriji_error(
                E_RUNTIME_01,
                "http_get",
                "DNS lookup fail hua",
                host
            );

            return value_null();
        }

        if (!test_connect(host)) {

            value_free(&urlv);

            shriji_error(
                E_RUNTIME_01,
                "http_get",
                "server se connection nahi hua",
                host
            );


            return value_null();
        }

char *response =
    send_http_get(
        host,
        path
    );

value_free(&urlv);

if (!response) {

    shriji_error(
        E_RUNTIME_01,
        "http_get",
        "HTTP request fail hui",
        host
    );

    return value_null();
}

int status =
    extract_status_code(
        response
    );

char *body =
    extract_body(
        response
    );

Value *keys =
    malloc(
        sizeof(Value) * 2
    );

Value *values =
    malloc(
        sizeof(Value) * 2
    );

if (!keys || !values) {

    if (keys)
        free(keys);

    if (values)
        free(values);

    if (body)
        free(body);

    free(response);

    return value_null();
}

keys[0] =
    value_string(
        "status"
    );

values[0] =
    value_int(
        status
    );

keys[1] =
    value_string(
        "body"
    );

values[1] =
    value_string(
        body ? body : ""
    );

if (body)
    free(body);

free(response);

return value_dict(
    keys,
    values,
    2
);

    }

if (strcmp(node->function_name, "http_post") == 0)
{
    *handled = 1;

    if (node->arg_count != 2) {

        shriji_error(
            E_PARSE_02,
            "http_post",
            "http_post ko URL aur data chahiye",
            "udaharan: http_post(url, data)"
        );

        return value_null();
    }

    Value urlv =
        eval(node->args[0], env, rt);

    Value datav =
        eval(node->args[1], env, rt);

    if (
        urlv.type != VAL_STRING ||
        datav.type != VAL_STRING
    ) {

        value_free(&urlv);
        value_free(&datav);

        shriji_error(
            E_PARSE_02,
            "http_post",
            "URL aur data string hone chahiye",
            "http_post(url, data)"
        );

        return value_null();
    }

    char host[256];
    char path[512];

    if (
        !parse_url(
            urlv.string,
            host,
            sizeof(host),
            path,
            sizeof(path)
        )
    ) {

        value_free(&urlv);
        value_free(&datav);

        return value_null();
    }

    char *response =
        send_http_post(
            host,
            path,
            datav.string
        );

    value_free(&urlv);
    value_free(&datav);

    if (!response)
        return value_null();

int status =
    extract_status_code(
        response
    );

char *body =
    extract_body(
        response
    );

char *headers =
    extract_headers(
        response
    );

Value *keys =
    malloc(
        sizeof(Value) * 3
    );

Value *values =
    malloc(
        sizeof(Value) * 3
    );

if (!keys || !values) {

    if (keys)
        free(keys);

    if (values)
        free(values);

    if (body)
        free(body);

    if (headers)
        free(headers);

    free(response);

    return value_null();
}

keys[0] =
    value_string(
        "status"
    );

values[0] =
    value_int(
        status
    );

keys[1] =
    value_string(
        "body"
    );

values[1] =
    value_string(
        body ? body : ""
    );

keys[2] =
    value_string(
        "headers"
    );

values[2] =
    value_string(
        headers
            ? headers
            : ""
    );

if (body)
    free(body);

if (headers)
    free(headers);

free(response);

return value_dict(
    keys,
    values,
    3
);

}

    return value_null();
}
