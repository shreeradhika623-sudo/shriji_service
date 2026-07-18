/*
 * ============================================================
 * Shriji Language
 * FFI Version
 * ============================================================
 *
 * Responsibility:
 *   - FFI version definitions
 *   - Version compatibility
 *
 * Dependencies:
 *   - ffi_base.h
 *
 * This file MUST NOT contain:
 *   - Registry
 *   - Handles
 *   - Adapter logic
 *   - Runtime dependencies
 */

#ifndef SHRIJI_FFI_VERSION_H
#define SHRIJI_FFI_VERSION_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_base.h"

/* ============================================================
 * Version
 * ============================================================ */

typedef struct FFI_Version
{
    uint32_t major;
    uint32_t minor;
    uint32_t patch;

} FFI_Version;

#endif /* SHRIJI_FFI_VERSION_H */
