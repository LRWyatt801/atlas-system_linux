BITS 64

section .data
    ; no global data to set

section .text
           ;int _strcmp(char *s1, char *s2)
           ; {
           ;    for ( ; *s1 == *s2; s1++, s2++)
           ;        if (*s1 == '\0' && *s2 == '\0')
           ;            return (0);
           ;    return (*s1 - *s2);
           ; }

global asm_strncmp       ; export asm_strcmp

asm_strncmp: ; Label for function
    ; setting up stack frame
    push    rbp
    mov     rbp, rsp

    xor     rcx, rcx

    ; Set up for loop
.strcmploop: ; Loop label / start of loop

        ; rdi == str1
        ; rsi == str2
        ; rdx == n

    ; check if at n bytes
    cmp     rcx, rdx
    jz      .all_bytes_read

    ; load bytes
    mov     r10b, byte[rdi]
    mov     r11b, byte[rsi]

    ; check each str for '\0'
    cmp     r10b, 0
    jz      .end_of_str1
    cmp     r11b, 0
    jz      .end_of_str2

    ; compare char
    cmp     r10b, r11b
    jl      .end_of_str1
    jg      .end_of_str2

    ; str1[i] == str2[i]
    inc     rdi
    inc     rsi
    inc     rcx
    jmp     .strcmploop

.all_bytes_read: ; label for when rcx == n bytes
    xor     rax, rax
    jmp     .exit

.end_of_str1: ; label for end of str1
    cmp     r11b, 0
    jz      .strs_equal
    mov     rax, -1
    jmp     .exit

.end_of_str2: ; label for end of str2
    ; str1 != NULL && str2 == NULL
    mov     rax, 1
    jmp     .exit

.strs_equal: ; label for strings are equal
    xor     rax, rax
    jmp     .exit

.exit: ; label for exiting func
    ; pop stack and return
    mov     rsp, rbp
    pop     rbp
    ret
