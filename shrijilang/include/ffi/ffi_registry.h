/*
 * ============================================================
 * Shriji Language
 * FFI Registry
 * ============================================================
 *
 * Responsibility:
 *   - Handle registration
 *   - Handle lookup
 *   - Handle removal
 *
 * This file MUST NOT contain:
 *   - SQLite code
 *   - Adapter code
 *   - Runtime logic
 */

#ifndef SHRIJI_FFI_REGISTRY_H
#define SHRIJI_FFI_REGISTRY_H

#include "ffi/ffi_types.h"
#include "ffi/ffi_ids.h"

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_registry_init(void);

void
ffi_registry_shutdown(void);

#endif /* SHRIJI_FFI_REGISTRY_H */
