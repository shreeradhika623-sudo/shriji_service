/*
 * ============================================================
 * Shriji Language
 * FFI Marshal API
 * ============================================================
 *
 * Responsibility:
 *   - Argument preparation
 *   - Native value representation
 *   - Return value representation
 *
 * This file MUST NOT contain:
 *   - Function invocation
 *   - Library loading
 *   - Symbol lookup
 *   - Registry logic
 */

#ifndef SHRIJI_FFI_MARSHAL_H
#define SHRIJI_FFI_MARSHAL_H

/* ============================================================
 * Includes
 * ============================================================ */
#include <stddef.h>

#include "ffi_types.h"

#include <stdbool.h>
#include <stdint.h>
#include <x86_64-linux-gnu/ffi.h>

/* ============================================================
 * Marshal Types
 * ============================================================ */

typedef enum FFI_Value_Type
{
    FFI_VALUE_VOID = 0,

    FFI_VALUE_BOOL,

    FFI_VALUE_INT8,
    FFI_VALUE_INT16,
    FFI_VALUE_INT32,
    FFI_VALUE_INT64,

    FFI_VALUE_UINT8,
    FFI_VALUE_UINT16,
    FFI_VALUE_UINT32,
    FFI_VALUE_UINT64,

    FFI_VALUE_FLOAT,
    FFI_VALUE_DOUBLE,

    FFI_VALUE_STRING,

    FFI_VALUE_POINTER

} FFI_Value_Type;


//------------------------------------------------------------

typedef struct FFI_Value
{
    FFI_Value_Type type;

    union
    {
        bool bool_value;

        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;

        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;

        float f32;
        double f64;

        char *str;

        void *ptr;

    } value;

} FFI_Value;


//--------------------------------------------------------------

ffi_type *
ffi_marshal_get_ffi_type(
    FFI_Value_Type type
);


//---------------------------------------------------------------

FFI_Status
ffi_marshal_build_types(
    const FFI_Value *arguments,
    size_t argument_count,
    ffi_type **types
);

//------------------------------------------------------------------

FFI_Status
ffi_marshal_build_values(
    FFI_Value *arguments,
    size_t argument_count,
    void **values
);

//=================================================================

FFI_Status
ffi_marshal_read_result(
    FFI_Value_Type type,
    const void *native_result,
    FFI_Value *out
);
/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_marshal_validate_type(
    FFI_Value_Type type
);

#endif /* SHRIJI_FFI_MARSHAL_H */
