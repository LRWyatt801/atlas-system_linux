BITS 64

section .text
    global asm_strpbrk
    ; size_t asm_strpbrk(const char *s, const char *reject)
    ; rdi == s
    ; rsi == reject

asm_strpbrk:
    ; set up stack frame
    push    rbp
    mov     rbp, rsp

    xor     rax, rax

    ;check for null arguments
    cmp     rdi, 0
    jz      .done
    cmp     rsi, 0
    jz      .done
    mov     bl, byte[rsi]
    cmp     bl, 0
    jz      .done

    push    rsi
    mov     rsi, [rsp]

    ;set up for first char in s
    mov     al, byte[rdi]
    cmp     al, 0
    jz      .done
    jmp     .accept_loop

.s_loop:
    inc     rdi
    mov     al, byte[rdi]
    cmp     al, 0
    je      .done
    mov     rsi, [rsp]
    jmp     .accept_loop

.accept_loop:
    mov     bl, byte[rsi]
    cmp     bl, 0
    jz      .s_loop
    cmp     al, bl
    je      .accept_in_loop
    inc     rsi
    jmp     .accept_loop

.accept_in_loop:
    mov     rax, rdi
    jmp     .done

.done:
    pop     rsi
    mov     rsp, rbp
    pop     rbp
    ret
