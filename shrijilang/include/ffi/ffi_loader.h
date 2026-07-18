/*
 * ============================================================
 * Shriji Language
 * FFI Loader API
 * ============================================================
 *
 * Responsibility:
 *   - Dynamic library loading
 *   - Dynamic library unloading
 *   - Symbol lookup
 *   - Library validation
 *
 * Dependencies:
 *   - ffi_types.h
 *   - ffi_ids.h
 *
 * This file MUST NOT contain:
 *   - Loader implementation
 *   - Registry implementation
 *   - Handle implementation
 *   - Adapter logic
 *   - SQLite dependencies
 */

#ifndef SHRIJI_FFI_LOADER_H
#define SHRIJI_FFI_LOADER_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_types.h"
#include "ffi_ids.h"

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_loader_load(
    const char    *path,
    FFI_Handle_ID *handle_id
);

FFI_Status
ffi_loader_unload(
    FFI_Handle_ID handle_id
);

void *
ffi_loader_symbol(
    FFI_Handle_ID handle_id,
    const char    *symbol
);

bool
ffi_loader_is_loaded(
    FFI_Handle_ID handle_id
);

#endif /* SHRIJI_FFI_LOADER_H */
