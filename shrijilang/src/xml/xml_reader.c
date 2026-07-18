/*
 * ============================================================
 * Shriji XML
 * XML Reader
 * ============================================================
 */

#include <stdio.h>

#include "xml/xml_reader.h"

void
xml_reader_init(
    XmlReader *reader,
    const char *buffer,
    size_t length
)
{
    reader->buffer = buffer;
    reader->length = length;
    reader->position = 0;
}

void
xml_reader_reset(
    XmlReader *reader
)
{
    reader->position = 0;
}

int
xml_reader_eof(
    const XmlReader *reader
)
{
    return reader->position >= reader->length;
}

int
xml_reader_peek(
    XmlReader *reader
)
{
    if (xml_reader_eof(reader))
    {
        return EOF;
    }

    return (unsigned char)reader->buffer[reader->position];
}

int
xml_reader_next(
    XmlReader *reader
)
{
    if (xml_reader_eof(reader))
    {
        return EOF;
    }

    return (unsigned char)reader->buffer[reader->position++];
}
