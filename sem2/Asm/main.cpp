#include <iostream>

using namespace std;

int Calculate(int a, int b, int c, int y)
{
    int result;
    __asm
    {
        mov eax, a
        imul eax, 3
        mov ecx, eax

        mov eax, b
        mov ebx, y
        imul eax, ebx

        mov ebx, c
        add eax, ebx
        neg eax
        cdq
        idiv ecx

        cmp edx, 0
        jne rnd
        jmp end_if

        rnd :
        imul edx, 2
            cmp edx, ecx
            jg increase
            jmp skip

            increase :
        inc eax
            jmp end_if
            skip :

        cmp edx, ecx
            jl end_if

            mov ecx, eax
            mov ebx, 2
            cdq
            idiv ebx
            cmp edx, 0
            je end_if
            mov eax, ecx
            inc eax

            end_if :
        mov result, eax
    }
    return result;
}

int main() {
    int a, b, c, y;
    cout << "Enter a, b, c, y: ";
    cin >> a; cin >> b; cin >> c; cin >> y;
    cout << Calculate(a, b, c, y) << endl;
    return 0;
}
