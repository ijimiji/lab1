#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    double x;
    std::cout << "Enter x ";
    std::cin >> x;
    int k; // unsigned int can't be used as negative power in pow
    std::cout << "Enter k ";
    std::cin >> k;
    double accuracy = pow(10, -k);
   
    double taylor_member = x; // First member is always equals x
    double result = taylor_member; // First cycle approximation is always x
    if (!(taylor_member > 0 && taylor_member < accuracy))
    for (int i = 3; i; i += 2) {
        taylor_member = taylor_member * x * x / i / (i-1);
        // Finish calculations if a member is accurate enough
        if (taylor_member > 0 && taylor_member < accuracy) break; 
        result += taylor_member;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(k);
    std::cout << "The result is " << result << std::endl;
    std::cout << "Result form std is " << sinh(x) << std::endl;
    return 0;
}
