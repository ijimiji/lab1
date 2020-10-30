#include "fraction.h"
#include <cstdlib>
#include <iostream>
#include <ostream>


Fraction::Fraction(Fraction const &fraction) {
    numerator = fraction.numerator;
    denominator = fraction.denominator;
}

Fraction::Fraction(int a, int b) {
    numerator = a;
    denominator = b;
}

Fraction::Fraction(int a, int b, bool simplify) {
  if (b == 0){
    std::cout << "Can't create Fraction object with 0 as a denominator" << std::endl;;
    std::exit(1);
  }
  numerator = a;
    denominator = b;
    if (simplify){
        ConvertToSimple();
    }
}

Fraction::Fraction() {
    std::cout << "I'm a simple program. I see no number, I do exit."
              << std::endl;
    std::exit(1);
}

void Fraction::Print() {
    bool isNegative = false;

    if (numerator * denominator < 0) {
      numerator = std::abs(numerator);
      denominator = std::abs(denominator);
      isNegative = true;
    }
    
    int integer = numerator / denominator;
    numerator = numerator - integer * denominator;
    
    if (isNegative && numerator != 0){
       std::cout << "-(";
    } else if(isNegative){
      std::cout << "-";
    }
    
    if (integer != 0) {
        std::cout << integer;
    }
    
    if (numerator != 0) {
        std::cout << ((integer != 0) ? " + " : "") << numerator << "/"
                  << denominator;
    }

    if (numerator == 0 && integer == 0) {
        std::cout << 0;
    }

    
    if (isNegative && numerator != 0){
        std::cout << ")";
    }

    std::cout << std::endl;
}

int Fraction::GCD(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return std::abs(a + b);
}

int Fraction::LCM(int a, int b) { return std::abs(a * b) / GCD(a, b); }

void Fraction::ConvertToSimple() {
    int gcd = GCD(abs(numerator), abs(denominator));
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

int Fraction::GetDenominator() { return denominator; }

int Fraction::GetNumerator() { return numerator; }

void Fraction::SetNumerator(int number) { numerator = number; }

void Fraction::SetDenominator(int number) { denominator = number; }

void Fraction::DumbDivide(Fraction const &number) {
    numerator = numerator * number.denominator;
    denominator = denominator * number.numerator;
};

void Fraction::Divide(Fraction const &number) { DumbDivide(number); }

void Fraction::Divide(Fraction const &number, bool simplify) {
    DumbDivide(number);
    if (simplify)
        ConvertToSimple();
};

void Fraction::DumbMultiply(Fraction const &number) {
    numerator = number.numerator * numerator;
    denominator = number.denominator * denominator;
};

void Fraction::Multiply(Fraction const &number) { DumbMultiply(number); }

void Fraction::Multiply(Fraction const &number, bool simplify) {
    DumbMultiply(number);
    if (simplify)
        ConvertToSimple();
};

void Fraction::DumbAdd(Fraction const &number) {
    int lcm = LCM(denominator, number.denominator);
    int FirstMultiple = lcm / denominator;
    int SecondMultiple = lcm / number.denominator;
    numerator = numerator * FirstMultiple;
    denominator = denominator * FirstMultiple;
    int secondNumerator = number.numerator * SecondMultiple;
    numerator = numerator + secondNumerator;
};

void Fraction::Add(Fraction const &number) { DumbAdd(number); }

void Fraction::Add(Fraction const &number, bool simplify) {
    DumbAdd(number);
    if (simplify)
        ConvertToSimple();
};

