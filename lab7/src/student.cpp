#include "student.h"
#include "id.h"

Student::Student(char *nameIO, int groupIO, int yearIO)
  : UniqueID(),
  personal_id(id.id), record_book_id(id.id) {
  name = nameIO;
  group = groupIO;
  year = yearIO;
}

