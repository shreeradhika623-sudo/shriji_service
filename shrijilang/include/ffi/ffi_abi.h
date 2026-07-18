/*
 * ============================================================
 * Shriji Language
 * FFI ABI Definition
 * ============================================================
 *
 * Responsibility:
 *   - ABI information
 *   - Calling convention definitions
 *   - Platform compatibility
 *
 * This file MUST NOT contain:
 *   - Function invocation
 *   - Argument marshaling
 *   - Loader logic
 *   - Registry logic
 */

#ifndef SHRIJI_FFI_ABI_H
#define SHRIJI_FFI_ABI_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_types.h"
#include <x86_64-linux-gnu/ffi.h>

/* ============================================================
 * ABI Types
 * ============================================================ */

typedef enum FFI_ABI_Type
{
    FFI_ABI_DEFAULT = 0,

    FFI_ABI_CDECL,

    FFI_ABI_SYSV

} FFI_ABI_Type;

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_abi_validate(
    FFI_ABI_Type abi
);

//==============================================================

ffi_abi
ffi_abi_to_libffi(
    FFI_ABI_Type abi
);

//===============================================================

#endif /* SHRIJI_FFI_ABI_H */
