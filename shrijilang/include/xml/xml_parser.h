#ifndef SHRIJI_XML_PARSER_H
#define SHRIJI_XML_PARSER_H

/*
 * ============================================================
 * Shriji XML
 * XML Parser
 * ============================================================
 *
 * Purpose:
 *   Converts XML tokens into an XML document tree.
 *
 * Responsibilities:
 *   - Consume XML tokens
 *   - Build XmlDocument
 *   - Build XmlNode tree
 *
 * Must NOT contain:
 *   - Reader logic
 *   - Tokenizer logic
 *   - Writer logic
 *   - Error printing
 *
 */

#include "xml/xml_document.h"
#include "xml/xml_tokenizer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct XmlParser
{
    XmlTokenizer *tokenizer;

    XmlDocument *document;

} XmlParser;

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_PARSER_H */
