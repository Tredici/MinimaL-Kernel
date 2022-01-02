/**
 * This file contains code to handle the
 * passage to 64 bits mode.
 *
 * Useful reference, Intel Volume 3A
 *  [9.8 SOFTWARE INITIALIZATION FOR PROTECTED-MODE OPERATION]
 *
 */

/**
 * If this bit is set in EFLAGS the CPUID
 * istruction is available
 */
#define BIT_ID_EFLAGS (1 << 21)

/**
 * Bit to set enabled in CR0 to enable paging
 */
#define CR0_BIT_PE (1 << 0)
#define CR0_BIT_PG (1 << 31)

/**
 * Value to be used in EAX to query
 * limits for 'Extended Function CPUID Information'
 *
 * Result:
 *  EAX Maximum Input Value for Extended Function CPUID Information.
 *
 * See Intel manual 2
 *  [CPUID—CPU Identification]
 */
#define CPUID_EAX_EFCI_LIMIT 0x80000000

/**
 * Value in EAX to be used to query 64 bit support.
 *
 * Result:
 *  EDX Bit 29: Intel ® 64 Architecture available if 1.
 */
#define CPUID_EAX_EFCI_64BIT 0x80000001
#define BIT_29 (1 << 29)

/**
 * From Intel volume 3 [2.5 Control register]
 *
 * CR4.PSE
 *  Page Size Extensions (bit 4 of CR4) — Enables
 *  4-MByte pages with 32-bit paging when set; restricts
 *  32-bit paging to pages of 4 KBytes when clear.
 *  See also: Section 4.3, “32-Bit Paging.”
 */
#define CR4_PSE (1 << 4)
/**
 * From Intel volume 3 [2.5 Control register]
 *
 * CR4.PAE
 *  Physical Address Extension (bit 5 of CR4) — When set,
 *  enables paging to produce physical addresses with
 *  more than 32 bits. When clear, restricts physical
 *  addresses to 32 bits. PAE must be set before entering
 *  IA-32e mode.
 *  See also: Chapter 4, “Paging.”
 */
#define CR4_PAE (1 << 5)

.data
ERROR_CPUID:
    .asciz "CPUID istruction not available!"
ERROR_64BIT_MODE:
    .asciz "64 BIT MODE not supported!"
OK_64BIT:
    .asciz "64 BIT MODE is available!"
PAGING_32_BIT_ENABLED:
    .asciz "32 BIT paging working!"

.global trampoline
.text
.code32

/**
 * This function check CPU capabilities
 * and, if possible, activate 64 bits
 * execution mode.
 *
 * Prior to switch to 64 bit mode it
 *
 * Then it invoke the kernel main function
 * thaht will take care of the remaining
 * work
 */
trampoline:
    /* Can we use the CPUID istruction? */
    call ensure_cpuid_available
    /* Is 64 bit mode supported? */
    call ensure_64bit_mode_available

    /**
     * Initialize paging
     * See Intel manual 3 chapter
     *  [9.8.3 Initializing Paging]
     *      With this paging initialization complete,
     *      paging is enabled and the processor is
     *      switched to protected mode at the same
     *      time by loading control register CR0 with
     *      an image in which the PG and PE flags are set.
     *
     * Require initialising CR3 register with
     * physical address of top level page table,
     * then flags in CR0 must be set.
     */
    call initialize_32bit_paging

    /**
     * Pass multiboot info to the main
     * function. See Multiboot specification
     * for details.
     */
    pushl multiboot_info_structure
    call main32
    pop %eax

    /* Should never be reached */
    hlt

/**
 * Manipulate control registers to enable paging
 * and 64 bit mode.
 *
 * EAX is overwritten
 *
 * For more info see Intel manual volume 3:
 *  [2.5 CONTROL REGISTERS]
 */
initialize_64bit_paging:
#pragma GCC warning "To be complete"
    /* Initialize CR3 */
        mov $PML4, %eax
        mov %eax, %cr3
    /* Enable paging setting CR0 */
        /* Get current value of CR0 */
        mov %cr0, %eax
        /* Enable paging */
        or $CR0_BIT_PE, %eax
        or $CR0_BIT_PG, %eax

        /* Overwrite CR0 */
        mov %eax, %cr0

    ret

/**
 * To enable paging in 32 bit mode we need
 * less configuration.
 * Without PAE just 2 page table levels are
 * used and we can create MAXI table to use
 * only one translation level.
 */
