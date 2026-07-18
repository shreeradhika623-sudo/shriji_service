/*
 * ============================================================
 * Shriji Language
 * FFI Adapter
 *
 * Responsibility:
 *     Convert Shriji Value and FFI Value.
 * ============================================================
 */

#include "ffi/ffi_adapter.h"

#include "value.h"


FFI_Status
ffi_adapter_value_to_ffi(
    const Value *value,
    FFI_Value *out
)
{
    if (!value || !out)
        return FFI_STATUS_INVALID_ARGUMENT;


    switch (value->type)
    {

        case VAL_NUMBER:

            out->type = FFI_VALUE_DOUBLE;
            out->value.f64 = value->number;

            return FFI_STATUS_SUCCESS;


        case VAL_INT:

            out->type = FFI_VALUE_INT64;
            out->value.i64 = value->integer;

            return FFI_STATUS_SUCCESS;


        case VAL_BOOL:

            out->type = FFI_VALUE_BOOL;
            out->value.bool_value = value->boolean;

            return FFI_STATUS_SUCCESS;


        case VAL_STRING:

            out->type = FFI_VALUE_STRING;
            out->value.str = value->string;

            return FFI_STATUS_SUCCESS;


        default:

            return FFI_STATUS_NOT_SUPPORTED;
    }
}


//=================================================================

FFI_Status
ffi_adapter_ffi_to_value(
    const FFI_Value *input,
    Value *out
)
{
    if (!input || !out)
        return FFI_STATUS_INVALID_ARGUMENT;


    switch (input->type)
    {

        case FFI_VALUE_DOUBLE:

            *out = value_number(
                input->value.f64
            );

            return FFI_STATUS_SUCCESS;


        case FFI_VALUE_INT64:

            *out = value_int(
                input->value.i64
            );

            return FFI_STATUS_SUCCESS;


        case FFI_VALUE_BOOL:

            *out = value_bool(
                input->value.bool_value
            );

            return FFI_STATUS_SUCCESS;


        case FFI_VALUE_STRING:

            *out = value_string(
                input->value.str
            );

            return FFI_STATUS_SUCCESS;


        default:

            return FFI_STATUS_NOT_SUPPORTED;
    }
}
