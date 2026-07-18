/*
 * ============================================================
 * Shriji Language
 * FFI Identifier Types
 * ============================================================
 *
 * Responsibility:
 *   - Strongly typed FFI identifiers
 *
 * Dependencies:
 *   - ffi_base.h
 *
 * This file MUST NOT contain:
 *   - Object definitions
 *   - Registry logic
 *   - Runtime dependencies
 *   - SQLite dependencies
 */

#ifndef SHRIJI_FFI_IDS_H
#define SHRIJI_FFI_IDS_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_base.h"

/* ============================================================
 * Identifier Types
 * ============================================================ */

typedef uint64_t FFI_Handle_ID;
typedef uint64_t FFI_Module_ID;
typedef uint64_t FFI_Adapter_ID;
typedef uint64_t FFI_Capability_ID;
typedef uint64_t FFI_Callback_ID;
typedef uint64_t FFI_Thread_ID;
typedef uint64_t FFI_Session_ID;

#endif /* SHRIJI_FFI_IDS_H */
