/**
 * Functions to read and write Model Specific Registers (MSRs).
 */

.text
.code64

/**
 * See Intel Manual Vol. 2
 *  [RDMSR—Read from Model Specific Register]
 */
.global msr_read
msr_read:
    push %rdx
    mov %rdi, %rcx
    rdmsr
    shl $32, %rdx
    or %rdx, %rax
    pop %rdx
    ret

.global write_msr
msr_write:
    push %rdx
    mov %edi, %ecx
    mov %esi, %eax
    mov %rsi, %rdx
    shr $32, %rdx
    wrmsr
    pop %rdx
    ret


