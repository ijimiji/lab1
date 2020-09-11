#include <cmath>
#include <iomanip>
#include <iostream>

int factorial(int n) { return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n; }

// Refactor
double get_taylor_member(double x, int i) { return pow(x, i) / factorial(i); }

int main() {
    double x;
    int k;
    std::cout << "Enter x ";
    std::cin >> x;
    std::cout << "Enter k ";
    std::cin >> k;
    double accuracy = pow(10, -k);
    double result = 0;
   
    for (int i = 1; i; i += 2) {
        double taylor_member = get_taylor_member(x, i);
        if (taylor_member > 0 && taylor_member < accuracy) break;
        result += taylor_member;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(k);
    std::cout << "The result is " << result << std::endl;
    std::cout << "Result form std is " << sinh(x) << std::endl;
   
    return 0;
}
