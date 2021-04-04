%macro export_function 1
global %1, _%1
_%1:
%endmacro

section .text
export_function IsPalindrom
export_function DeleteBraces

IsPalindrom:
    mov ecx, 0 ; Find len of str
    mov eax, 0 ; Search for NULL
    beg:
        scasb
        je end_if
        add ecx, 1
        jmp beg
    end_if:
    mov rsi, rdi ; Save pointer to the end
    sub rsi, 2 
    sub rdi, rcx ; Restore pointer to the beginning
    sub rdi, 1
    mov rax, rcx ; Divide len by two
    mov rbx, 2
    div rbx
    mov rcx, rax
    cmp rcx, 0
    je pal
    check: ; Check for q == from both sides
        cmpsb
        jne not_pal
        sub rsi, 2
        sub rcx, 1
        cmp rcx, 0
        jne check
    pal:
        mov eax, 1
        jmp end
    not_pal:
        mov eax, 0
        jmp end
    end:
    ret

DeleteBraces:
    mov ecx, esi ; Len
    mov rsi, rdi ; Old string
    mov ebx, 0   ; New len
    mov edx, 0   ; Flag for brace
    mov eax, 0   ; Current char
    loop_beg:
        lodsb
        cmp eax, 40 ; (
        je is_open
        cmp eax, 41 ; )
        je is_closed
        cmp edx, 1 
        je loop_end
            stosb
            inc ebx
            jmp loop_end
        is_open:
            mov edx, 1
            jmp loop_end
        is_closed:
            mov edx, 0
    loop_end:
    loop loop_beg
    mov eax, 0
    stosb ; Terminate just in case
    mov eax, ebx
    ret