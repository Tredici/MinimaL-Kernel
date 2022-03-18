/**
 * Assembly code of status_operations functions
 */

.text
.code64


.global so_read_cr0
so_read_cr0:
    mov %cr0, %rax
    ret

.global so_read_cr1
so_read_cr1:
    mov %cr1, %rax
    ret

.global so_read_cr2
so_read_cr2:
    mov %cr2, %rax
    ret

.global so_read_cr3
so_read_cr3:
    mov %cr3, %rax
    ret

.global so_read_cr4
so_read_cr4:
    mov %cr4, %rax
    ret

.global so_read_cr5
so_read_cr5:
    mov %cr5, %rax
    ret

.global so_read_cr6
so_read_cr6:
    mov %cr6, %rax
    ret

.global so_read_cr7
so_read_cr7:
    mov %cr7, %rax
    ret

.global so_read_cr8
so_read_cr8:
    mov %cr8, %rax
    ret

.global so_read_cs
so_read_cs:
    xor %rax, %rax
    mov %cs, %ax
    ret

.global so_read_ds
so_read_ds:
    xor %rax, %rax
    mov %ds, %ax
    ret

.global so_read_ss
so_read_ss:
    xor %rax, %rax
    mov %ss, %ax
    ret

.global so_read_es
so_read_es:
    xor %rax, %rax
    mov %es, %ax
    ret

.global so_read_fs
so_read_fs:
    xor %rax, %rax
    mov %fs, %ax
    ret

.global so_read_gs
so_read_gs:
    xor %rax, %rax
    mov %gs, %ax
    ret

.global so_read_rflags
so_read_rflags:
    pushf
    pop %rax
    ret

.global so_read_gdtr
so_read_gdtr:
    mov $1, %rax
    test %rdi, %rdi
    jz 1f
    test %rsi, %rsi
    jz 1f
    sub $10, %rsp
    popw (%rsi) /* get limit */
    popq (%rdi) /* get pointer */
    xor %rax, %rax
1:  ret
