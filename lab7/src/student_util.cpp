#include "student_util.h"

std::vector<std::pair<STermStudent*, StudentType>> StudentUtil::GetStudents() {
    std::vector<std::pair<STermStudent*, StudentType>> students;

    for (auto student : Student::students) {
        auto ptr = static_cast<STermStudent*>(student);
        students.push_back(std::make_pair(ptr, STUDENT));
    }

    for (auto student : FTermStudent::students) {
        auto ptr = static_cast<STermStudent*>(student);
        students.push_back(std::make_pair(ptr, FTERMSTUDENT));
    }

    for (auto student : STermStudent::students) {
        students.push_back(std::make_pair(student, STERMSTUDENT));
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
        return 0;
    }
    else if (session == 2) {
        auto students = STermStudent::GetStudents();
        for (auto student : students) {
            if (student->group == group) {
                sum += student->GetAverageMark();
                ++amountOfStudents;
            }
            if (amountOfStudents) {
                return sum / amountOfStudents;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

double StudentUtil::CalculateAverageMarkOfAll() {
    double sum = 0; int amountOfStudents = 0;
    auto students = GetStudents();
    for (auto student : students) {
        if (student.second == STERMSTUDENT) {
            sum += student.first->GetAverageMark();
            ++amountOfStudents;
        }
        else if (student.second == FTERMSTUDENT) {
            auto ptr = static_cast<FTermStudent*>(student.first);
            sum += ptr->GetAverageMark();
            ++amountOfStudents;
        }
    }
    if (amountOfStudents != 0) {
        return sum / amountOfStudents;
    }
    return 0;
}