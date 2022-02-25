/**
 * This file contains the "entry point"
 * for 64 bit code execution.
 */

/**
 * Stack size for 64 bit code
 */
#define STACK_64_SIZE (4096)


.global _start64
.text
.code64

_start64:
    /**
     * In 64 bit segment registers other than code are unnecessary.
     * They are all mapped to the predefined (secondo) entry in GDT.
     * See trampoline.S for details.
     */
    mov $0x10, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs
    /**
     * Intel Manual Vol. 3
     *
     * [6.8.3 Masking Exceptions and Interrupts When Switching Stacks]
     *  Intel recommends that software use the LSS instruction to
     *  load the SS register and ESP together. The problem identified
     *  earlier does not apply to LSS, and the LSS instruction does
     *  not inhibit events as detailed above.
     */

    /* initialize stack pointer */
    mov $(STACK_64 + STACK_64_SIZE), %rsp
    /* Clean GP registers */
    mov %rsp, %rbp
    xor %rax, %rax
    xor %rbx, %rbx
    xor %rcx, %rcx
    xor %rdx, %rdx
    xor %rsi, %rsi
    xor %rdi, %rdi

    /* Initialize interrupt handling */
    call initialize_idt

    /* Call main function */
    call main64
    
    hlt

.bss
/**
 * Page aligned stack
 */
.align 4096
STACK_64:
    .skip STACK_64_SIZE
