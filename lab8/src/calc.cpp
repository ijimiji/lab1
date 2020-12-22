#include "calc.h"

class ParseError : public std::exception {
public:
  [[nodiscard]] const char* what() const noexcept override {
    return "Can't parse expression";
  }
};
class CalcError : public std::exception {
public:
  [[nodiscard]] const char* what() const noexcept override {
    return "Can't calculate expression";
  }
};

std::vector<std::string> Calculator::ParseExpression(std::string expr) {
  std::vector<std::string> out;
  std::smatch match;
  std::regex number("(\\(|((\\+|-)?[0-9]+(\\.[0-9]+)?))");
  std::regex op("(\\)|[\\+\\-\\/\\^\\*])");
  bool is_number = true;
  while (std::regex_search(expr, match, (is_number ? number : op))) {
    if (!(match[0] == "(" || match[0] == ")")) {
      is_number = !is_number;
    }
    out.push_back(match[0]);
    expr = match.suffix();
  }
  return out;
}


double calculate(std::string& op, double x, double y) {
  if (op == "+") {
    return x + y;
  }
  if (op == "-") {
    return y - x;
  }
  if (op == "*") {
    return x * y;
  }
  if (op == "/") {
    return y / x;
  }
  if (op == "^") {
    return pow(y, x);
  }
  throw CalcError();
  return 0;
}

bool is_operator(std::string str) {
  if (str == "+" ||
    str == "-" ||
    str == "*" ||
    str == "/" ||
    str == "^") {
    return true;
  }
  else {
    return false;
  }
}

double read(const std::string& str) {
  try {
    return std::stod(str);
  }
  catch (...) {
    throw ParseError();
  }
}

bool is_double(std::string& str) {
  bool is_double = true;
  int n = str.size();
  for (char ch : str) {
    if (!((ch == '-' && n > 1) || isdigit(ch) || ch == '.')) {
      is_double = false;
    }
  }
  return is_double;
}

double Calculator::CalcExpression(std::vector<std::string> expr) {
  stack<double> st;
  if (expr.size() == 1) {
    return read(expr[0]);
  }
  for (auto op : expr) {
    if (is_double(op)) {
      st.push(read(op));
    }
    if (op.size() == 1 && is_operator(op)) {
      st.push(calculate(op, st.pop(), st.pop()));
    }
  }
  return st.pop();
}

int operator_priority(std::string& op) {
  if (op == "(") {
    return 1000;
  }
  if (op == "-") {
    return 6;
  }
  if (op == "+") {
    return 6;
  }
  if (op == "*") {
    return 5;
  }
  if (op == "/") {
    return 5;
  }
  if (op == "^") {
    return 4;
  }
  return -1;
}

bool is_lower_priority(std::string ref, std::string comp) {
  if (ref == "^") {
    return operator_priority(ref) > operator_priority(comp);

  }
  else {
    return operator_priority(ref) >= operator_priority(comp);
  }
}

std::vector<std::string> Calculator::ConvertToPRN(std::vector<std::string>& expr) {
  stack<std::string> ops;
  std::vector<std::string> dest;

  for (auto str : expr) {
    if (is_double(str)) {
      dest.push_back(str);
    }

    if (str == "(") {
      ops.push(str);
    }

    if (str == ")") {
      while (ops.top_elem() != "(") {
        dest.push_back(ops.pop());
      }
      ops.pop();
      continue;
    }

    if (is_operator(str)) {
      while (ops.size() > 0 && is_lower_priority(str, ops.top_elem())) {
        dest.push_back(ops.pop());
      }

      ops.push(str);
    }
  }
  int n = ops.size();

  for (int i = 0; i < n; ++i) {
    dest.push_back(ops.pop());
  }

  return dest;
}

bool Calculator::ExpressionIsValid(std::vector<std::string> raw) {
  int count = raw.size();
  int op_count = 0;
  int paren_count = 0;
  stack<std::string> parens;
  for (auto x : raw) {
    if (x == "(") {
      ++paren_count;
      parens.push(x);
    }
    if (x == ")") {
      ++paren_count;
      parens.pop();
    }
    if (is_operator(x)) {
      ++op_count;
    }
  }
  if (parens.size() != 0){
    return false;
  }
  if (op_count + 1 != count - paren_count - op_count) {
    return false;
  }
  return true;
}

void Calculator::Run() {
  bool running = true;
  std::string input;
  std::cout << "Type \":q\" to exit" << std::endl;
  while (running) {
    std::cout << ">>> ";
    std::getline(std::cin, input);

    if (input == ":q") {
      running = false;
      break;
    }

    if (input.empty()) {
      continue;
    }

    auto expr = ParseExpression(input);

    if (Calculator::ExpressionIsValid(expr)) {
      expr = Calculator::ConvertToPRN(expr);
      auto res = Calculator::CalcExpression(expr);
      std::cout << res << std::endl;
    }
    else {
      std::cout << "Expression is invalid" << std::endl;
    }
  }
}
