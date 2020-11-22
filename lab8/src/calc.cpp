#include "calc.h"

double calculate(std::string op, double x, double y) {
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

bool isOperator(char ch) {
    switch (ch) {
    case '+':
        return true;
    case '-':
        return true;
    case '*':
        return true;
    case '/':
        return true;
    case '^':
        return true;
    default:
        return false;
    }
}

double read(std::string str) {
    return std::stod(str.c_str());
}

bool isdouble(std::string str) {
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
        if (isdouble(op)) {
            st.push(read(op));
        }
        if (op.size() == 1 && isOperator(op[0])) {
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

bool isOpenParen(char ch) {
    if (ch == '(') {
        return true;
    }
    return false;
}

bool isCloseParen(char ch) {
    if (ch == ')') {
        return true;
    }
    return false;
}

bool isROperator(char ch) {
    if (ch == '^') {
        return true;
    }
    return false;
}



int operatorPriority(char ch) {
    switch (ch) {
    case '+':
        return 6;
    case '-':
        return 6;
    case '*':
        return 5;
    case '/':
        return 5;
    case '^':
        return 4;
    case '(':
        return 1000;
    }
}

bool isLowerPriority(char ref, char comp) {
    if (isROperator(ref)) {
        return operatorPriority(ref) > operatorPriority(comp);

    }
    else {
        return operatorPriority(ref) >= operatorPriority(comp);
    }
}
std::vector<std::string> Calculator::ConvertToPRN(std::string expr) {
    stack<char> st;
    bool is_right_operator;
    std::vector<std::string> dest;
    std::string temp;
    bool reading_number = false;
    bool last_is_operator = true;
    int i = 0;
    int n = expr.length();
    for (char ch : expr) {
        ++i;
        if (isdigit(ch) || ch == '.' || (last_is_operator && ch == '-')) {
            last_is_operator = false;
            temp = temp + ch;
            reading_number = true;
            if (i == n) {
                dest.push_back(temp);
            }
            continue;
        }
        else if (reading_number) {
            dest.push_back(temp);
            temp = "";
            reading_number = false;
        }

        if (isOpenParen(ch)) {
            st.push(ch);
            continue;
        }

        if (isCloseParen(ch)) {
            while (st.top_elem() != '(') {
                dest.push_back(show(st.pop()));
            }

            st.pop(); // Remove '('
            continue;
        }

        if (isOperator(ch)) {

            last_is_operator = true;
            while (st.size() > 0 && isLowerPriority(ch, st.top_elem())) {
                dest.push_back(show(st.pop()));
            }

            st.push(ch);
        }
    }

    n = st.size();
    for (i = 0; i < n; ++i) {
        dest.push_back(show(st.pop()));
    }
    return dest;
}

bool Calculator::ExpressionIsValid(std::string) {

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
        }
        else if (input == "") {
        } else {
            auto rpn = Calculator::ConvertToPRN(input);
            // for (auto x : rpn){
            //     std::cout << x << " ";
            // }
            // std::cout << std::endl;
            auto res = Calculator::CalcExpression(rpn);
            std::cout << res << std::endl;
        }
    }
}