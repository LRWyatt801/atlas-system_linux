BITS 64

section .text
    global asm_strncasecmp
    ; int asm_strncasecmp(const char *s1, const char *s2);
    ; rdi == s1
    ; rsi == s2
    ; rdx == n

asm_strncasecmp:
    ; set up stack frame
    push    rbp
    mov     rbp, rsp

    xor     rax, rax

    ; check for null strs
    cmp     rdi, 0
    jz      .done
    cmp     rsi, 0
    jz      .done

.cmp_loop:
    cmp     rdx, 0
    jz      .done
    mov     al, byte[rdi]
    mov     bl, byte[rsi]

    ; check for '\0'
    cmp     al, 0
    jz      .greater_than
    cmp     bl, 0
    jz      .less_than

    ; convert to lowercase
    and     al, 0dfh
    and     bl, 0dfh

    cmp     al, bl
    jl      .less_than
    jg      .greater_than

    ; move to next char
    inc     rdi
    inc     rsi
    dec     rdx
    jmp     .cmp_loop

.less_than:
    sub     al, bl
    movzx   rax, al
    jmp     .done

.greater_than:
    cmp     bl, 0
    jz      .done
    sub     al, bl
    movzx   rax, al
    jmp     .done


.done:
    ; breakdown stack frame
    mov     rsp, rbp
    pop     rbp
    ret