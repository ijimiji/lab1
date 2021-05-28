%macro export_function 1
global %1, _%1
_%1:
%endmacro

section .data
    buffer dd 0.0
    rad dd 57.2957795
    eps dd 0.1
section .text

export_function asinInt
asinInt:
   	push   rbp
   	mov    rbp,rsp

    finit
    movss dword [buffer], xmm0

    fld dword [buffer]
    fld dword [buffer]
    fld dword [buffer]
    fmul
    fld1
    fsubr
    fsqrt
    fpatan
    fmul dword [rad]
    fistp dword [buffer]
    mov eax, dword [buffer]

   	pop rbp
   	ret    

export_function CalculateSh
CalculateSh:
   	push   rbp
   	mov    rbp,rsp

    movss dword [buffer], xmm0
    movss dword [eps], xmm1

    finit
    fld1
    fld dword [buffer]
    fld  st0
    fmul st1, st0
    fld  st0

    for_begin:
        fmul  st0, st2
        fld1
        faddp st4, st0
        fdiv  st0, st3
        fld1
        faddp st4, st0
        fdiv  st0, st3
        fadd  st1, st0
        fld   st0
        fabs
        fcomp dword [eps]
        fstsw ax
        sahf
    jae for_begin

    fxch st1
    fstp dword [buffer]
    movss xmm0, dword [buffer]

   	pop rbp
   	ret    
