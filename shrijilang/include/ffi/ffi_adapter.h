#ifndef SHRIJI_FFI_ADAPTER_H
#define SHRIJI_FFI_ADAPTER_H


#include "ffi/ffi_marshal.h"


typedef struct Value Value;


FFI_Status
ffi_adapter_value_to_ffi(
    const Value *value,
    FFI_Value *out
);


FFI_Status
ffi_adapter_ffi_to_value(
    const FFI_Value *input,
    Value *out
);


#endif
