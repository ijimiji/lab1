#include "app.h"
#include "fraction.h"
#include <iostream>

void App::Main() {
  Fraction r1(2, 4, true);
  Fraction r2(7, 4, true);
  Fraction r3(17, 3);
  Fraction r4(3, 17);
  r1.Add(r2);
  std::cout << Fraction::GCD(-2, 4) << std::endl;
  r1.Print();

}
