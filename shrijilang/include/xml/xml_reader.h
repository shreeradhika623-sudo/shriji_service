#ifndef SHRIJI_XML_READER_H
#define SHRIJI_XML_READER_H

/*
 * ============================================================
 * Shriji XML
 * XML Reader
 * ============================================================
 *
 * Purpose:
 *   Reads XML data from a source into memory.
 *
 * Responsibilities:
 *   - Open XML source
 *   - Read XML content
 *   - Close XML source
 *
 * Must NOT contain:
 *   - Tokenizer logic
 *   - Parser logic
 *   - Tree building
 *   - Writer logic
 *   - Error printing
 *
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct XmlReader
{
    const char *buffer;

    size_t length;

    size_t position;

} XmlReader;

/*
 * ============================================================
 * XML Reader API
 * ============================================================
 */

void
xml_reader_init(
    XmlReader *reader,
    const char *buffer,
    size_t length
);

void
xml_reader_reset(
    XmlReader *reader
);

int
xml_reader_peek(
    XmlReader *reader
);

int
xml_reader_next(
    XmlReader *reader
);

int
xml_reader_eof(
    const XmlReader *reader
);

#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_XML_READER_H */
