#ifndef SHRIJI_XML_ATTRIBUTE_H
#define SHRIJI_XML_ATTRIBUTE_H

/*
 * ============================================================
 * Shriji XML
 * XML Attribute
 * ============================================================
 *
 * Purpose:
 *   Defines the XML attribute data model.
 *
 * Responsibilities:
 *   - Represents one XML attribute.
 *   - Stores attribute name/value.
 *   - Links to next attribute.
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

struct XmlAttribute
{
    char *name;

    char *value;

    XmlAttribute *next;
};

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_ATTRIBUTE_H */
