#include "student.h"

#include <array>
#ifndef FIRST_TERM_STUDENT_H
#define FIRST_TERM_STUDENT_H
class FTermStudent {
  public:
    std::array<int, 4> ftermMarks;
    FTermStudent(const Student&, std::array<int, 4>);

};
#endif
