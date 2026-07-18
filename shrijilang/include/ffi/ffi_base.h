/*
 * ============================================================
 * Shriji Language
 * FFI Base Definitions
 * ============================================================
 *
 * Responsibility:
 *   - Standard C includes
 *   - Compiler detection
 *   - Platform detection
 *   - Visibility macros
 *   - Common utility macros
 *
 * This file MUST NOT contain:
 *   - FFI types
 *   - Handles
 *   - Registry
 *   - Adapter logic
 *   - Runtime dependencies
 *   - SQLite dependencies
 */

#ifndef SHRIJI_FFI_BASE_H
#define SHRIJI_FFI_BASE_H

/* ============================================================
 * Standard C
 * ============================================================ */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ============================================================
 * Compiler Detection
 * ============================================================ */

#if defined(__clang__)
    #define SHRIJI_COMPILER_CLANG 1

#elif defined(__GNUC__)
    #define SHRIJI_COMPILER_GCC 1

#elif defined(_MSC_VER)
    #define SHRIJI_COMPILER_MSVC 1

#else
    #error "Unsupported compiler."
#endif

/* ============================================================
 * Platform Detection
 * ============================================================ */

#if defined(_WIN32)

    #define SHRIJI_PLATFORM_WINDOWS 1

#elif defined(__linux__)

    #define SHRIJI_PLATFORM_LINUX 1

#elif defined(__APPLE__)

    #define SHRIJI_PLATFORM_MACOS 1

#else
    #error "Unsupported platform."
#endif

/* ============================================================
 * Symbol Visibility
 * ============================================================ */

#if defined(_WIN32)

    #define SHRIJI_FFI_EXPORT __declspec(dllexport)
    #define SHRIJI_FFI_IMPORT __declspec(dllimport)

#else

    #define SHRIJI_FFI_EXPORT __attribute__((visibility("default")))
    #define SHRIJI_FFI_IMPORT

#endif

/* ============================================================
 * Common Helpers
 * ============================================================ */

#define SHRIJI_UNUSED(x) ((void)(x))

#endif /* SHRIJI_FFI_BASE_H */
