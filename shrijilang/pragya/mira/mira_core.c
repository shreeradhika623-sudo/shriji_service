// JAI SHREE KRISHNA
#include "mira_contract.h"
#include "../niyu/niyu_contract.h"

#include "../../include/error.h"
#include "../../include/pragya_avastha.h"

#include <string.h>

/* =========================================
   SAFE APPEND
========================================= */
static void append(char *out, const char *text)
{
    if (!out || !text) return;
    strcat(out, text);
}

/* =========================================
   POINTER BUILDER
========================================= */
static void build_pointer(char *out, const char *text, int pos)
{
    if (!out || !text || pos < 0) return;

    append(out, text);
    append(out, "\n");

    for (int i = 0; i < pos; i++)
        append(out, " ");

    append(out, "^\n\n");
}

/* =========================================
   MIRA TEACHING ENGINE (FIXED)
========================================= */
void mira_teach_avastha(PragyaAvastha *a, NiyuResult *res, char *out)
{
    if (!a || !res || !out)
        return;

    const char *text = a->raw_text;

    if (res->error_type == NIYU_ERR_VALID)
        return;

    switch (a->error_code)
    {

    case E_PARSE_DOUBLE_OPERATOR:
    case E_PARSE_OPERATOR_CHAIN:

        append(out, "Extra operator detect hua hai\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "Do operators ek saath allowed nahi hote.\n\n");
        append(out, "Example: 6 + 5\n");

        break;

    case E_PARSE_OPERATOR_START:

        append(out, "Expression operator se start nahi hota\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "Pehle ek value honi chahiye.\n\n");
        append(out, "Example: 6 + 5\n");

        break;

    case E_PARSE_OPERATOR_END:

        append(out, "Expression incomplete lag raha hai\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "Operator ke baad ek value expected hoti hai.\n\n");
        append(out, "Example: 6 + 5\n");

        break;

    case E_PARSE_MISSING_OPERATOR:

        append(out, "Operator missing hai\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "Do values ke beech operator hona chahiye.\n\n");
        append(out, "Example: 5 + 6\n");

        break;

    case E_ASSIGN_02:

        append(out, "Assignment incomplete hai\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "'=' ke baad value expected hai.\n\n");
        append(out, "Example: mavi x = 10\n");

        break;

    case E_PARSE_02:

        append(out, "Syntax error detect hua hai\n\n");
        build_pointer(out, text, res->error_pos);
        append(out, "Invalid token ya unsupported symbol mila hai.\n\n");
        append(out, "Example: 6 + 5\n");

        break;

    default:
        return;
    }
}
