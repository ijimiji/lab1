#include "student_util.h"

bool StudentIsPresent(Student* ref, std::vector<Student*>& students) {
    bool is_present = false;
    for (auto student : students) {
        if (student == ref) {
            is_present = true;
            break;
        }
    }
    return is_present;
}

std::vector<Student*> StudentUtil::GetStudents() {
    std::vector<Student*> students;
    for (auto student : Student::students) {
        if (!StudentIsPresent(student, students)) {
            students.push_back(student);
        }
    }

    for (auto student : FTermStudent::students) {
        if (!StudentIsPresent(student, students)) {
            students.push_back(student);
        }
    }

    for (auto student : STermStudent::students) {
        if (!StudentIsPresent(student, students)) {
            students.push_back(student);
        }
    }

    return students;
}

double StudentUtil::CalculateAverageMarkOfGroupAfterSession(int group, int session) {
    double sum = 0; int amountOfStudents = 0;

    if (session == 1) {
        auto students = FTermStudent::GetStudents();
        for (auto student : students) {
            if (student->group == group) {
                sum += student->GetAverageMark();
                ++amountOfStudents;
            }
        }

        if (amountOfStudents) {
            return sum / amountOfStudents;
        }
    }

    else if (session == 2) {
        auto students = STermStudent::GetStudents();
        for (auto student : students) {
            if (student->group == group) {
                sum += student->GetAverageMark();
                ++amountOfStudents;
            }
        }

        if (amountOfStudents) {
            return sum / amountOfStudents;
        }
    }

    return 0;
}

double StudentUtil::CalculateAverageMarkOfAll() {
    double sum = 0;
    double mark;
    int amountOfStudents = 0;

    auto students = GetStudents();

    for (auto student : students) {
        mark = student->GetAverageMark();
        if (mark) {
            sum += mark;
            ++amountOfStudents;
        }
    }

    if (amountOfStudents) {
        return sum / amountOfStudents;
    }

    return 0;
}