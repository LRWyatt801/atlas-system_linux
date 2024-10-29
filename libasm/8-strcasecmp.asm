BITS 64

section .text
    global asm_strcasecmp
    ; int asm_strcasecmp(const char *s1, const char *s2);
    ; rdi == s1
    ; rsi == s2

asm_strcasecmp:
    ; set up stack frame
    push    rbp
    mov     rbp, rsp



    ; breakdown stack frame
    mov     rsp, rbp
    pop     rbp
    ret