#include "first_term_student.h"

std::vector<FTermStudent*> FTermStudent::students;

FTermStudent::FTermStudent(const Student& student, std::array<int, 4> ftermMarks)
    : Student(student), ftermMarks(ftermMarks) {
    students.push_back(this);
};

FTermStudent::FTermStudent(const Student& student, int mark1, int mark2, int mark3, int mark4)
    : Student(student) {
    std::array<int, 4>  marks;
    marks[0] = mark1;
    marks[1] = mark2;
    marks[2] = mark3;
    marks[3] = mark4;
    ftermMarks = marks;
    students.push_back(this);
};

FTermStudent::FTermStudent(const FTermStudent& student)
    : Student(student),
    ftermMarks(student.ftermMarks) {
}

double FTermStudent::GetAverageMark() {
    int sum = 0;
    for (int mark : ftermMarks) {
        sum += mark;
    }
    return sum / 4.0;
}

void FTermStudent::ChangeMarks(std::array<int, 4> marks) {
    ftermMarks = marks;
}
std::array<int, 4> FTermStudent::GetMarks() const {
    return ftermMarks;
}

std::ostream& operator<<(std::ostream& os, const FTermStudent& student) {
    printf("%s is a %d course student from the group number %d\n",
        student.name, student.course, student.group);
    printf("His/her first term marks marks are: ");
    for (auto mark : student.GetMarks()) {
        printf("%d ", mark);
    }
    return os;
}