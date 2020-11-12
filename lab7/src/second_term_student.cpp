#include "second_term_student.h"

STermStudent::STermStudent(const FTermStudent& student, std::array <int, 5> marks)
    :FTermStudent(student), stermMarks(marks) {
    students.push_back(this);
}

std::vector<STermStudent*> STermStudent::students;

STermStudent::STermStudent(const FTermStudent& student, int mark1, int mark2, int mark3, int mark4, int mark5)
    : FTermStudent(student) {
    std::array<int, 5>  marks;
    marks[0] = mark1;
    marks[1] = mark2;
    marks[2] = mark3;
    marks[3] = mark4;
    marks[4] = mark5;
    stermMarks = marks;
    students.push_back(this);
};
double STermStudent::GetAverageMark() {
    int sum = 0;
    for (int mark : ftermMarks) {
        sum += mark;
    }
    for (int mark : stermMarks) {
        sum += mark;
    }
    return sum / 9.0;
}

void STermStudent::ChangeMarks(std::array<int, 5> marks) {
    stermMarks = marks;
}

std::array<int, 5> STermStudent::GetMarks() const {
    return stermMarks;
}

std::array<int, 4> STermStudent::GetFTermMarks() const {
    return ftermMarks;
}

std::ostream& operator<<(std::ostream& os, const STermStudent& student) {
    printf("%s is a %d course student from the group number %d\n",
        student.name, student.course, student.group);
    printf("His/her first term marks marks are: ");

    for (auto mark : student.GetFTermMarks()) {
        printf("%d ", mark);
    }
    printf("\n");

    printf("His/her second term marks marks are: ");
    for (auto mark : student.GetMarks()) {
        printf("%d ", mark);
    }
    return os;
}