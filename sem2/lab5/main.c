#include "stdbool.h"
#include "stdio.h"
#include "stdint.h"
#include "math.h"

int32_t asinInt(float x);
float CalculateSh(float x, float eps);

int main(){
    printf("%d\n", asinInt(1));
    printf("%f\n", CalculateSh(2, 0.1));
    return 0;
}
