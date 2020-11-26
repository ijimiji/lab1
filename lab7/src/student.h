#include "id.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>

#ifndef STUDENT_H
#define STUDENT_H

class Student {
protected:
  static std::vector<Student*> students;
private:
  const UniqueID id;
  const int record_book_id;
  const int personal_id;
  Student();
public:
  ~Student();
  char* name;
  int course;
  int group;
  Student(char*, int, int);
  Student(const Student&);
  int GetPersonalID();
  int GetRecordBookID();
  char* GetName();
  int GetCourse();
  int GetGroup();
  void SetName(char* _name);
  void SetCourse(int _course);
  void SetGroup(int _group);
  void PrintID();
  virtual double GetAverageMark(){ return 0;}
  friend std::ostream& operator<<(std::ostream& os, const Student& student);
  friend class StudentUtil;
  std::string to_string() const;
};

#endif
