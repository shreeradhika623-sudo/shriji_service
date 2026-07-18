/*
 * ============================================================
 * Shriji Language
 * Foreign Function Interface (FFI)
 *
 * Public API
 *
 * Responsibility:
 *     Public entry point for the complete FFI subsystem.
 *
 * This file DOES NOT:
 *     - load libraries
 *     - resolve symbols
 *     - call libffi
 *     - convert types
 *
 * It only exposes the public interface used by the interpreter.
 * ============================================================
 */

#ifndef SHRIJI_FFI_H
#define SHRIJI_FFI_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Required Types
 * ============================================================
 */

#include "value.h"
#include "runtime.h"


/* ============================================================
 * Opaque Handle
 * ============================================================
 */

typedef struct ShrijiFFI ShrijiFFI;


/* ============================================================
 * Lifecycle
 * ============================================================
 */

/*
 * Create a new FFI context.
 */
ShrijiFFI *ffi_create(void);

/*
 * Destroy an FFI context.
 */
void ffi_destroy(ShrijiFFI *ffi);


/* ============================================================
 * Library Management
 * ============================================================
 */

/*
 * Load a native library.
 */
int ffi_load_library(
    ShrijiFFI *ffi,
    const char *path
);

/*
 * Unload a native library.
 */
int ffi_unload_library(
    ShrijiFFI *ffi,
    const char *path
);


/* ============================================================
 * Function Invocation
 * ============================================================
 */

/*
 * Invoke a native function.
 */
Value ffi_call(
    ShrijiFFI *ffi,
    ShrijiRuntime *runtime,
    const char *library,
    const char *function
);


#ifdef __cplusplus
}
#endif

#endif /* SHRIJI_FFI_H */
