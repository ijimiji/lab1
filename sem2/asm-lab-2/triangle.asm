; Macro to format asm function
; in C-style
%macro export_function 1
global %1, _%1
_%1:
%endmacro

section .text

export_function triangle_p
triangle_p:
    push rbp
    mov rbp, rsp
    ; UNIX style convention I guess
    ; a = edi
    ; b = esi
    ; c = edx
    ; check if a + c > b
    mov ecx, edi  
    add ecx, edx
    jc carry_sum
    cmp ecx, esi
    ja true
    jmp false
    ; We got carry!
    ; Bu no worries! We will check
    ; equivalent statement:
    ; a + c - c > b
    ; a         > b - c 
    carry_sum:
        sub esi, edx
        ; Carry again!
        ; No more carry!
        ; This case means that
        ; a + b is > c
        jc true
        cmp edi, esi
        ja true
        jmp false
    true:
        mov eax, 1
        jmp exit
    false:
        mov eax, 0
    exit:
        pop rbp
        ret