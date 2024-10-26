BITS 64

section .text
    global asm_strstr
    ; rdi = haystack
    ; rsi = needle

asm_strstr:
    ; set up stack
    push    rbp
    mov     rbp, rsp

    xor     rax, rax
    xor     rcx, rcx

    cmp     rsi, 0
    jz      .done

.haystack_loop:
    mov     al, byte[rdi]
    mov     bl, byte[rsi]

    cmp     al, 0
    jz      .needle_not_found

    cmp     al, bl
    je      .needle_search

    inc     rdi
    jmp     .haystack_loop

.needle_search:
    ; set rdi, rsi to rdx, rcx to preserve rdi, rsi pointers
    mov     rdx, rdi
    mov     rcx, rsi
    jmp     .needle_loop
.needle_loop:
    ; scanning rest of needle against haystack
    inc     rdx
    inc     rcx
    mov     al, byte[rdx]
    mov     bl, byte[rcx]

    cmp     bl, 0
    jz      .needle_found

    cmp     al, bl
    je      .needle_loop
    jne     .reset_haystack

.needle_found:
    mov     rax, rdi
    jmp     .done

.reset_haystack:
    ; increment rdi to move haystack search to next char
    inc     rdi
    jmp     .haystack_loop

.needle_not_found:
    xor     rax, rax
    jmp     .done

.done:
    mov     rsp, rbp
    pop     rbp
    ret

