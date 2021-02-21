#include "student.h"

std::ostream& operator<<(std::ostream &out, Student student){
    out << student.f_name << " " << student.surname << " " << student.s_name << " ";
    out << student.year << " курс " << "#" << student.id;
    return out;
}

std::ostream& operator<<(std::ostream &out, std::shared_ptr<Student> student){
    out << *student;
    return out;
}

std::string Student::getFullName(){
    return f_name + " " + surname + " " + s_name;
}