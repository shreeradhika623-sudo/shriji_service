#ifndef SHRIJI_XML_NODE_H
#define SHRIJI_XML_NODE_H

/*
 * ============================================================
 * Shriji XML
 * XML Node
 * ============================================================
 *
 * Purpose:
 *   Defines the XML node data model.
 *
 * Responsibilities:
 *   - Represents one XML node.
 *   - Owns child relationships.
 *   - Owns attribute relationships.
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
 * XML Node
 * ============================================================
 */

struct XmlNode
{
    /* Node Identity */
    XmlNodeType type;

    /* Tree Relationships */
    XmlNode *parent;
    XmlNode *first_child;
    XmlNode *next_sibling;

    /* Attribute List */
    XmlAttribute *first_attribute;

    /* Node Data */
    char *name;
    char *value;
};


#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_NODE_H */
