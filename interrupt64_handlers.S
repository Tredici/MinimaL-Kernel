
.text
.code64

.global handle_gpe
handle_gpe:
    mov (%rsp), %rdi
    call handle_gpe_c
    iretq
