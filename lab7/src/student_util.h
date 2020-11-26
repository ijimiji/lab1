#include "student.h"
#include "first_term_student.h"
#include "second_term_student.h"
#include <utility>

#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H
bool StudentIsPresent(Student*, std::vector<Student *>&);
class StudentUtil {
public:
    static std::vector<Student *> GetStudents();
    static double CalculateAverageMarkOfGroupAfterSession(int group, int session);
    static double CalculateAverageMarkOfAll();
};

#endif