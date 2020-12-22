#ifndef CALC_H
#define CALC_H

#include "stack_array.h"
#include <string>
#include <vector>
#include <exception>
#include <regex>

bool is_double(std::string &str);

class Calculator {
 public:
  static void Run();
  static double CalcExpression(std::vector<std::string> expr);
  static std::vector<std::string> ConvertToPRN(std::vector<std::string> &expr);
  static bool ExpressionIsValid(std::vector<std::string> input);
  static std::vector<std::string> ParseExpression(std::string);
};
#endif
