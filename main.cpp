#include <iostream>
#include <cmath>

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double get_taylor_member(double x, int i){
    return pow(x, i) / factorial(i);
}

int main(){
    double x;
    unsigned int k;
    double result = 0;
    double epsilon = 0.1;

    for (int i;;i+=2){
        if (result < epsilon){
            break;
        }
        result += get_taylor_member(x, i);
    }

    return 0;
}

