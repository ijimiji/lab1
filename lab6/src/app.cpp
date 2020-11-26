#include "app.h"
#include "fraction.h"
#include <iostream>

void App::Main() {
    Fraction a(2, 4, true);
    a.Print(); // => 1/2
    Fraction b(2, 4);
    b.Print(); // => 2/4
    Fraction c(4, 2, true);
    c.Print(); // => 2
    Fraction d(-4, 2, true);
    d.Print(); // => -2
    // Fraction e(1, 0, true); // Error: Can't create Fraction object with 0 as
    // a denominator
    Fraction f(-1, 2);
    Fraction g(1, 3);
    f.Divide(g);
    f.Print(); // -(1 + 1/2) aka -(3/2)

    Fraction k(2, 4);
    Fraction l(2, 4, true);
    k.Add(l, true);
    k.Print(); // 1

    Fraction k1(2, 4);
    Fraction l1(-2, 4, true);
    k1.Add(l1, true);
    k1.Print(); // 0

    Fraction x(13, 5);
    Fraction y(10, 13, true);
    x.Multiply(y);
    x.Print(); // 2

    Fraction t(12, 3);
    Fraction z(5, 13);
    t.Multiply(z, false);
    std::cout << t.GetNumerator() << "/" << t.GetDenominator()
              << std::endl; // 60/39
    t.Print();              // 1 + 7/13 aka 20/13
    Fraction gg(1, 0);
}
