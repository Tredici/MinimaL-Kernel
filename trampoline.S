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
 * See Intel Manual Vol. 4
 *  [CHAPTER 2 MODEL-SPECIFIC REGISTERS (MSRS)]
 *  in particular
 *  [2.1 ARCHITECTURAL MSRS]
 *
 * These register are managed using specific
 * instructions (they are not accessible directly
 * like general purpose registers or control
 * register) like:
 *  +RDMSR—Read from Model Specific Register
 *      Read MSR specified by ECX into EDX:EAX.
 *  +WRMSR—Write to Model Specific Register
 *      Write the value in EDX:EAX to MSR specified
 *      by ECX.
 *
 * See Intel Manual Vol. 2 for details.
 * Register structure is described in:
 *  [2.2.1 Extended Feature Enable Register]
 *  [Figure 2-4. IA32_EFER MSR Layout]
 *  [Table 2-1. IA32_EFER MSR Information]
 */
#define IA32_EFER_ADDR 0xc0000080
/**
 * Position of the bit in the MSR
 *
 * LME (probably) stand for Long Mode Enable
 *
 * From:
 *  IA-32e Mode Enable: IA32_EFER.LME (R/W)
 *  Enables IA-32e mode operation.
 */
#define IA32_EFER_LME (1 << 8)


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

/**
 * Used to load GDT pointer with lgdt
 * instruction. This instruction, in 32
 * bit mode, require one word followed
 * by a double word.
 *
 * See Intel manual Vol. 2:
 *  [LGDT/LIDT—Load Global/Interrupt
 *  Descriptor Table Register]
 */
GDT_POINTER:
    .word (SEGMENT_DESCRIPTOR_TABLE_64_END - SEGMENT_DESCRIPTOR_TABLE_64)
    .long SEGMENT_DESCRIPTOR_TABLE_64
/**
 * Used to debug lgdt
 *
GDT_POINTER_CP:
    .skip 10
 */

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

    jmp trampoline64
    hlt
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
 * Handle 64 bit initialization
 */
trampoline64:
    /* Is 64 bit mode supported? */
    call ensure_64bit_mode_available
    call initialize_64bit_paging
    call initialize_64bit_data_structure

    /**
     * For far jump in AT&T syntax.
     *
     * See as manual:
     * [9.16.3.1 AT&T Syntax versus Intel Syntax]
     *  Immediate form long jumps and calls are
     *  ‘lcall/ljmp $section, $offset’ in AT&T syntax;
     *  the Intel syntax is ‘call/jmp far section:offset’.
     *  Also, the far return instruction is ‘lret $stack-adjust’
     *  in AT&T syntax; Intel syntax is ‘ret far stack-adjust’.
     *
     * https://sourceware.org/binutils/docs/as.html#i386_002dVariations
     *
     * Reference first entry of GDT for code segment
     */
    ljmp $0x10, $_start64

    hlt

/**
 * This function will initialise remaining
 * data structure other than page tables
 *
 * An useful tutorial is this:
 *  https://www.youtube.com/watch?v=wz9CZBeXR6U
 *  [Write Your Own 64-bit Operating System Kernel #2
 *  - Stack, long mode and printing using C code]
 *
 * For details see Intel Manual Vol. 3:
 *  [9.8.5 Initializing IA-32e Mode]
 *  [9.8.5.1 IA-32e Mode System Data Structures]
 */
initialize_64bit_data_structure:
    pushl $SEGMENT_DESCRIPTOR_TABLE_64
    call intialise_gdt
    add $4, %esp
GDT:
    /**
     * In 32 bit mode this instruction require
     * a m16&32 argument from memory
     *
     * See comment near GDT_POINTER for details
     */
    lgdt GDT_POINTER
    /**
     * Used for debugging purposes
     *
    sgdt GDT_POINTER_CP
     */
    ret

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
    /**
     * For a recap see Vol. 3
     *  [9.8.5 Initializing IA-32e Mode]
     */
    /* Initialize 64 bit page tables structure */
    pushl $PDT
    pushl $PDPT
    pushl $PML4
    call initialize_64bits_page_tables
    /* clear stack */
    add $12, %esp

    /* Initialize CR3 */
        mov $PML4, %eax
        mov %eax, %cr3
    
    /**
     * See Intel Manual Vol. 3
     *  [Figure 4-1. Enabling and Changing Paging Modes]
     *
     * Must access Model Specific Registers
     *  IA32_EFER.LME = 1
     *
     * To access MSR use rdmsr and wrmsr.
     * See comment near macro definition for details
     */
    mov $IA32_EFER_ADDR, %ecx
    rdmsr
    or $IA32_EFER_LME, %eax
    wrmsr
    /**
     * Also CR4 must be set
     *  CR4.PAE = 1
     */
    mov %cr4, %eax
    or $CR4_PAE, %eax
    mov %eax, %cr4
    /**
     * Also CR0 must be set
     *  CR0.PG = 1
     */
    /* Enable paging setting CR0 */
        /* Get current value of CR0 */
        mov %cr0, %eax
        /* Enable paging */
        or $CR0_BIT_PE, %eax
        or $CR0_BIT_PG, %eax

        /* Overwrite CR0 */
        mov %eax, %cr0

    /* Now LONG MODE is ENABLED! */
    /**
     * ret WILL work because THIS
     * CODE is compiled as 32 bit
     */
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

/**
 * Here will be stored the GDT
 * used when jumping to 64 bit
 * code.
 *
 * Max size would be 8 * 8192 fields.
 * Just one page will be sufficient
 * for this simple project.
 *
 * Will be initialised before jumping
 * to 64 bit code.
 *
 * See Intel manual Vol. 3:
 *  [3.4.5 Segment Descriptors]
 *  [3.5 SYSTEM DESCRIPTOR TYPES]
 */
SEGMENT_DESCRIPTOR_TABLE_64:
    .skip 4096
SEGMENT_DESCRIPTOR_TABLE_64_END:

/**
 * Will be initialised if required when
 * activating 64 bit mode.
 *
 * One TSS will be useful in 64 bit mode.
 *
 * See Intel Manual Vol. 3:
 *  [7.7 TASK MANAGEMENT IN 64-BIT MODE]
 *  [Figure 7-11. 64-Bit TSS Format]
 *
 * More less than 4KB are required but
 * to simplify code...
 */
#pragma warning GCC "To be used..."
INITIAL_TSS_64:
    .skip 4096
