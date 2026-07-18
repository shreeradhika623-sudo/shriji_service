/*
 * ============================================================
 * Shriji Language
 * FFI Handle Manager
 * ============================================================
 */

#include <stdlib.h>

#include "ffi/core/ffi_internal.h"
#include "ffi/core/ffi_registry_internal.h"
#include "ffi/ffi_handle.h"

/* ============================================================
 * Private Variables
 * ============================================================ */

static FFI_Handle_ID next_handle_id = 1;

/* ============================================================
 * Public API
 * ============================================================ */

FFI_Status ffi_handle_create(FFI_Handle_ID *handle_id) {
  if (handle_id == NULL) {
    return FFI_STATUS_INVALID_ARGUMENT;
  }

  FFI_Handle *handle = malloc(sizeof(FFI_Handle));

  if (handle == NULL) {
    return FFI_STATUS_OUT_OF_MEMORY;
  }

  handle->id = 0;
  handle->resource = NULL;
  handle->adapter_id = 0;
  handle->flags = 0;
  handle->active = false;

  handle->id = next_handle_id;
  next_handle_id++;

  FFI_Status status = ffi_registry_register(handle);

  if (status != FFI_STATUS_SUCCESS) {
    free(handle);
    return status;
  }

  *handle_id = handle->id;

  return FFI_STATUS_SUCCESS;
}

FFI_Status ffi_handle_destroy(FFI_Handle_ID handle_id) {

  FFI_Handle *handle = ffi_registry_lookup(handle_id);

  if (handle == NULL) {
    return FFI_STATUS_NOT_FOUND;
  }

  FFI_Status status = ffi_registry_unregister(handle_id);

  if (status != FFI_STATUS_SUCCESS) {
    return status;
  }

  free(handle);

  return FFI_STATUS_SUCCESS;
}

bool ffi_handle_is_valid(FFI_Handle_ID handle_id) {
  FFI_Handle *handle = ffi_registry_lookup(handle_id);

  if (handle == NULL) {
    return false;
  }

  return handle->active;
}
