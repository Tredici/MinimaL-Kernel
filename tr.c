#include "tr.h"
#include "status_operations64.h"
#include "error64.h"

/**
 * The fourth position in the GDT will be used
 * for the kernel task.
 */
#define FIRST_TASK_INDEX  3
#define FIRST_TASK_OFFSET (FIRST_TASK_INDEX * sizeof(struct segment_descriptor))

void *get_kernel_stack();

/**
 * This is the main kernel task.
 * It is used for initialising purposes
 * and will never have a user space component.
 */
static struct task_descriptor kernel_task;

/**
 * See Intel Manual Vol. 3
 *  [7.7 TASK MANAGEMENT IN 64-BIT MODE]
 *  The operating system must create at least one
 *  64-bit TSS after activating IA-32e mode. It must
 *  execute the LTR instruction (in 64-bit mode) to
 *  load the TR register with a pointer to the 64-bit
 *  TSS responsible for both 64-bit-mode programs and
 *  compatibility-mode programs.
 */
void init_first_task_descriptor()
{
    void *ptr;
    unsigned short limit;
    so_read_gdtr(&ptr, &limit);
    struct segment_descriptor *const gdt = (struct segment_descriptor *)ptr;
    if (sizeof(struct segment_descriptor) != 16L)
    {
        panic64("sizeof(struct segment_descriptor) != 16L");
    }

    /* Prepare GDT field for TSS */
    {
        // Prepare kernel stack
        kernel_task.tss.rsp0 = (long)get_kernel_stack();
        kernel_task.tss.io_map_base_address = sizeof(struct  TSS)-1;

        // Clear everything
        gdt[FIRST_TASK_INDEX] = (struct segment_descriptor){};
        // Prepare pointer to TSS address
        unsigned long val = (unsigned long)&kernel_task.tss;
        gdt[FIRST_TASK_INDEX].base_15_0 = val & 0xffff;
        gdt[FIRST_TASK_INDEX].base_23_16 = (val >> 16) & 0xff;
        gdt[FIRST_TASK_INDEX].base_31_24 = (val >> 24) & 0xff;
        gdt[FIRST_TASK_INDEX].base_63_32 = (val >> 32) & 0xffffffff;
        // set limit size
        /**
         * See Intel Manual Vol. 3
         *  [7.2.2 TSS Descriptor]
         *  When the G flag is 0 in a TSS descriptor for a 32-bit TSS,
         *  the limit field must have a value equal to or greater than
         *  67H, one byte less than the minimum size of a TSS.
         *  Attempting to switch to a task whose TSS descriptor has a
         *  limit less than 67H generates an invalid-TSS exception (#TS).
         *  A larger limit is required if an I/O permission bit map is
         *  included or if the operating system stores additional data.
         */
        gdt[FIRST_TASK_INDEX].limit_15_0 = sizeof(struct TSS)-1;
        /**
         * See Intel Manual Vol. 3
         *  [3.5 SYSTEM DESCRIPTOR TYPES]
         *  When the S (descriptor type) flag in a segment descriptor
         *  is clear, the descriptor type is a system descriptor. The
         *  processor recognizes the following types of system
         *  descriptors:
         *      [...]
         *      +Task-state segment (TSS) descriptor.
         *      [...]
         *  These descriptor types fall into two categories:
         *  system-segment descriptors and gate descriptors. System
         *  segment descriptors point to system segments (LDT and TSS
         *  segments). Gate descriptors are in themselves “gates,” which
         *  hold pointers to procedure entry points in code segments
         *  (call, interrupt, and trap gates) or which hold segment
         *  selectors for TSS’s (task gates).
         *
         * See Intel Manual Vol. 3
         *  [Figure 7-4. Format of TSS and LDT Descriptors in 64-bit Mode]
         * The field is 0 for TSS descriptor.
         */
        gdt[FIRST_TASK_INDEX].system = 0;
        /**
         * See Intel Manual Vol. 3
         *  [Table 3-2. System-Segment and Gate-Descriptor Types]
         *  Type Field  Description
         *  9           64-bit TSS (Available)
         */
        gdt[FIRST_TASK_INDEX].type = 9;
        // It must clearly be marked as present
        gdt[FIRST_TASK_INDEX].present = 1;
    }
    /* load TR */
    load_tr(FIRST_TASK_OFFSET);

}
