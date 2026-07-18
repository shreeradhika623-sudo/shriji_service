#ifndef SHRIJI_XML_TYPES_H
#define SHRIJI_XML_TYPES_H

#include <stdbool.h>

#include "xml/xml_types.h"

/*
 * ============================================================
 * Shriji XML
 * Common Types
 * ============================================================
 *
 * Purpose:
 *   Defines XML subsystem shared types.
 *
 * Responsibilities:
 *   - Forward declarations
 *   - Shared enums
 *   - Common typedefs
 *
 * Must NOT contain:
 *   - Function declarations
 *   - Parser implementation
 *   - Reader implementation
 *   - Writer implementation
 *   - Business logic
 *   - Error handling logic
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================
 * Forward Declarations
 * ============================================================
 */

typedef struct XmlDocument  XmlDocument;
typedef struct XmlNode      XmlNode;
typedef struct XmlAttribute XmlAttribute;


/*
 * ============================================================
 * Shared Enumerations
 * ============================================================
 */

typedef enum
{
    XML_NODE_ELEMENT,

    XML_NODE_TEXT,

    XML_NODE_COMMENT,

    XML_NODE_CDATA,

    XML_NODE_PROCESSING_INSTRUCTION

} XmlNodeType;

/*
 * ============================================================
 * Shared Type Definitions
 * ============================================================
 */

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_TYPES_H */
