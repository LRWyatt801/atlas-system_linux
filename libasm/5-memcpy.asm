BITS 64

section .text

    global asm_memcpy

    ; void *asm_memcpy(void *dest, const void *src, size_t n);

    ; rdi == dest == edi
    ; rsi == src == esi
    ; rdx == n

asm_memcpy:
    push    rbp
    mov     rbp, rsp

    ; check for null arguments
    cmp     rdi, 0
    jz      .return
    cmp     rsi, 0
    jz      .return

    xor     rcx, rcx

.cpy_loop:
    cmp     rdx, rcx
    jz      .return
    mov     al, byte[rsi + rcx]
    mov     byte[rdi + rcx], al
    inc     rcx
    jmp     .cpy_loop

.return:
    mov     rax, rdi
    mov     rsp, rbp
    pop     rbp
    ret
