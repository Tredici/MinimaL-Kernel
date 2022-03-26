
.text
.code64

/**
 * Offsets to be used for storing
 */
#include "task_descriptor_offsets.h"

/**
 * To be used for storing task state when an interrupt
 * handler is invoked.
 * RSP must point to the Error Code quadword onto the
 * stack.
 * Task state is stored into the "current_tast"
 * task_descriptor.
 */
.macro SAVE_TASK_STATE
/* GPR */
    push %rbx
    push %rax
    /* get pointer to current task */
    mov current_task, %rax
    /* Store RAX */
    pop %rbx
    mov %rbx, TD_RAX(%rax)
    /* Store RBX */
    pop %rbx
    mov %rbx, TD_RBX(%rax)
    /* Other GPRS does not need to be pushed onto the stack */
    mov %rcx, TD_RCX(%rax)  /* Store RCX */
    mov %rdx, TD_RDX(%rax)  /* Store RDX */
    mov %rdi, TD_RDI(%rax)  /* Store RDI */
    mov %rsi, TD_RSI(%rax)  /* Store RSI */
    mov %rbp, TD_RBP(%rax)  /* Store RBP */
    mov %r8,  TD_R8 (%rax)  /* Store R8  */
    mov %r9,  TD_R9 (%rax)  /* Store R9  */
    mov %r10, TD_R10(%rax)  /* Store R10 */
    mov %r11, TD_R11(%rax)  /* Store R11 */
    mov %r12, TD_R12(%rax)  /* Store R12 */
    mov %r13, TD_R13(%rax)  /* Store R13 */
    mov %r14, TD_R14(%rax)  /* Store R14 */
    mov %r15, TD_R15(%rax)  /* Store R15 */

    /* Current is the current RSP */
    mov %rsp, TD_RSP(%rax)

    /* CRn */
    mov %cr3, %rbx
    mov %rbx, TD_CR3(%rax)

.endm

.global handle_div0
handle_div0:
    SAVE_TASK_STATE
    call handle_div0_c
    iretq

.global handle_int3
handle_int3:
    SAVE_TASK_STATE
    call handle_int3_c
    iretq

.global handle_ud
handle_ud:
    SAVE_TASK_STATE
    /* Pass %RIP causing fault */
    mov (%rsp), %rdi
    call handle_ud_c
    iretq


.global handle_double_f
handle_double_f:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    /* Error code is alwais 0 */
    call handle_double_f_c
    iretq


.global handle_stack_f
handle_stack_f:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    mov (%rsp), %rdi
    call handle_stack_f_c
    iretq


.global handle_gpe
handle_gpe:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    mov (%rsp), %rdi
    call handle_gpe_c
    iretq


.global handle_tss
handle_tss:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    mov (%rsp), %rdi
    call handle_tss_c
    iretq


.global handle_snp
handle_snp:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    mov (%rsp), %rdi
    call handle_snp_c
    iretq


.global handle_pfe
handle_pfe:
    add $0x08, %rsp
    SAVE_TASK_STATE
    sub $0x08, %rsp
    mov (%rsp), %rdi
    call handle_pfe_c
    iretq
