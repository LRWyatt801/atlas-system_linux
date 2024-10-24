BITS 64

section .data
    ; No needed global vars

section .text
    global asm_strchr

    ; char *asm_strchr(const char *s, int c);

asm_strchr:
    ; set up stack frame
    push    rbp
    mov     rbp, rsp

    xor     rax, rax                    ; returning address needs rax
    xor     rcx, rcx

    cmp     rsi, 0
    jz      .done

.loop:
    ; move char to ax
    movzx   eax, byte[rdi]

    ; check for null byte
    cmp     eax, 0
    jz      .done
    ; cmp char to int
    cmp     eax, esi
    je      .found
    inc     rdi
    jmp     .loop

.found:
    ; set eax to found char
    mov     rax, rdi
    jmp     .done

.done:
    ; break down stack frame
    mov     rsp, rbp
    pop     rbp
    ret