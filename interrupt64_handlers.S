
.text
.code64

.global handle_ud
handle_ud:
    mov (%rsp), %rdi
    call handle_ud_c
    iretq


.global handle_gpe
handle_gpe:
    mov (%rsp), %rdi
    call handle_gpe_c
    iretq
