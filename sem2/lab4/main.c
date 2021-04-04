#include "stdbool.h"
#include "stdio.h"
#include "stdint.h"

char IsPalindrom(char* string);
int DeleteBraces(char* string, int len);

int main(){
    char src[100];
    scanf("%s", src);
    printf("%d\n", IsPalindrom(src));
    char str[8] = "a(a)(a)a";
    int n = DeleteBraces(str, 8);
    printf("%s\n", str);
    printf("%d\n", n);
    return 0;
}