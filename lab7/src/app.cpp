#include "app.h"
#include "student.h"
#include "first_term_student.h"
#include "second_term_student.h"
#include "student_util.h"
#include <iostream>

/*
    Personal id -> value of id from class UniqueID
    Record book id -> value of id from class UniqueID
    Name -> name 🎯
    Course -> year 🎯
    Group -> group 🎯
    4 marks -> ftermMarks
    5 marks -> stermMarks
    Private default constructors
    Parameter constructor -> const Student/FTermStudent + array of marks/4(5) ints
    Protected copy constructor -> For internals only in order to not create instances of UniqueID (KEEP IT UNIQUE)
    Setters/Getters:
        int GetPersonalID();
        int GetRecordBookID();

        char * GetName();
        int GetCourse();
        int GetGroup();

        void SetName(char * _name);
        void SetCourse(int _course);
        void SetGroup(int _group);

    Marks setters/getters
        void ChangeMarks(std::array<int, 5(4)>);
        std::array<int, 5(4)> GetMarks() const;

    Average mark
        double GetAverageMark();

    << overloading -> 🎯

    Average mark of students in the array (array created automaticaly)
        double StudentUtil::CalculateAverageMarkOfAll();
        0.0 if no students griven

    Average mark of a group
        StudentUtil::CalculateAverageMarkOfGroupAfterSession(int group, int session);
        0.0 if no students griven
    Multifile?
    Sure!
*/

void App::Main() {
    STermStudent dubas("Dubas", 5, 1, {5, 6, 7, 7}, {4, 4, 4, 5, 6});
    FTermStudent lupa("Lupa", 3, 1, {10, 5, 8, 9});
    Student pupa("Pupa", 4, 1);

    // FTermStudent zhmyx("Zhmyx", 4, 1, {10, 9, 9, 8});
    STermStudent buba("Buba", 4, 1, {7, 9, 6, 4}, {9, 9, 8, 8, 8});
    STermStudent oleg("Oleg", 4, 1, {10, 9, 6, 5}, {10, 7, 8, 8, 10});
    STermStudent kuka("Kuka", 4, 1, {6, 9, 6, 4}, {9, 7, 8, 8, 9});

    // We have 3 Gimbitskys in the first group. 
    // Nice way to show copy constructor
    FTermStudent gymbytsky1("Gymbytsky", 1, 1, {10, 10, 9, 10});
    std::cout << gymbytsky1.GetPersonalID() << ' ' << gymbytsky1.GetRecordBookID() << std::endl;
    FTermStudent gymbytsky2(gymbytsky1);
    std::cout << gymbytsky2.GetPersonalID() << ' ' << gymbytsky1.GetRecordBookID() << std::endl;
    FTermStudent gymbytsky3(gymbytsky1);
    std::cout << gymbytsky3.GetPersonalID() << ' ' << gymbytsky1.GetRecordBookID() << std::endl;

    std::cout << "Average mark of the first group is: ";
    std::cout << StudentUtil::CalculateAverageMarkOfGroupAfterSession(1, 1) << std::endl;
    std::cout << "Average mark of the fourth group is: ";
    std::cout << StudentUtil::CalculateAverageMarkOfGroupAfterSession(4, 2) << std::endl;

    std::cout << pupa << std::endl;
    std::cout << dubas << std::endl;

    std::cout << "Average mark of all students is: ";
    std::cout << StudentUtil::CalculateAverageMarkOfAll() << std::endl;
}
