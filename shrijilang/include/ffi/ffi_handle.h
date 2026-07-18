/*
 * ============================================================
 * Shriji Language
 * FFI Handle API
 * ============================================================
 *
 * Responsibility:
 *   - Handle lifecycle
 *   - Handle validation
 *
 * Dependencies:
 *   - ffi_types.h
 *   - ffi_ids.h
 *
 * This file MUST NOT contain:
 *   - Handle implementation
 *   - Registry
 *   - Adapter logic
 *   - SQLite dependencies
 */

#ifndef SHRIJI_FFI_HANDLE_H
#define SHRIJI_FFI_HANDLE_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_types.h"
#include "ffi_ids.h"

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_handle_create(
    FFI_Handle_ID *handle_id
);

FFI_Status
ffi_handle_destroy(
    FFI_Handle_ID handle_id
);

bool
ffi_handle_is_valid(
    FFI_Handle_ID handle_id
);

#endif /* SHRIJI_FFI_HANDLE_H */
