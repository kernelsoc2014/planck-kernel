/*
 * These interfaces are required in order to compile the ASL compiler and the
 * various ACPICA tools under Linux or other Unix-like system.
 */
#include "acpi.h"
#include "accommon.h"
#include "amlcode.h"
#include "acparser.h"
#include "acdebug.h"

#include <stdlib.h>
#include <planck/kmalloc.h>

#define _COMPONENT          ACPI_OS_SERVICES
        ACPI_MODULE_NAME    ("oslplanck")

ACPI_STATUS AcpiOsInitialize()
{
    return AE_OK;
}

ACPI_STATUS AcpiOsTerminate()
{
    return AE_OK;
}

ACPI_PHYSICAL_ADDRESS AcpiOsGetRootPointer()
{
    ACPI_SIZE Ret;
    AcpiFindRootPointer(&Ret);
    return Ret;
}

ACPI_STATUS AcpiOsPredefinedOverride(const ACPI_PREDEFINED_NAMES *PredefinedObject, ACPI_STRING *NewValue)
{
    *NewValue = NULL;
    return AE_OK;
}

ACPI_STATUS AcpiOsTableOverride(ACPI_TABLE_HEADER *ExistingTable, ACPI_TABLE_HEADER **NewTable)
{
    *NewTable = NULL;
    return AE_OK;
}

void *AcpiOsMapMemory(ACPI_PHYSICAL_ADDRESS PhysicalAddress, ACPI_SIZE Length)
{
    return PhysicalAddress;
}

void AcpiOsUnmapMemory(void *where, ACPI_SIZE length)
{

}

ACPI_STATUS AcpiOsGetPhysicalAddress(void *LogicalAddress, ACPI_PHYSICAL_ADDRESS *PhysicalAddress)
{
    *PhysicalAddress = LogicalAddress;
    return AE_OK;
}

void *AcpiOsAllocate(ACPI_SIZE Size)
{

}

void AcpiOsFree(void *Memory)
{

}

BOOLEAN AcpiOsReadable(void *Memory, ACPI_SIZE Length)
{

}

BOOLEAN AcpiOsWritable(void *Memory, ACPI_SIZE Length)
{

}
