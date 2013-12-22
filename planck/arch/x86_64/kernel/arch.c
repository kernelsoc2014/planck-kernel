#include <arch/arch.h>
#include <arch/segment.h>
#include <arch/trap.h>
#include <arch/memorymanager.h>
#include <arch/earlyoutput.h>
#include <acpi.h>

void AcInitialize(void *bootArguments)
{
    ACPI_STATUS status;

    KeEarlyOutput("[planck_kernel] AcInitialize\n");

    AcSegmentInitialize();
    AcTrapInitialize();
    MmPageInitialize();

    status = AcpiInitializeSubsystem();
    if (ACPI_FAILURE(status))
    {
        KeEarlyOutput("ACPI init failure: 0x%x\n", status);
    }

    status = AcpiInitializeTables(NULL, 16, FALSE);
    if (ACPI_FAILURE(status))
    {
        KeEarlyOutput("ACPI tables init failure: 0x%x\n", status);
        return;
    }

    status = AcpiLoadTables();
    if (ACPI_FAILURE(status))
    {
        KeEarlyOutput("ACPI tables load failure: 0x%x\n", status);
        return;
    }
}
