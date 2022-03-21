/**
 * 64 bit functions to handle the Task Register (TR)
 *
 * See Intel Manual Vol. 3
 *  [2.4.4 Task Register (TR)]
 *  The task register holds the 16-bit segment selector, base
 *  address (32 bits in protected mode; 64 bits in IA-32e mode),
 *  segment limit, and descriptor attributes for the TSS of the
 *  current task. The selector references the TSS descriptor in
 *  the GDT. The base address specifies the linear address of
 *  byte 0 of the TSS; the segment limit specifies the number of
 *  bytes in the TSS. See also: Section 7.2.4, “Task Register.”
 */

#ifndef TR
#define TR

/**
 * TSS in 64 bit mode
 *
 * See Intel Manual Vol. 3
 *  [7.7 TASK MANAGEMENT IN 64-BIT MODE]
 *  [Figure 7-11. 64-Bit TSS Format]
 */
struct TSS
{
    // Must be 0
    /*   0 */ int reserved0;
    /**
     *  RSPn — The full 64-bit canonical forms of the stack
     *  pointers (RSP) for privilege levels 0-2.
     */
    /*   4 */ long rsp0;
    /*  12 */ long rsp1;
    /*  20 */ long rsp2;
    // Must be 0
    /*  28 */ long reserved1;
    /**
     *  ISTn — The full 64-bit canonical forms of the interrupt
     *  stack table (IST) pointers.
     */
    /*  36 */ long ist1;
    /*  44 */ long ist2;
    /*  52 */ long ist3;
    /*  60 */ long ist4;
    /*  68 */ long ist5;
    /*  76 */ long ist6;
    /*  84 */ long ist7;
    // Must be 0
    /*  92 */ long reserved2;
    /* 100 */ short reserved3;
    /**
     *  I/O map base address — The 16-bit offset to the I/O
     *  permission bit map from the 64-bit TSS base.
     */
    /* 102 */ short io_map_base_address;
} __attribute__ ((packed));

#endif
