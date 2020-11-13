#include "student.h"

#ifndef FIRST_TERM_STUDENT_H
#define FIRST_TERM_STUDENT_H
class FTermStudent : public Student {
private:
  FTermStudent();
protected:
  static std::vector<FTermStudent*> students;
  std::array<int, 4> ftermMarks;
public:
  static std::vector<FTermStudent*> GetStudents() { return students; }
  FTermStudent(char * _name, int _group, int _course, std::array<int, 4> ftermMarks);
  FTermStudent(char * _name, int _group, int _course, int, int, int, int);
  FTermStudent(const Student&, int, int, int, int);
  FTermStudent(const FTermStudent&);
  virtual double GetAverageMark();
  void ChangeMarks(std::array<int, 4>);
  std::array<int, 4> GetMarks() const;
  friend std::ostream& operator<<(std::ostream& os, const FTermStudent& student);
  friend class StudentUtil;
};
#endif
