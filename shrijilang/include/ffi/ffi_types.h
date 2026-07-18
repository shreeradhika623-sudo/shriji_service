/*
 * ============================================================
 * Shriji Language
 * FFI Common Types
 * ============================================================
 *
 * Responsibility:
 *   - Common FFI types
 *   - Status definitions
 *   - Forward declarations
 *
 * Dependencies:
 *   - ffi_base.h
 *
 * This file MUST NOT contain:
 *   - Registry
 *   - Handles
 *   - Adapter logic
 *   - Runtime types
 *   - SQLite types
 */

#ifndef SHRIJI_FFI_TYPES_H
#define SHRIJI_FFI_TYPES_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_base.h"

/* ============================================================
 * Status
 * ============================================================ */

typedef enum FFI_Status
{
    FFI_STATUS_SUCCESS = 0,
    FFI_STATUS_FAILURE,

    FFI_STATUS_INVALID_ARGUMENT,
    FFI_STATUS_INVALID_HANDLE,

    FFI_STATUS_NOT_FOUND,
    FFI_STATUS_ALREADY_EXISTS,

    FFI_STATUS_NOT_INITIALIZED,

    FFI_STATUS_NOT_SUPPORTED,

    FFI_STATUS_OUT_OF_MEMORY,

    FFI_STATUS_INTERNAL_ERROR

} FFI_Status;

/* ============================================================
 * Forward Declarations
 * ============================================================ */

typedef struct FFI_Handle      FFI_Handle;
typedef struct FFI_Context     FFI_Context;
typedef struct FFI_Adapter     FFI_Adapter;
typedef struct FFI_Module      FFI_Module;
typedef struct FFI_Registry    FFI_Registry;
typedef struct FFI_Callback    FFI_Callback;
typedef struct FFI_Thread      FFI_Thread;
typedef struct FFI_Marshal     FFI_Marshal;
typedef struct FFI_ABI         FFI_ABI;

/* ============================================================
 * Common Types
 * ============================================================ */

typedef uint32_t FFI_Flags;
typedef uint32_t FFI_Size;

#endif /* SHRIJI_FFI_TYPES_H */
