#include <cmath>
#include <iomanip>
#include <iostream>

double round(double x, int n) {
    int d = 0;
    if ((x * pow(10, n + 1)) - (floor(x * pow(10, n))) > 4) d = 1;
    x = (floor(x * pow(10, n)) + d) / pow(10, n);
    return x;
}

int main() {
    double x;
    std::cout << "Enter x ";
    std::cin >> x;
    int k;
    std::cout << "Enter k ";
    std::cin >> k;

    double accuracy = pow(10, -k);
    double a_n = 1, ch = 1;
    int i = 2;
    while (abs(a_n *= (x * x / i / (i - 1.0))) > accuracy) {
        ch += a_n;
        i += 2;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(k);
    std::cout << "The result is " << ch << std::endl;
    std::cout << "The result from std is " << cosh(x) << std::endl;
    std::cout << "The difference between the implementation and std is ";
    std::cout << abs(round(ch, k) - round(cosh(x), k)) << std::endl;
    return 0;
}
