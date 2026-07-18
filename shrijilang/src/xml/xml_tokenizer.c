/*
 * ============================================================
 * Shriji XML
 * XML Tokenizer
 * ============================================================
 */

#include "xml/xml_tokenizer.h"

#include <ctype.h>

/*
 * ============================================================
 * Character Classification Helpers
 * ============================================================
 */

static int
xml_is_identifier_start(
    int ch
)
{
    return
        isalpha(ch) ||
        ch == '_';
}

static int
xml_is_identifier_part(
    int ch
)
{
    return
        isalnum(ch) ||
        ch == '_' ||
        ch == '-' ||
        ch == '.';
}

/*
 * ============================================================
 * Tokenizer Initialization
 * ============================================================
 */

void
xml_tokenizer_init(
    XmlTokenizer *tokenizer,
    XmlReader *reader
)
{
    tokenizer->reader = reader;

    tokenizer->line = 1;

    tokenizer->column = 1;

    tokenizer->token.type = XML_TOKEN_UNKNOWN;

    tokenizer->token.start = NULL;

    tokenizer->token.length = 0;

    tokenizer->token.line = 1;

    tokenizer->token.column = 1;
}

/*
 * ============================================================
 * Tokenizer Reset
 * ============================================================
 */

void
xml_tokenizer_reset(
    XmlTokenizer *tokenizer
)
{
    xml_reader_reset(
        tokenizer->reader
    );

    tokenizer->line = 1;

    tokenizer->column = 1;

    tokenizer->token.type = XML_TOKEN_UNKNOWN;

    tokenizer->token.start = NULL;

    tokenizer->token.length = 0;

    tokenizer->token.line = 1;

    tokenizer->token.column = 1;
}

/*
 * ============================================================
 * Next Token Scanner
 * ============================================================
 */

const XmlToken *
xml_tokenizer_next(
    XmlTokenizer *tokenizer
)
{
    if (
        xml_reader_eof(
            tokenizer->reader
        )
    )
    {
        tokenizer->token.type = XML_TOKEN_EOF;

        tokenizer->token.start = NULL;

        tokenizer->token.length = 0;

        tokenizer->token.line = tokenizer->line;

        tokenizer->token.column = tokenizer->column;

        return &tokenizer->token;
    }

    tokenizer->token.type = XML_TOKEN_UNKNOWN;

    tokenizer->token.start =
        tokenizer->reader->buffer +
        tokenizer->reader->position;

    tokenizer->token.length = 1;

    tokenizer->token.line = tokenizer->line;

    tokenizer->token.column = tokenizer->column;

    if (
        xml_is_identifier_start(
            *tokenizer->token.start
        )
    )
    {
        while (
            !xml_reader_eof(
                tokenizer->reader
            ) &&
            xml_is_identifier_part(
                xml_reader_peek(
                    tokenizer->reader
                )
            )
        )
        {
            xml_reader_next(
                tokenizer->reader
            );

            tokenizer->column++;

            tokenizer->token.length++;
        }

        tokenizer->token.type =
            XML_TOKEN_IDENTIFIER;

        return &tokenizer->token;
    }

    switch (
        *tokenizer->token.start
    )
    {
        case '<':

            tokenizer->token.type =
                XML_TOKEN_OPEN_TAG;

            break;

        case '>':

            tokenizer->token.type =
                XML_TOKEN_CLOSE_TAG;

            break;

        case '/':

            tokenizer->token.type =
                XML_TOKEN_SLASH;

            break;

        case '=':

            tokenizer->token.type =
                XML_TOKEN_EQUALS;

            break;

        default:

            tokenizer->token.type =
                XML_TOKEN_UNKNOWN;

            break;
    }

    xml_reader_next(
        tokenizer->reader
    );

    tokenizer->column++;

    return &tokenizer->token;
}
