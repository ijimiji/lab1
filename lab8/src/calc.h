#ifndef CALC_H
#define CALC_H 

#include <string>
#include <vector>
#include "stack_array.h"
#include <map>
#include <string.h>

class Calculator{
public:
    Calculator(){};
    static void Run();
    static double CalcExpression(std::vector<std::string> expr);
    static std::vector<std::string> ConvertToPRN(std::string expr);
    static bool ExpressionIsValid(std::string);
};
#endif