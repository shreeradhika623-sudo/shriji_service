/*
 * ============================================================
 * Shriji Language
 * FFI Internal Registry API
 * ============================================================
 *
 * Responsibility:
 *   - Internal registry operations
 *
 * This file is PRIVATE.
 * It MUST NOT be included outside the FFI implementation.
 */

#ifndef SHRIJI_FFI_REGISTRY_INTERNAL_H
#define SHRIJI_FFI_REGISTRY_INTERNAL_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_internal.h"

/* ============================================================
 * Internal API
 * ============================================================ */

FFI_Status
ffi_registry_register(
    FFI_Handle *handle
);

FFI_Handle *
ffi_registry_lookup(
    FFI_Handle_ID handle_id
);

FFI_Status
ffi_registry_unregister(
    FFI_Handle_ID handle_id
);

#endif /* SHRIJI_FFI_REGISTRY_INTERNAL_H */
