; Macro to format asm function
; in C-style
%macro export_function 1
global %1, _%1
_%1:
%endmacro

section .text

export_function dot
dot:
    push rbp
    mov rbp, rsp
    ; a = rdi
    ; b = rsi
    ; c = rdx
    ; n = ecx
    xor r8d, r8d
    mov r10, rdx

    for_begin:
    cmp r8d, ecx
    je for_end

    mov ebx, dword [rdi]
    add rdi, 4
    mov eax, dword  [rsi]
    add rsi, 4

    imul ebx

    add DWORD [r10],   eax
    adc DWORD [r10+4], edx
    adc DWORD [r10+8], 0

    inc r8d
    jmp for_begin
    for_end:

    pop rbp
    ret