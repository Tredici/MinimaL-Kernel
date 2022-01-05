/**
 * 64 bit version of IO functions
 */

.text
.code64

.global inputb64
.global outputb64

/* 64 bit C wrapper for IN machine istruction */
inputb64:
    /* Argument 1 is in %rdi, needend in %rdx */
    xchg %rdi, %rdx

    xor %rax, %rax
    /* Perform input op */
    in %dx, %al

    /* Restore previous %rdx */
    xchg %rdi, %rdx
    ret


outputb64:
    /* Argument 1 is in %rdi, needend in %rdx */
    xchg %rdi, %rdx
    /* Argument 2 is in %rsi, needend in %rax */
    mov %rsi, %rax

    /* Perform input op */
    out %al, %dx

    /* Restore previous %rdx */
    xchg %rdi, %rdx    
    ret

