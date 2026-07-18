/*
 * ============================================================
 * Shriji Language
 * FFI ABI Implementation
 * ============================================================
 */

#include "ffi/ffi_invoke.h"
#include "ffi/core/ffi_internal.h"
#include "ffi/ffi_marshal.h"


/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_abi_validate(
    FFI_ABI_Type abi
)
{
    switch (abi)
    {
        case FFI_ABI_DEFAULT:
        case FFI_ABI_CDECL:
        case FFI_ABI_SYSV:

            return FFI_STATUS_SUCCESS;

        default:

            return FFI_STATUS_INVALID_ARGUMENT;
    }
}

//==================================================================

ffi_abi
ffi_abi_to_libffi(
    FFI_ABI_Type abi
)
{
    switch (abi)
    {
        case FFI_ABI_DEFAULT:
            return FFI_DEFAULT_ABI;

#if defined(__i386__) || defined(_M_IX86)

        case FFI_ABI_CDECL:
            return FFI_DEFAULT_ABI;

#endif

#ifdef FFI_SYSV

        case FFI_ABI_SYSV:
            return FFI_SYSV;

#endif

        default:
            return FFI_DEFAULT_ABI;
    }
}

//================================================================
