#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    double x;
    std::cout << "Enter x ";
    std::cin >> x;
    int k;
    std::cout << "Enter k ";
    std::cin >> k;

    double accuracy = pow(10, -k);
    double a_n = x, sh = x;
    int i = 3;
    while (abs(a_n *= (x * x / i / (i - 1.0))) > accuracy) {
        sh += a_n;
        i += 2;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(k);
    std::cout << "The result is " << sh << std::endl;
    std::cout << "Result form std is " << sinh(x) << std::endl;
    return 0;
}
