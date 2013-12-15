#include <arch/arch.h>
#include <arch/segment.h>
#include <arch/trap.h>
#include <arch/page.h>
#include <arch/early_printk.h>
#include <acpi.h>

void arch_init(void *args)
{
    ACPI_STATUS Status;

    early_printk("planck_kernel arch_init\n");

    page_init();

    Status = AcpiInitializeSubsystem();
    if (ACPI_FAILURE(Status))
    {
        early_printk("ACPI init failure: 0x%x\n", Status);
    }

    Status = AcpiInitializeTables(NULL, 16, FALSE);
    if (ACPI_FAILURE(Status))
    {
        early_printk("ACPI tables init failure: 0x%x\n", Status);
        return;
    }

    Status = AcpiLoadTables();
    if (ACPI_FAILURE(Status))
    {
        early_printk("ACPI tables load failure: 0x%x\n", Status);
        return;
    }



    segment_init();
    trap_init();
}
