#ifndef SHRIJI_XML_TOKENIZER_H
#define SHRIJI_XML_TOKENIZER_H

/*
 * ============================================================
 * Shriji XML
 * XML Tokenizer
 * ============================================================
 *
 * Purpose:
 *   Converts XML character stream into XML tokens.
 *
 * Responsibilities:
 *   - Read characters
 *   - Produce tokens
 *   - Maintain tokenizer state
 *
 * Must NOT contain:
 *   - Parser logic
 *   - Tree building
 *   - Writer logic
 *   - Error printing
 *
 */

#include <stddef.h>

#include "xml/xml_reader.h"

#include "xml/xml_token.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct XmlTokenizer
{
    XmlReader *reader;

    XmlToken token;

    size_t line;

    size_t column;

} XmlTokenizer;


/*
 * ============================================================
 * XML Tokenizer API
 * ============================================================
 */

void
xml_tokenizer_init(
    XmlTokenizer *tokenizer,
    XmlReader *reader
);

void
xml_tokenizer_reset(
    XmlTokenizer *tokenizer
);

const XmlToken *
xml_tokenizer_next(
    XmlTokenizer *tokenizer
);

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_TOKENIZER_H */
