/**
 * Functions to read and write Model Specific Registers (MSRs).
 */

.text
.code64

/**
 * See Intel Manual Vol. 2
 *  [RDMSR—Read from Model Specific Register]
 */
.global read_msr
read_msr:
    push %rdx
    mov %rdi, %rcx
    rdmsr
    shl $32, %rdx
    or %rdx, %rax
    pop %rdx
    ret

.global write_msr
write_msr:
    push %rdx
    mov %edi, %ecx
    mov %esi, %eax
    mov %rsi, %rdx
    shr $32, %rdx
    wrmsr
    pop %rdx
    ret


