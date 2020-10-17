#include "app.h"
#include "fraction.h"

void App::Main() {
  Fraction r1(1, 2, true);
  Fraction r2(2, 4, true);
  Fraction r3(17, 3);
  Fraction r4(3, 17);

  r1.Add(r2);
  r3.Multiply(r4, true);
  r1.Print();
  r3.Print();

}
