%macro export_function 1
global %1, _%1
_%1:
%endmacro

%macro multiply 2
    push rax
    push rbx
    mov rax, %1
    mov rbx, %2
    mul rbx
    mov %1, rax
    pop rbx
    pop rax
%endmacro

%macro index 3
    push rdi
    push rsi
    push rdx
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    mov rax, rdi
    multiply rsi, 8
    add rax, rsi
    mov rax, [rax]
    multiply rdx, 2
    add rax, rdx
    mov rax, [rax]
    pop rdx
    pop rsi
    pop rdi
%endmacro

section .text

export_function IsMagicSquare
IsMagicSquare:
    push rbx
    mov rax, 0
    mov r10, 0
    mov rcx, 0
    main_diag_loop:
        index rdi, rcx, rcx
        add r10, rax
        inc ecx
        cmp ecx, esi
        je .end
        jmp main_diag_loop
    .end
    mov rbx, r10

    mov r8, rcx
    mov rcx, 0
    
    mov r10, 0
    sub_diag_loop:
        index rdi, rcx, r8
        add r10, rax
        inc rcx
        dec r8
        cmp ecx, esi
        je .end
        jmp sub_diag_loop
    .end
    cmp rbx, r10
    jne false

    mov r9, 0
    cols_loop:
        mov rcx, 0
        mov r10, 0
        sum_col:
            index rdi, rcx, r9
            add r10, rax
            inc rcx
            cmp ecx, esi
            je .end
            jmp sum_col
        sum_col.end:
    cmp r10, rbx
    jne false
    inc r9
    cmp r9d, esi
    je cols_loop.end
    jmp cols_loop
    cols_loop.end:

    mov r9, 0
    rows_loop:
        mov rcx, 0
        mov r10, 0
        sum_row:
            index rdi, r9, rcx
            add r10, rax
            inc rcx
            cmp ecx, esi
            je .end
            jmp sum_row
        sum_row.end:
    cmp r10, rbx
    jne false
    inc r9
    cmp r9d, esi
    je rows_loop.end
    jmp rows_loop
    rows_loop.end:

    true:
        mov eax, 1
        jmp end
    false:
        mov eax, 0
        jmp end

    end:
    pop rbx
    ret
