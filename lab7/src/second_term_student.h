#include "student.h"
#include "first_term_student.h"

#ifndef SECOND_TERM_STUDENT_H
#define SECOND_TERM_STUDENT_H

class STermStudent : public FTermStudent {
private:
  std::array <int, 5> stermMarks;
  STermStudent();
protected:
  static std::vector<STermStudent*> students;
public:
  static std::vector<STermStudent*> GetStudents() { return students; }
  STermStudent(const FTermStudent&, std::array <int, 5>);
  STermStudent(char * _name, int _group, int _course, std::array<int, 4> ftermMarks, std::array<int, 5> stermMarks);
  STermStudent(const FTermStudent&, int, int, int, int, int);
  virtual double GetAverageMark();
  void ChangeMarks(std::array<int, 5>);
  std::array<int, 5> GetMarks() const;
  std::array<int, 4> GetFTermMarks() const;
  friend std::ostream& operator<<(std::ostream& os, const STermStudent& student);
  friend class StudentUtil;
};

#endif
