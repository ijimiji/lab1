#include "student.h"
#include <iostream>

std::vector<Student*> Student::students;

Student::Student(char* nameIO, int groupIO, int courseIO) : id(), personal_id(id.value), record_book_id(id.value)
{
  name = nameIO;
  group = groupIO;
  course = courseIO;
  students.push_back(this);
}

Student::Student(const Student& student)
  : id(student.id),
  record_book_id(id.value),
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

std::ostream& operator<<(std::ostream& os, const Student& student) {
  printf("%s is a %d course student from the group number %d",
    student.name, student.course, student.group);
  return os;
}
