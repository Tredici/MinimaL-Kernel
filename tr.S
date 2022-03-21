

.text
.code64

.global load_tr
load_tr:
    ltr %di
    ret

.global get_kernel_stack
get_kernel_stack:
    lea KERNEL_STACK, %rax
    ret

.bss
/**
 * Kernel stack used by the kernel task descriptor
 */
.align 4096
KERNEL_STACK:
    .skip 4096
