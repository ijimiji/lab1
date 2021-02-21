#include "first_term_student.h"

std::vector<FTermStudent*> FTermStudent::students;

FTermStudent::FTermStudent(char * _name, int _group, int _course, std::array<int, 4> ftermMarks)
    : ftermMarks(ftermMarks), Student(_name, _group, _course) {
    students.push_back(this);
};

FTermStudent::FTermStudent(const Student& student, int mark1, int mark2, int mark3, int mark4)
    : Student(student) {
    std::array<int, 4>  marks = {mark1, mark2, mark3, mark4};
    ftermMarks = marks;
    students.push_back(this);
};
FTermStudent::FTermStudent(char * _name, int _group, int _course, int mark1, int mark2, int mark3, int mark4)
    : Student(_name, _group, _course) {
    std::array<int, 4>  marks = {mark1, mark2, mark3, mark4};
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
std::string FTermStudent::to_string() const{
    std::string out;
    out += name;
    out += " is a ";
    out += std::to_string(course); 
    out += " course student from the group number ";
    out += std::to_string(group);
    out += "\n";
    out += "His/her first term marks are: ";
    for (auto mark : GetMarks()) {
        out += std::to_string(mark);
        out += " ";
    }
    return out;
}


std::ostream& operator<<(std::ostream& os, const FTermStudent& student) {
    std::cout << student.to_string();
    return os;
}
FTermStudent::~FTermStudent(){
  int n = students.size();
  for (int i = 0; i<n; ++i){
    if (this == students[i]){
      students.erase(students.begin() + i);
    }
  }
}