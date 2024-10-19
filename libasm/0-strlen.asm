BITS 64

section .data
    ; no global data to set

section .text
            ; size_t asm_strlen(const char *str)
            ; count the number of characters in a string (str)
            ; size_t count = 0
            ; for (count = 0; str[count] != '\0'; count++)
            ;   ;
            ; return (count)

global asm_strlen       ; export asm_strlen

asm_strlen: ; Label for function
    ; setting up stack frame
    push    rbp                 ; Push base pointer to stack
    mov     rbp, rsp            ; Set stack pointer to base pointer

    ; Begin function logic
    xor     rcx, rcx            ; zero(0) out counter register

    ; Set up for loop
.loop: ; Loop label / start of loop
    cmp     byte[rdi, rcx], 0   ; Check byte for '\0'
    jz      .done               ; If byte is NULL jump to lable .done
    inc     rcx                 ; rcx++
    jmp     .loop               ; jump to .loop / start loop over

.done ; Lable for breaking out of loop
    mov     rax, rcx            ; Set return register = to count (rcx)

    ; pop stack and return
    mov     rsp, rbp            ; return to previous pointer
    pop     rbp                 ; pop rbp from stack
    ret                         ; return from function
