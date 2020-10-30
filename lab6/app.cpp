#include "app.h"
#include "fraction.h"
#include <iostream>

void App::Main() {
  Fraction a(2, 4, true);
  a.Print(); // => 1/2
  Fraction b(2, 4, false);
  b.Print(); // => 2/4
  Fraction c(4, 2, true);
  c.Print(); // => 2
  Fraction d(-4, 2, true);
  d.Print(); // => -2
  Fraction e(1, 0, true);
  d.Print(); // => -2
  
}
