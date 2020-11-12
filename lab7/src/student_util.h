#include "student.h"
#include "first_term_student.h"
#include "second_term_student.h"
#include <utility>

#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H

enum StudentType { STUDENT, FTERMSTUDENT, STERMSTUDENT };
class StudentUtil {
public:
    static std::vector<std::pair<STermStudent*, StudentType>> GetStudents();
    static double CalculateAverageMarkOfGroupAfterSession(int group, int session);
    static double CalculateAverageMarkOfAll();
};

#endif