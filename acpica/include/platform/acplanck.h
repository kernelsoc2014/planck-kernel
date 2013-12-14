#pragma once

#include "acgcc.h"
#include <stdint.h>

#define ACPI_MACHINE_WIDTH 64

#define COMPILER_DEPENDENT_INT64        int64_t
#define COMPILER_DEPENDENT_UINT64       uint64_t

#define ACPI_UINTPTR_T      uintptr_t

#define ACPI_USE_DO_WHILE_0
#define ACPI_USE_LOCAL_CACHE
#define ACPI_USE_NATIVE_DIVIDE

#define ACPI_MUTEX_TYPE     ACPI_BINARY_SEMAPHORE
