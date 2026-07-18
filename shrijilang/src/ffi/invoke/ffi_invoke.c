/*
 * ============================================================
 * Shriji Language
 * FFI Invoke
 * ============================================================
 */

#include <stdio.h>

#include "ffi/ffi_invoke.h"

#include "ffi/core/ffi_internal.h"
#include "ffi/ffi_marshal.h"
#include "ffi/ffi_call_frame.h"

#include <x86_64-linux-gnu/ffi.h>

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_invoke(
        const FFI_Call *call,
        void *result
    )
    {
        FFI_Status status;

        FFI_Call_Frame frame;


    /* --------------------------------------------------------
     * Validate Input
     * -------------------------------------------------------- */

    if (call == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (call->function == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (call->argument_count > 0 &&
        call->arguments == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (result == NULL &&
        call->return_type != FFI_VALUE_VOID)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    /* --------------------------------------------------------
 * Initialize Call Frame
 * -------------------------------------------------------- */

    status = ffi_call_frame_init(
        &frame,
        call->argument_count
    );

    if (status != FFI_STATUS_SUCCESS)
    {
        return status;
    }

    /* --------------------------------------------------------
     * Build Argument Types
     * -------------------------------------------------------- */

    status = ffi_marshal_build_types(
        call->arguments,
        call->argument_count,
        frame.types
    );


    if (status != FFI_STATUS_SUCCESS)
    {
        ffi_call_frame_destroy(&frame);
        return status;
    }
//------------------------------------------------------------

ffi_type *return_type;

return_type =
    ffi_marshal_get_ffi_type(
        call->return_type
    );

if (return_type == NULL)
{
    ffi_call_frame_destroy(&frame);
    return FFI_STATUS_INVALID_ARGUMENT;
}

//-----------------------------------------------------------=

status =
    ffi_call_frame_prepare(
        &frame,
        ffi_abi_to_libffi(call->abi),
        return_type
    );

if (status != FFI_STATUS_SUCCESS)
{
    ffi_call_frame_destroy(&frame);
    return status;
}


/* --------------------------------------------------------
 * Build Argument Values
 * -------------------------------------------------------- */

status =
    ffi_marshal_build_values(
        call->arguments,
        call->argument_count,
        frame.values
    );

if (status != FFI_STATUS_SUCCESS)
{
    ffi_call_frame_destroy(&frame);
    return status;
}

//==============================================================

/* --------------------------------------------------------
 * Native Call
 * -------------------------------------------------------- */

ffi_call(
    &frame.cif,
    (void (*)(void))call->function,
    result,
    frame.values
);


ffi_call_frame_destroy(&frame);

return FFI_STATUS_SUCCESS;

}

//---------------------------------------------------------------
