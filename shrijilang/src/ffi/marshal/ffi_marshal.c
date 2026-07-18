/*
 * ============================================================
 * Shriji Language
 * FFI Marshal Implementation
 * ============================================================
 */

#include <stdio.h>
#include "ffi/ffi_marshal.h"

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_marshal_validate_type(
    FFI_Value_Type type
)
{
    switch (type)
{
    case FFI_VALUE_VOID:

    case FFI_VALUE_BOOL:

    case FFI_VALUE_INT8:
    case FFI_VALUE_INT16:
    case FFI_VALUE_INT32:
    case FFI_VALUE_INT64:

    case FFI_VALUE_UINT8:
    case FFI_VALUE_UINT16:
    case FFI_VALUE_UINT32:
    case FFI_VALUE_UINT64:

    case FFI_VALUE_FLOAT:
    case FFI_VALUE_DOUBLE:

    case FFI_VALUE_STRING:

    case FFI_VALUE_POINTER:

        return FFI_STATUS_SUCCESS;

    default:

        return FFI_STATUS_INVALID_ARGUMENT;
    }
}

    ffi_type *
ffi_marshal_get_ffi_type(
    FFI_Value_Type type
)
{
    switch (type)
    {
        case FFI_VALUE_VOID:
            return &ffi_type_void;

        case FFI_VALUE_BOOL:
            return &ffi_type_uint8;

        case FFI_VALUE_INT8:
            return &ffi_type_sint8;

        case FFI_VALUE_INT16:
            return &ffi_type_sint16;

        case FFI_VALUE_INT32:
            return &ffi_type_sint32;

        case FFI_VALUE_INT64:
            return &ffi_type_sint64;

        case FFI_VALUE_UINT8:
            return &ffi_type_uint8;

        case FFI_VALUE_UINT16:
            return &ffi_type_uint16;

        case FFI_VALUE_UINT32:
            return &ffi_type_uint32;

        case FFI_VALUE_UINT64:
            return &ffi_type_uint64;

        case FFI_VALUE_FLOAT:
            return &ffi_type_float;

        case FFI_VALUE_DOUBLE:
            return &ffi_type_double;

        case FFI_VALUE_STRING:
            return &ffi_type_pointer;

        case FFI_VALUE_POINTER:
            return &ffi_type_pointer;

        default:
            return NULL;
    }
}

//-----------------------------------------------------------------

FFI_Status
ffi_marshal_build_types(
    const FFI_Value *arguments,
    size_t argument_count,
    ffi_type **types
)
    {
    if (argument_count == 0)
    {
    return FFI_STATUS_SUCCESS;
    }

    if (types == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (arguments == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }


    if (arguments == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < argument_count; ++i)
    {
        types[i] = ffi_marshal_get_ffi_type(arguments[i].type);

        if (types[i] == NULL)
        {
            return FFI_STATUS_INVALID_ARGUMENT;
        }
    }

    return FFI_STATUS_SUCCESS;
}

//--------------------------------------------------------------

FFI_Status
ffi_marshal_build_values(
    FFI_Value *arguments,
    size_t argument_count,
    void **values
    )
    {

    if (argument_count == 0)
    {
        return FFI_STATUS_SUCCESS;
    }

    if (values == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (arguments == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < argument_count; ++i)
    {
        switch (arguments[i].type)
        {
            case FFI_VALUE_BOOL:
                values[i] = &arguments[i].value.bool_value;
                break;

            case FFI_VALUE_INT8:
                values[i] = &arguments[i].value.i8;
                break;

            case FFI_VALUE_INT16:
                values[i] = &arguments[i].value.i16;
                break;

            case FFI_VALUE_INT32:
                values[i] = &arguments[i].value.i32;
                break;

            case FFI_VALUE_INT64:
                values[i] = &arguments[i].value.i64;
                break;

            case FFI_VALUE_UINT8:
                values[i] = &arguments[i].value.u8;
                break;

            case FFI_VALUE_UINT16:
                values[i] = &arguments[i].value.u16;
                break;

            case FFI_VALUE_UINT32:
                values[i] = &arguments[i].value.u32;
                break;

            case FFI_VALUE_UINT64:
                values[i] = &arguments[i].value.u64;
                break;

            case FFI_VALUE_FLOAT:
                values[i] = &arguments[i].value.f32;
                break;

            case FFI_VALUE_DOUBLE:
                values[i] = &arguments[i].value.f64;
                break;

            case FFI_VALUE_STRING:
                values[i] = &arguments[i].value.str;
                break;

            case FFI_VALUE_POINTER:
                values[i] = &arguments[i].value.ptr;
                break;

            case FFI_VALUE_VOID:
            default:
                return FFI_STATUS_INVALID_ARGUMENT;
        }
    }

    return FFI_STATUS_SUCCESS;
}

//=================================================================

FFI_Status
ffi_marshal_read_result(
    FFI_Value_Type type,
    const void *native_result,
    FFI_Value *out
)
{
    if (out == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (type == FFI_VALUE_VOID)
    {
        out->type = FFI_VALUE_VOID;
        return FFI_STATUS_SUCCESS;
    }

    if (native_result == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }


    out->type = type;


    switch (type)
    {
        case FFI_VALUE_BOOL:
            out->value.bool_value =
                *(const bool *)native_result;
            break;


        case FFI_VALUE_INT8:
            out->value.i8 =
                *(const int8_t *)native_result;
            break;


        case FFI_VALUE_INT16:
            out->value.i16 =
                *(const int16_t *)native_result;
            break;


        case FFI_VALUE_INT32:
            out->value.i32 =
                *(const int32_t *)native_result;
            break;


        case FFI_VALUE_INT64:
            out->value.i64 =
                *(const int64_t *)native_result;
            break;


        case FFI_VALUE_UINT8:
            out->value.u8 =
                *(const uint8_t *)native_result;
            break;


        case FFI_VALUE_UINT16:
            out->value.u16 =
                *(const uint16_t *)native_result;
            break;


        case FFI_VALUE_UINT32:
            out->value.u32 =
                *(const uint32_t *)native_result;
            break;


        case FFI_VALUE_UINT64:
            out->value.u64 =
                *(const uint64_t *)native_result;
            break;


        case FFI_VALUE_FLOAT:
            out->value.f32 =
                *(const float *)native_result;
            break;


        case FFI_VALUE_DOUBLE:
            out->value.f64 =
                *(const double *)native_result;
            break;


        case FFI_VALUE_STRING:
        case FFI_VALUE_POINTER:

            out->value.ptr =
                *(void * const *)native_result;

            break;


        default:
            return FFI_STATUS_NOT_SUPPORTED;
    }


    return FFI_STATUS_SUCCESS;
}


//---------------------------------------------------------------

