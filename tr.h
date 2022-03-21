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



#endif
