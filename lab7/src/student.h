#include "id.h"
#ifndef STUDENT_H
#define STUDENT_H

class Student : UniqueID{
  // protected:
  //   static int nextID;
private:
  char * name;
  int group;
  int year;
  UniqueID id;
 public:
  Student(char *, int, int);
  const int personal_id;
  const int record_book_id;
};

#endif
