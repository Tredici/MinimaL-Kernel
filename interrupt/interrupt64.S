
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

/**
 * See Intel Manual Vol. 2
 *  [SIDT—Store Interrupt Descriptor Table Register]
 */
.global store_idt_register
store_idt_register:
    /* check args */
    mov $1, %eax
    test %rdi, %rdi
    jz 3f
    test %rsi, %rsi
    jz 3f
    /* Get IDT */
    sub $10, %rsp
    sidt (%rsp)
    popw (%rsi) /* get limit */
    popq (%rdi) /* get pointer */
    xor %eax,%eax
3:  ret

.bss
IDT_POINTER:
IDT_POINTER_LIMIT:
    .skip 2
IDT_POINTER_BASE:
    .skip 8
