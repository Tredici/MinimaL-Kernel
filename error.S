/**
 * The purpose of this file is to expose a function to
 * print a supplied error string on the display of the
 * machine and halt the machine itself.
 *
 * It should be used only for unrecoverable errors
 * during the intial (32 bits) part of the booting
 * process.
 */

/**
 * Memory location on video memory on x86 at startup.
 *
 */
#define VIDEO_MEMORY 0xB8000
/**
 * To be used for background and font color
 */
#define CHAR_COLOR 0x15

.data
/* Point at the beginning */
VIDEO_BUFFER:
    .long VIDEO_MEMORY
ABORT_MSG:
    .asciz "ABORTED: "

.text
.code32
.global _abort

/**
 * Expect character in AL. Print it on the screen.
 * Next character will be printed.
 * All registers will be preserved.
 * STACK IS REQUIRED!
 */
putc:
    push %eax
    /* To be used for char position */
    push %ebx
    mov $CHAR_COLOR, %ah
    mov VIDEO_BUFFER, %ebx
    /* Next char will be printed 2 pos after */
    addl $2, VIDEO_BUFFER
    /* print char */
    movw %ax, (%ebx)
    /* restore registers */
    pop %ebx
    pop %eax
    ret

/**
 * Print a null terminated ascii string up to 80 chars
 * on the console string.
 *
 * @parameter: EAX pointer to the string
 * 
 * All registers are preserved.
 * STACK IS REQUIRED!
 */
printstr:
    push %eax
    push %ebx
    push %ecx
    mov $80, %ecx
    /* EBX is for arrays */
    mov %eax, %ebx
loop_printstr:
    /* take letter */
    movb (%ebx), %al
    /* inc pointer */
    inc %ebx
    /* check letter */
    test %al, %al   /* AND without effect on the operands */
        /* if is null jump to end_printstr */
        jz end_printstr
    /* print letter */
    call putc
    /* repeat */
    loop loop_printstr

end_printstr:
    pop %ecx
    pop %ebx
    pop %eax
    ret

/**
 * Expect a pointer to a null terminated ascii string
 * in EAX.
 *
 * Does NOT return!
 */
_abort:
    push %eax
    mov $ABORT_MSG, %eax
    call printstr
    pop %eax
    call printstr
    /* clear interrupt to not resume execution */
    cli
    hlt

