#include "calc.h"

class ParseError : public std::exception {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "Can't parse expression";
  }
};

double calculate(std::string &op, double x, double y) {
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
}

bool isOperator(std::string str) {
  if (str == "+" ||
      str == "-" ||
      str == "*" ||
      str == "/" ||
      str == "^") {
    return true;
  } else {
    return false;
  }
}

double read(const std::string &str) {
  try {
    return std::stod(str);
  }
  catch (...) {
    throw ParseError();
  }
}

bool isDouble(std::string &str) {
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
    if (isDouble(op)) {
      st.push(read(op));
    }
    if (op.size() == 1 && isOperator(op)) {
      st.push(calculate(op, st.pop(), st.pop()));
    }
  }
  return st.pop();
}

std::string show(char ch) {
  std::string str;
  str += ch;
  return str;
}

char unshow(std::string str) {
  return str[0];
}

int operatorPriority(std::string &op) {
  if (op == ")") {
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
}

bool isLowerPriority(std::string ref, std::string comp) {
  if (ref == "^") {
    return operatorPriority(ref) > operatorPriority(comp);

  } else {
    return operatorPriority(ref) >= operatorPriority(comp);
  }
}

std::vector<std::string> Calculator::ParseExpression(std::string expr) {
  std::vector<std::string> dest;

  auto isNumberPart = [](char ch, char prev) {
    if (isdigit(ch) || isdigit(prev) && ch == '.' || prev == '(' && ch == '-') {
      return true;
    }
    return false;
  };

  std::string temp;

  for (auto current = expr.begin(); current != expr.end(); ++current) {
    if (isNumberPart(*current, current[-1])) {
      temp += *current;
      if (current == expr.end() - 1) {
        dest.push_back(temp);
      }
      continue;
    } else if (isNumberPart(current[-1], current[-2])) {
      dest.push_back(temp);
      temp = "";
    }
    if (*current == '(') {
      dest.push_back(show(*current));
      continue;
    }
    if (*current == ')') {
      dest.push_back(show(*current));
      continue;
    }
    if (isOperator(show(*current))) {
      dest.push_back(show(*current));
      continue;
    }
    if (*current == ' ') {
      continue;
    }

    throw ParseError();
  }

  return dest;
}

std::vector<std::string> Calculator::ConvertToPRN(std::vector<std::string> &expr) {
  stack<std::string> ops;
  std::vector<std::string> dest;

  for (auto str : expr) {
    if (isDouble(str)) {
      dest.push_back(str);
    }

    if (str == "(") {
      ops.push(str);
    }

    if (str == ")") {
      while (ops.top_elem() != "(") {
        dest.push_back(ops.pop());
      }
      // Remove '('
      ops.pop();
      continue;
    }

    if (isOperator(str)) {
      while (ops.size() > 0 && isLowerPriority(str, ops.top_elem())) {
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

bool Calculator::ExpressionIsValid(const std::vector<std::string> &expr) {
  stack<std::string> parens;
  stack<std::string> ops;

  try {
    for (auto current = expr.begin(); current != expr.end(); ++current) {
      if (*current == "(") {
        parens.push(*current);
        continue;
      }

      if (*current == ")") {
        try {
          parens.pop();
        } catch (...) {
          throw ParseError();
        }
        continue;
      }

      if (isOperator(*current)) {
        read(current[-1]);
        read(current[1]);
      }
    }
  } catch (ParseError &e) {
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
    } else if (input.empty()) {
    } else {
      auto expr = Calculator::ParseExpression(input);
      if (Calculator::ExpressionIsValid(expr)) {
        expr = Calculator::ConvertToPRN(expr);
      }
      auto res = Calculator::CalcExpression(expr);
      std::cout << res << std::endl;
    }
  }
}
