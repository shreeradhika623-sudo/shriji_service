/*
 * ============================================================
 * Shriji Language
 * FFI Call Frame
 * ============================================================
 */

#include "ffi/ffi_call_frame.h"

#include <stdlib.h>

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_call_frame_init(
    FFI_Call_Frame *frame,
    size_t argument_count
)
{
    if (frame == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    frame->types = NULL;
    frame->values = NULL;
    frame->argument_count = argument_count;

    if (argument_count == 0)
    {
        return FFI_STATUS_SUCCESS;
    }

    frame->types =
        malloc(sizeof(ffi_type *) * argument_count);

    if (frame->types == NULL)
    {
        return FFI_STATUS_OUT_OF_MEMORY;
    }

    frame->values =
        malloc(sizeof(void *) * argument_count);

    if (frame->values == NULL)
    {
        free(frame->types);

        frame->types = NULL;

        return FFI_STATUS_OUT_OF_MEMORY;
    }

    return FFI_STATUS_SUCCESS;
}

//=====================================================================
FFI_Status
ffi_call_frame_prepare(
    FFI_Call_Frame *frame,
    ffi_abi abi,
    ffi_type *return_type
)
{
    ffi_status result;

    if (frame == NULL || return_type == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    result =
        ffi_prep_cif(
            &frame->cif,
            abi,
            (unsigned int)frame->argument_count,
            return_type,
            frame->types
        );

    if (result != FFI_OK)
    {
        return FFI_STATUS_INTERNAL_ERROR;
    }

    return FFI_STATUS_SUCCESS;
}

//=====================================================================
void
ffi_call_frame_destroy(
    FFI_Call_Frame *frame
)
{
    if (frame == NULL)
    {
        return;
    }

    free(frame->types);
    free(frame->values);

    frame->types = NULL;
    frame->values = NULL;
    frame->argument_count = 0;
}

