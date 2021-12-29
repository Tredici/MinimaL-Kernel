.text
.code32

.global inputb32
.global outputb32

/* 32 bit C wrapper for IN machine istruction */
inputb32:
    push %edx
    mov $0, %eax

    /* ESP+4 point to return EIP due the initial push */
    mov 8(%esp), %edx
    /* Perform input op */
    in %dx, %al
    
    pop %edx
    ret


outputb32:
    push %edx
    mov $0, %eax

    /* ESP+4 point to return EIP due the initial push */
    mov 8(%esp), %edx
    mov 12(%esp), %eax
    /* Perform input op */
    out %al, %dx
    
    pop %edx
    ret

