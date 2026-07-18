#ifndef SHRIJI_XML_TOKEN_H
#define SHRIJI_XML_TOKEN_H

/*
 * ============================================================
 * Shriji XML
 * XML Token
 * ============================================================
 *
 * Purpose:
 *   Defines XML lexical tokens.
 *
 * Responsibilities:
 *   - XML token type
 *   - XML token data
 *   - Token location
 *
 * Must NOT contain:
 *   - Reader logic
 *   - Tokenizer logic
 *   - Parser logic
 *   - Writer logic
 *   - Error handling
 *
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum XmlTokenType
{
    XML_TOKEN_UNKNOWN = 0,

    XML_TOKEN_EOF,

    XML_TOKEN_OPEN_TAG,

    XML_TOKEN_CLOSE_TAG,

    XML_TOKEN_SLASH,

    XML_TOKEN_EQUALS,

    XML_TOKEN_IDENTIFIER,

    XML_TOKEN_STRING,

    XML_TOKEN_TEXT

} XmlTokenType;

typedef struct XmlToken
{
    XmlTokenType type;

    const char *start;

    size_t length;

    size_t line;

    size_t column;

} XmlToken;

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_TOKEN_H */
