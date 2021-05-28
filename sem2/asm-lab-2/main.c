#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

bool triangle_p(uint32_t a, uint32_t b, uint32_t c);

bool isTriangle(uint32_t a, uint32_t b, uint32_t c){
    return 
        triangle_p(a, b, c) && 
        triangle_p(b, a, c) && 
        triangle_p(b, c, a);
}

void dot(int* a, int* b, int* c,  int n);

int main(){
    int a[2] = {5, 2};
    int b[2] = {1, 4};
    int c[3] = {0, 0, 0};
    dot(a, b, c, 2);
    printf("%d %d %d\n", c[2], c[1], c[0]);
    printf("%d\n", isTriangle(5, 3, 4));
    // free(c);
    return 0;
}