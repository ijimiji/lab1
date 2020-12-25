#include "fraction.h"
#include <exception>



Fraction::Fraction(Fraction const& fraction) {
    numerator = fraction.numerator;
    denominator = fraction.denominator;
}

Fraction::Fraction(int a, int b) {
    if (b == 0) {
        throw FractionConstructionFailed();
    }
    numerator = a;
    denominator = b;

}

Fraction::Fraction(int a, int b, bool simplify) {
    if (b == 0) {
        throw FractionConstructionFailed();
    }
    numerator = a;
    denominator = b;
    if (simplify) {
        ConvertToSimple();
    }
}

std::string Fraction::to_string() {
    std::string out;
    bool isNegative = false;
    int _numerator = numerator;
    int _denominator = denominator;

    if (_numerator * _denominator < 0) {
        _numerator = std::abs(_numerator);
        _denominator = std::abs(_denominator);
        isNegative = true;
    }

    int integer = _numerator / _denominator;
    _numerator = _numerator - integer * _denominator;

    if (integer && isNegative && _numerator != 0) {
        out += "-(";
    }
    else if (isNegative) {
        out += "-";
    }

    if (integer != 0) {
        out += std::to_string(integer);
    }

    if (_numerator != 0) {
        out += ((integer != 0) ? " + " : "");
        out += std::to_string(_numerator);
        out += "/";
        out += std::to_string(_denominator);
    }

    if (_numerator == 0 && integer == 0) {
        out += "0";
    }


    if (integer && isNegative && _numerator != 0) {
        out += ")";
    }

    return out;
}
void Fraction::Print() {
    std::cout << to_string();
    std::cout << std::endl;
}

int Fraction::GCD(int a, int b) {
    if (a == 0 && b == 0){
        throw ZerosInGCD();
    }
    a = std::abs(a);
    b = std::abs(b);
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        }
        else {
            b = b % a;
        }
    }
    return std::abs(a + b);
}

int Fraction::LCM(int a, int b) { return std::abs(a * b) / GCD(a, b); }

void Fraction::ConvertToSimple() {
    int gcd = GCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;

    if (numerator < 0 && denominator < 0){
        numerator = std::abs(numerator); 
        denominator = std::abs(denominator);
    }
    if (numerator == 0 && denominator < 0){
        denominator = std::abs(denominator);
    }
}

int Fraction::GetDenominator() { return denominator; }

int Fraction::GetNumerator() { return numerator; }

void Fraction::SetNumerator(int number) { numerator = number; }

void Fraction::SetDenominator(int number) { 
    if (number == 0){
        throw FractionConstructionFailed();
    }
    denominator = number; 
}

void Fraction::DumbDivide(Fraction const& number) {
    if (number.numerator == 0){
        throw FractionConstructionFailed();
    }
    numerator = numerator * number.denominator;
    denominator = denominator * number.numerator;
};

void Fraction::Divide(Fraction const& number) { DumbDivide(number); }

void Fraction::Divide(Fraction const& number, bool simplify) {
    DumbDivide(number);
    if (simplify)
        ConvertToSimple();
};

void Fraction::DumbMultiply(Fraction const& number) {
    numerator = number.numerator * numerator;
    denominator = number.denominator * denominator;
};

void Fraction::Multiply(Fraction const& number) { DumbMultiply(number); }

void Fraction::Multiply(Fraction const& number, bool simplify) {
    DumbMultiply(number);
    if (simplify)
        ConvertToSimple();
};

void Fraction::DumbAdd(Fraction const& number) {
    int lcm = LCM(denominator, number.denominator);
    int FirstMultiple = lcm / denominator;
    int SecondMultiple = lcm / number.denominator;
    numerator = numerator * FirstMultiple;
    denominator = denominator * FirstMultiple;
    int secondNumerator = number.numerator * SecondMultiple;
    numerator = numerator + secondNumerator;
};

void Fraction::Add(Fraction const& number) { DumbAdd(number); }

void Fraction::Add(Fraction const& number, bool simplify) {
    DumbAdd(number);
    if (simplify)
        ConvertToSimple();
};

