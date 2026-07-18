#ifndef SHRIJI_XML_DOCUMENT_H
#define SHRIJI_XML_DOCUMENT_H

/*
 * ============================================================
 * Shriji XML
 * XML Document
 * ============================================================
 *
 * Purpose:
 *   Defines the XML document data model.
 *
 * Responsibilities:
 *   - XML declaration metadata
 *   - Root node ownership
 *
 * Must NOT contain:
 *   - Parser logic
 *   - Reader logic
 *   - Writer logic
 *   - Tokenizer logic
 *   - Error handling
 *
 */

#include "xml/xml_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================
 * XML Document
 * ============================================================
 */

struct XmlDocument
{
    const char *version;

    const char *encoding;

    bool standalone;

    XmlNode *root;
};

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_DOCUMENT_H */
