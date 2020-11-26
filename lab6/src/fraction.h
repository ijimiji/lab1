#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ostream>

struct FractionConstructionFailed : public std::exception
{
  const char * what () const throw ()
  {
    return "Can't create fraction with denominator of zero";
  }
};

struct ZerosInGCD : public std::exception
{
  const char * what () const throw ()
  {
    return "Can't find GCD of both zeros";
  }
};

class Fraction {
  private:
    int denominator;
    int numerator;
    void DumbAdd(const Fraction &);
    void DumbMultiply(const Fraction &);
    void DumbDivide(const Fraction &);
    Fraction();

  public:
    Fraction(int, int);
    Fraction(int, int, bool);
    Fraction(const Fraction &);
    int GetNumerator();
    int GetDenominator();
    void SetNumerator(int);
    void SetDenominator(int);
    void Multiply(const Fraction &);
    void Divide(const Fraction &);
    void Add(const Fraction &);
    void Add(const Fraction &, bool);
    void Multiply(const Fraction &, bool);
    void Divide(const Fraction &, bool);
    void ConvertToSimple();
    std::string to_string();
    void Print();
    static int GCD(int, int);
    static int LCM(int, int);
};
