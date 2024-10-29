BITS 64

section .text
    global asm_putc
    ; size_t asm_putc(int c)
    ; rdi = c

asm_putc:
    push    rbp
    mov     rbp, rsp
    push    rdi

    mov     rax, 1           ; sys_write syscall number
    mov     rdi, 1           ; file descriptor 1 (stdout)
    mov     rsi, rsp         ; pointer to character
    mov     rdx, 1           ; length (1 character)
    syscall

    mov     rsp, rbp
    pop     rbp
    ret