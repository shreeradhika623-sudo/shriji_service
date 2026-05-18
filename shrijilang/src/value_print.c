#include <stdio.h>
#include "../include/value.h"

static void value_print_inner(Value v)
{
    switch (v.type)
    {
        case VAL_NULL:
            printf("null");
            break;

        case VAL_NUMBER:
            printf("%g", v.number);
            break;

        case VAL_STRING:
            printf("\"%s\"", v.string ? v.string : "");
            break;

        case VAL_BOOL:
            printf("%s", v.boolean ? "true" : "false");
            break;

        case VAL_LIST:
        {
            printf("[");

            for (int i = 0; i < v.count; i++)
            {
                if (i > 0)
                    printf(", ");

                value_print_inner(v.items[i]);
            }

            printf("]");
            break;
        }

        case VAL_DICT:
        {
            printf("{");

            for (int i = 0; i < v.dict_count; i++)
            {
                if (i > 0)
                    printf(", ");

                value_print_inner(v.dict_keys[i]);
                printf(": ");
                value_print_inner(v.dict_values[i]);
            }

            printf("}");
            break;
        }

        case VAL_FUNCTION:
            printf("<function>");
            break;

        default:
            printf("null");
            break;
    }
}

void value_print(Value v)
{
    printf("OUTPUT:\n");
    value_print_inner(v);
    printf("\n");
}

void debug_value_print(Value v)
{
    value_print_inner(v);
}
