BITS 64

section .text
    global asm_strcspn
    ; size_t asm_strcspn(const char *s, const char *reject)
    ; rdi == s
    ; rsi == reject

asm_strcspn:
    ; set up stack frame
    push    rbp
    mov     rbp, rsp

    xor     rcx, rcx

    ;check for null arguments
    cmp     rdi, 0
    jz      .done
    cmp     rsi, 0
    jz      .done

    push    rsi
    mov     rsi, [rsp]

    ;set up for first char in s
    mov     al, byte[rdi]
    cmp     al, 0
    jz      .done
    jmp     .reject_loop

.s_loop:
    inc     rdi
    mov     al, byte[rdi]
    cmp     al, 0
    je      .done ; re-evaluate in a bit
    mov     rsi, [rsp]
    jmp     .reject_loop

.reject_loop:
    mov     bl, byte[rsi]
    cmp     bl, 0
    jz      .reject_not_in_s
    cmp     al, bl
    je      .done
    inc     rsi
    jmp     .reject_loop

.reject_not_in_s:
    inc     rcx
    jmp     .s_loop

.done:
    mov     rax, rcx
    pop     rsi
    mov     rsp, rbp
    pop     rbp
    ret
