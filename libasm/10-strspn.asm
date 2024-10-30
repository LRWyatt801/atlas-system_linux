BITS 64

section .text
    global asm_strspn
    ; size_t asm_strspn(const char *s, const char *accept)
    ; rdi == s
    ; rsi == accept

asm_strspn:
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
    jmp     .accept_loop

.s_loop:
    inc     rdi
    mov     al, byte[rdi]
    cmp     al, 0
    je      .done ; re-evaluate in a bit
    mov     rsi, [rsp]
    jmp     .accept_loop

.accept_loop:
    mov     bl, byte[rsi]
    cmp     bl, 0
    jz      .done
    cmp     al, bl
    je      .accept_in_s
    inc     rsi
    jmp     .accept_loop

.accept_in_s:
    inc     rcx
    jmp     .s_loop

.done:
    mov     rax, rcx
    pop     rsi
    mov     rsp, rbp
    pop     rbp
    ret
