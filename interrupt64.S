
#define IDT_SIZE (16*256)

.global load_idt_register
.text
.code64

/**
 * See Intel Manual Vol. 2
 *  [LGDT/LIDT—Load Global/Interrupt Descriptor Table Register]
 *
 * Section "Operation" clarify why the limit is before the base
 */
load_idt_register:
    mov %rdi, IDT_POINTER_BASE /* First argument */
    mov %si, IDT_POINTER_LIMIT /* Second argument */
    lidt IDT_POINTER
    ret


.bss
IDT_POINTER:
IDT_POINTER_LIMIT:
    .skip 2
IDT_POINTER_BASE:
    .skip 8
