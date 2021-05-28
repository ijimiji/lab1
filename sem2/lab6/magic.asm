%macro export_function 1
global %1, _%1
_%1:
%endmacro

section .data
    n: dd 0
    offset: dd 2
    p: dd 0

section .text

export_function IsMagicSquare
IsMagicSquare:
    push   rbp
    mov    rbp,rsp

    mov eax, esi
    mov ebx, 2
    mul ebx
    mov dword [offset], eax
    dec esi
    mov dword [n], esi

    mov ecx, dword [n]
    mov r8d, 0
    mov rax, rdi
    mov rax, [rax] ;**

    main_diag_beg:
        mov ebx, [rax]
        add r8d, ebx
        add eax, dword [offset]
    loop main_diag_beg

    mov eax, r8d
    pop    rbp
    ret  