initialize_32bit_paging:
    pushal

    /* Initialize top level page directory */
    pushl $PD_32bit
    call initialize_page_directory
    /* clear stack */
    pop %eax

    /* Set CR3 to prepare mapping */
    mov $PD_32bit, %eax
    mov %eax, %cr3

    /* activate 4MB pages in CR4 */
    mov %cr4, %eax
    /* Ensure PAE is disabled, see [4.3 32-BIT PAGING] Intel manual 3 */
    and $(~CR4_PAE), %eax
    /* Enable 4MB pages */
    or $CR4_PSE, %eax
    mov %eax, %cr4
    
    /* activate 32 bit paging acting on CR0 */
    mov %cr0, %eax
    or $CR0_BIT_PE, %eax
    or $CR0_BIT_PG, %eax
    mov %eax, %cr0

    popal
    ret

/**
 * Ensure the CPUID istruction is available,
 * if not abort.
 * See CPUID on Intel manual 2
 *
 * From Intel Manual 1
 *  [3.4.3.3 System Flags and IOPL Field]
 *      ID (bit 21) Identification flag — The ability
 *      of a program to set or clear this flag
 *      indicates support for the CPUID instruction.
 *
 * All registers are preserved.
 */
ensure_cpuid_available:
    /* Save all registers */
    pushal

    /* Switch 2 times the ID flag */
    pushf
    /* Swap flag 1st time */
    xorl $BIT_ID_EFLAGS, (%esp)
    popf

    pushf
        /* Copy EFLAGS in EAX */
        mov (%esp), %eax
    /* Swap flag 2nd time */
    xorl $BIT_ID_EFLAGS, (%esp)
    popf

    /* Get current value of EFLAGS */
    pushf
    pop %ebx

    /* Check if ID flag was switched */
    cmp %eax, %ebx
        je cpuid_not_available

    /* Restore saved registers */
    popal
    ret

cpuid_not_available:
    mov $ERROR_CPUID, %eax
    call _abort
    /* never reached */
    hlt

/**
 * Check if 64 bit execution mode is supported
 * by the processor, if not abort.
 *
 * Preserve all registers,
 */
ensure_64bit_mode_available:
    /* save all registers on the stack */
    pushal

    /**
     * Prepare execution of CPUID istruction
     * See Intel manual 2
     *  [CPUID—CPU Identification]
     *
     * It is necessary to check if CPUID permit
     * to check some processor extension via
     * EAX=8000...
     * and then check if 64 bit mode is supported
     */

    /* Check if extended informations are available */
        mov $CPUID_EAX_EFCI_LIMIT, %eax
        cpuid
        /* Check EI availability */
        cmp $CPUID_EAX_EFCI_64BIT, %eax
            jb processor_64bit_mode_not_supported

    /* Now check if 64bit mode availability */
        mov $CPUID_EAX_EFCI_64BIT, %eax
        cpuid
        test $BIT_29, %edx
            jz processor_64bit_mode_not_supported
    
    /* If here eveything we can use 64 bit mode */

    /* restore all registers */
    popal
    ret

processor_64bit_mode_not_supported:
    mov $ERROR_64BIT_MODE, %eax
    call _abort
    /* never reached */
    hlt

.bss
/**
 * Data structures to handle paging and memory
 * See Intel manuals, in particular volume 3.
 */
/**
 * Pages must be aligned to 4KB due to hardware
 * constraints. See Intel manuals.
 */
.align 4096
/**
 * Intel Volume 3
 *  [2.1.5.1 Memory Management in IA-32e Mode]
 *      5. The page map level 5 (PML5)
 *      4. A page map level 4 (PML4)
 *      3. A set of page directory pointer tables
 *      2. Sets of page directories
 *      1. Sets of page tables
 *
 * Using 5 levels of pages is unnecessary in most
 * situations, so I will use only four.
 *
 * When a multiboot compliant bootloader start the
 * kernel it is placed where specified in the code
 * file, so out code will be started near the first
 * MB of RAM.
 * We can exploit this to use 4 MB page table to
 * avoid defining hundreds of useless page tables.
 */
PML4:
    .skip 4096
PDPT:
    .skip 4096
PDT:
    .skip 4096
PT:
    .skip 4096

/* Next are pages to be used in 32 byt paging */
PD_32bit:
    .skip 4096
