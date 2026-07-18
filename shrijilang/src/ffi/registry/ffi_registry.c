/*
 * ============================================================
 * Shriji Language
 * FFI Registry
 * ============================================================
 */

#include "ffi/ffi_registry.h"

#include "ffi/core/ffi_internal.h"
#include "ffi/core/ffi_registry_internal.h"

/* ============================================================
 * Private Constants
 * ============================================================ */

#define FFI_REGISTRY_MAX_HANDLES 1024

/* ============================================================
 * Private Variables
 * ============================================================ */

static bool registry_initialized = false;

static size_t registry_handle_count = 0;

static FFI_Handle *registry_handles[FFI_REGISTRY_MAX_HANDLES];

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status
ffi_registry_init(void)
{
    if (registry_initialized)
    {
        return FFI_STATUS_SUCCESS;
    }

    registry_initialized = true;

    registry_handle_count = 0;

    return FFI_STATUS_SUCCESS;
}

/* ============================================================
 * Internal API
 * ============================================================ */

FFI_Status
ffi_registry_register(
    FFI_Handle *handle
)
{
    if (handle == NULL)
    {
        return FFI_STATUS_INVALID_ARGUMENT;
    }

    if (!registry_initialized)
    {
        return FFI_STATUS_FAILURE;
    }

    if (handle->active)
 {
    return FFI_STATUS_ALREADY_EXISTS;
    }

for (size_t i = 0; i < FFI_REGISTRY_MAX_HANDLES; i++)
    {
    if (registry_handles[i] == NULL)
    {
        continue;
    }

    if (registry_handles[i]->id == handle->id)
    {
        return FFI_STATUS_ALREADY_EXISTS;
    }
    }

    if (registry_handle_count >= FFI_REGISTRY_MAX_HANDLES)
    {
        return FFI_STATUS_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < FFI_REGISTRY_MAX_HANDLES; i++)
    {
        if (registry_handles[i] == NULL)
        {
            registry_handles[i] = handle;

            handle->active = true;

            registry_handle_count++;

            return FFI_STATUS_SUCCESS;
        }
    }

    return FFI_STATUS_OUT_OF_MEMORY;
}


    FFI_Handle *
ffi_registry_lookup(
    FFI_Handle_ID handle_id
)
{
    if (!registry_initialized)
    {
        return NULL;
    }

    for (size_t i = 0; i < FFI_REGISTRY_MAX_HANDLES; i++)
    {
        if (registry_handles[i] == NULL)
        {
            continue;
        }

        if (registry_handles[i]->id == handle_id)
        {
            return registry_handles[i];
        }
    }

    return NULL;
}

    FFI_Status
ffi_registry_unregister(
    FFI_Handle_ID handle_id
)
{
    if (!registry_initialized)
    {
        return FFI_STATUS_FAILURE;
    }

    for (size_t i = 0; i < FFI_REGISTRY_MAX_HANDLES; i++)
    {
        if (registry_handles[i] == NULL)
        {
            continue;
        }

        if (registry_handles[i]->id == handle_id)
        {
            registry_handles[i]->active = false;

            registry_handles[i] = NULL;

            registry_handle_count--;

            return FFI_STATUS_SUCCESS;
        }
    }

    return FFI_STATUS_NOT_FOUND;
}


void
ffi_registry_shutdown(void)
{
    registry_initialized = false;

    registry_handle_count = 0;
}
