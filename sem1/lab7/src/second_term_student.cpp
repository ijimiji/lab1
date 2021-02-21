#include "second_term_student.h"

STermStudent::STermStudent(const FTermStudent& student, std::array <int, 5> marks)
    :FTermStudent(student), stermMarks(marks) {
    students.push_back(this);
}

std::vector<STermStudent*> STermStudent::students;

STermStudent::STermStudent(char * _name, int _group, int _course, std::array<int, 4> ftermMarks, std::array<int, 5> stermMarks)
    : stermMarks(stermMarks), FTermStudent(_name, _group, _course, ftermMarks) {
    students.push_back(this);
};

STermStudent::STermStudent(const FTermStudent& student, int mark1, int mark2, int mark3, int mark4, int mark5)
    : FTermStudent(student) {
    std::array<int, 5>  stermMarks = {mark1, mark2, mark3, mark4, mark5 };
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
 std::string STermStudent::to_string() const{
    std::string out;
    out += name;
    out += " is a ";
    out += std::to_string(course); 
    out += " course student from the group number ";
    out += std::to_string(group);
    out += "\n";
    out += "His/her first term marks are: ";
    for (auto mark : GetFTermMarks()) {
        out += std::to_string(mark);
        out += " ";
    }
    out += "\n";
    out += "His/her second term marks are: ";
    for (auto mark : GetMarks()) {
        out += std::to_string(mark);
        out += " ";
    }
    return out;
}


std::ostream& operator<<(std::ostream& os, const STermStudent& student) {
    std::cout << student.to_string();
    return os;
}

STermStudent::~STermStudent(){
  int n = students.size();
  for (int i = 0; i<n; ++i){
    if (this == students[i]){
      students.erase(students.begin() + i);
    }
  }
}