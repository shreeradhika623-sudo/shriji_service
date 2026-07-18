/*
 * ============================================================
 * Shriji Language
 * FFI Invoke
 * ============================================================
 */

#ifndef SHRIJI_FFI_INVOKE_H
#define SHRIJI_FFI_INVOKE_H

//----------------------------------------------------------------

#include "ffi_types.h"
#include "ffi/ffi_abi.h"
#include "ffi/ffi_marshal.h"

#include <stddef.h>


//-----------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------

typedef struct FFI_Call
{
    void *function;

    FFI_ABI_Type abi;

    FFI_Value_Type return_type;

    size_t argument_count;

    FFI_Value *arguments;

} FFI_Call;


/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_invoke(
    const FFI_Call *call,
    void *result
);


//------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif
