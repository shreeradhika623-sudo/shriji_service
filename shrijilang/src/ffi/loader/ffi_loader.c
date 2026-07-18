/*
 * ============================================================
 * Shriji Language
 * FFI Loader
 * ============================================================
 */

#include <dlfcn.h>

#include "ffi/ffi_loader.h"
#include "ffi/ffi_handle.h"

#include "ffi/core/ffi_internal.h"
#include "ffi/core/ffi_registry_internal.h"

/* ============================================================
 * Public API
 * ============================================================ */


FFI_Status
ffi_loader_load(
    const char    *path,
    FFI_Handle_ID *handle_id
)
{
    if (path == NULL || handle_id == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    FFI_Status status = ffi_handle_create(handle_id);

    if (status != FFI_STATUS_SUCCESS)
    {
        return status;
    }

    FFI_Handle *handle = ffi_registry_lookup(*handle_id);

    if (handle == NULL)
    {
        ffi_handle_destroy(*handle_id);

        return FFI_STATUS_INTERNAL_ERROR;
    }

    handle->resource = dlopen(path, RTLD_NOW);

    if (handle->resource == NULL)
    {
        ffi_handle_destroy(*handle_id);

        return FFI_STATUS_FAILURE;
    }

    handle->active = true;

    return FFI_STATUS_SUCCESS;
}



//---------------------------------------------------------

FFI_Status
ffi_loader_unload(
    FFI_Handle_ID handle_id
)
{
    FFI_Handle *handle = ffi_registry_lookup(handle_id);

    if (handle == NULL)
    {
        return FFI_STATUS_NOT_FOUND;
    }

    if (handle->resource == NULL)
    {
        return FFI_STATUS_FAILURE;
    }

    if (dlclose(handle->resource) != 0)
    {
        return FFI_STATUS_FAILURE;
    }

    handle->resource = NULL;
    handle->active = false;

    return ffi_handle_destroy(handle_id);
}


//-----------------------------------------------------------

void *
ffi_loader_symbol(
    FFI_Handle_ID handle_id,
    const char    *symbol
)
{
    if (symbol == NULL)
    {
        return NULL;
    }

    FFI_Handle *handle = ffi_registry_lookup(handle_id);

    if (handle == NULL)
    {
        return NULL;
    }

    if (handle->resource == NULL)
    {
        return NULL;
    }

    return dlsym(handle->resource, symbol);
}


//------------------------------------------------------------

bool
ffi_loader_is_loaded(
    FFI_Handle_ID handle_id
)
{
    FFI_Handle *handle = ffi_registry_lookup(handle_id);

    if (handle == NULL)
    {
        return false;
    }

    return (handle->resource != NULL);
}

//-----------------------------------------------------------
