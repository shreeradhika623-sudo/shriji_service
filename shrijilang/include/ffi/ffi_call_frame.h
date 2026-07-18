/*
 * ============================================================
 * Shriji Language
 * FFI Call Frame
 * ============================================================
 *
 * Responsibility:
 *   - Allocate call buffers
 *   - Destroy call buffers
 *   - Hold temporary invoke data
 *
 * This file MUST NOT contain:
 *   - ffi_call()
 *   - Marshal logic
 *   - Loader logic
 *   - Registry logic
 */

#ifndef SHRIJI_FFI_CALL_FRAME_H
#define SHRIJI_FFI_CALL_FRAME_H

/* ============================================================
 * Includes
 * ============================================================ */

#include "ffi_types.h"

#include <stddef.h>
#include <x86_64-linux-gnu/ffi.h>
/* ============================================================
 * Call Frame
 * ============================================================ */

typedef struct FFI_Call_Frame
{
    /* Prepared libffi Call Interface */
    ffi_cif cif;

    /* Argument type table */
    ffi_type **types;

    /* Argument value table */
    void **values;

    /* Number of arguments */
    size_t argument_count;

} FFI_Call_Frame;

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_call_frame_init(
    FFI_Call_Frame *frame,
    size_t argument_count
);

//============================================================

FFI_Status
ffi_call_frame_prepare(
    FFI_Call_Frame *frame,
    ffi_abi abi,
    ffi_type *return_type
);

//==============================================================
void
ffi_call_frame_destroy(
    FFI_Call_Frame *frame
);

#endif
