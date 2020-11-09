#include "student.h"
#include "first_term_student.h"
#ifndef SECOND_TERM_STUDENT_H
#define SECOND_TERM_STUDENT_H

class STermStudent : Student, FTermStudent {
 public:
  std::array <int, 5> stermMarks;
  STermStudent(FTermStudent, std::array <int, 5>);
};
#endif
