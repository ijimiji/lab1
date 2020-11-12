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
    Student pupa("Pupa", 1, 1);
    Student lupa("Lupa", 1, 1);
    Student duba("Duba", 5, 1);

    FTermStudent pupaF(pupa, 7, 9, 4, 4);
    FTermStudent lupaF(lupa, 5, 10, 4, 7);
    FTermStudent dubaF(duba, 5, 4, 4, 5);

    STermStudent pupaS(pupaF, 7, 9, 4, 4, 10);
    STermStudent lupaS(lupaF, 5, 10, 4, 5, 9);
    STermStudent dubaS(dubaF, 5, 4, 4, 5, 6);

    std::cout << dubaS << std::endl;

    std::cout << StudentUtil::CalculateAverageMarkOfGroupAfterSession(1, 1) << std::endl;
    std::cout << StudentUtil::CalculateAverageMarkOfAll() << std::endl;
}
