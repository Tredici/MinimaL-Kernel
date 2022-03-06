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
