/*
 * ============================================================
 * Shriji Language
 * FFI Internal Definitions
 * ============================================================
 *
 * Responsibility:
 *   - Internal FFI structures
 *   - Shared implementation definitions
 *
 * This file is PRIVATE.
 * It MUST NOT be included outside the FFI implementation.
 */

#ifndef SHRIJI_FFI_INTERNAL_H
#define SHRIJI_FFI_INTERNAL_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi/ffi_base.h"
#include "ffi/ffi_ids.h"
#include "ffi/ffi_types.h"

/* ============================================================
 * Internal Types
 * ============================================================ */

typedef struct FFI_Handle
{
    FFI_Handle_ID id;

    void *resource;

    uint32_t adapter_id;

    FFI_Flags flags;

    bool active;

} FFI_Handle;


#endif /* SHRIJI_FFI_INTERNAL_H */
