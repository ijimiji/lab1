#pragma once
#include <string>
#include <iostream>
#include <memory>
class Student{
public:
    std::string f_name;
    std::string surname;
    std::string s_name;
    int year;
    long long int id;
    friend std::ostream& operator<<(std::ostream &out, Student student);
    friend std::ostream& operator<<(std::ostream &out, std::shared_ptr<Student> student);
    std::string getFullName();
};