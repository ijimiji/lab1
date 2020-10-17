class Fraction {
  private:
    int denominator;
    int numerator;
    int integer;
    void DumbAdd(const Fraction &);
    void DumbMultiply(const Fraction &);
    void DumbDivide(const Fraction &);
  public:
    Fraction();
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
    void ConvertToIrregural();
    void Print();
    static int GCD(int, int);
    static int LCM(int, int);
};
