BITS 64

section .text
    global asm_puts
    ; size_t asm_puts(const char *str)
    ; rdi == str
    extern asm_strlen
    ; size_t asm_strlen(const char *str)

asm_puts:
    ; setup stack frame
    push    rbp
    mov     rbp, rsp

    push    rdi                 ; to save str
    call    asm_strlen
    mov     rdx, rax            ; set length of syscall equal to rax(return)
                                    ; from asm_strlen
    mov     rsi, [rsp]          ; set source to pushed str
    mov     rdi, 1              ; set dest to stdout
    mov     rax, 1              ; set syscall_number
    syscall

    pop     rdi
    mov     rsp, rbp
    pop     rbp
    ret
