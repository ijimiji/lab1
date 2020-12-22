#include "student.h"
#include <iostream>

std::vector<Student*> Student::students;

Student::Student(char* _name, int _group, int _course) : id(), personal_id(id.value), record_book_id(id.value)
{
  name = _name;
  group = _group;
  course = _course;
  students.push_back(this);
}

Student::Student(const Student& student)
  : id(),
  record_book_id(student.record_book_id),
  personal_id(id.value),
  name(student.name),
  group(student.group),
  course(student.course)
{
  students.push_back(this);
}

void Student::PrintID() {
  std::cout << id.value << std::endl;
}

int Student::GetPersonalID() {
  return personal_id;
}

int Student::GetRecordBookID() {
  return record_book_id;
}

char* Student::GetName() { return name; }
int Student::GetCourse() { return course; }
int Student::GetGroup() { return group; }
void Student::SetName(char* _name) { name = _name; }
void Student::SetCourse(int _course) { course = _course; }
void Student::SetGroup(int _group) { group = _group; }

std::string Student::to_string() const{
    std::string out;
    out += name;
    out += " is a ";
    out += std::to_string(course); 
    out += " course student from the group number ";
    out += std::to_string(group);
    return out;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
  std::cout << student.to_string();
  return os;
}

Student::~Student(){
  int n = students.size();
  for (int i = 0; i<n; ++i){
    if (this == students[i]){
      students.erase(students.begin() + i);
    }
  }
}
