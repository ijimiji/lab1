#include "gtest/gtest.h"
#include "student_util.h"

TEST(StudentConstructor, Simple){
    Student me("Jahor", 4, 1);
    EXPECT_EQ(me.GetName(), "Jahor");
    EXPECT_EQ(me.GetCourse(), 1);
    EXPECT_EQ(me.GetGroup(), 4);
}

TEST(StudentConstructor, Copy){
    Student lupa("Lupa", 4, 1);
    Student new_lupa(lupa);
    EXPECT_EQ(lupa.GetRecordBookID(), new_lupa.GetRecordBookID());
    EXPECT_EQ(lupa.GetCourse(), new_lupa.GetCourse());
    EXPECT_EQ(lupa.GetGroup(), new_lupa.GetGroup());
    EXPECT_EQ(lupa.GetName(), new_lupa.GetName());
    EXPECT_NE(lupa.GetPersonalID(), new_lupa.GetPersonalID());
}

TEST(FTermStudentConstructor, Simple){
    FTermStudent pupa("Pupa", 4, 1, {4, 5, 10, 9});
    EXPECT_EQ(pupa.GetName(), "Pupa");
    EXPECT_EQ(pupa.GetCourse(), 1);
    EXPECT_EQ(pupa.GetGroup(), 4);
    std::array<int, 4> marks = {4, 5, 10, 9};
    EXPECT_EQ(pupa.GetMarks(), marks);
}

TEST(FTermStudentConstructor, Copy){
    FTermStudent lupa("Lupa", 4, 1, {5, 6, 3, 2});
    FTermStudent new_lupa(lupa);
    EXPECT_EQ(lupa.GetRecordBookID(), new_lupa.GetRecordBookID());
    EXPECT_EQ(lupa.GetCourse(), new_lupa.GetCourse());
    EXPECT_EQ(lupa.GetGroup(), new_lupa.GetGroup());
    EXPECT_EQ(lupa.GetName(), new_lupa.GetName());
    EXPECT_NE(lupa.GetPersonalID(), new_lupa.GetPersonalID());
    EXPECT_EQ(lupa.GetMarks(), new_lupa.GetMarks());
}


TEST(Util, GetStudentsEmpty){
    // Make sure that no garbage remains in the vector
    std::vector<Student *> empty;
    EXPECT_EQ(StudentUtil::GetStudents(), empty);
}

TEST(Util, GetStudents){
    // Make sure that each student will appear in array once
    std::vector<Student *> students;
    Student lupa("Lupa", 4, 1);
    FTermStudent pupa("Pupa", 4, 1, {4, 5, 10, 9});
    STermStudent boka("Boka", 4, 1, {10, 4, 9, 7}, {10, 10, 9, 8, 10});
    students.push_back(&lupa);
    students.push_back(&pupa);
    students.push_back(&boka);
    EXPECT_EQ(StudentUtil::GetStudents(), students);
}

TEST(STermStudentConstructor, Simple){
    STermStudent pupa("Pupa", 4, 1, {4, 5, 10, 9}, {4, 5, 4, 9, 10});
    EXPECT_EQ(pupa.GetName(), "Pupa");
    EXPECT_EQ(pupa.GetCourse(), 1);
    EXPECT_EQ(pupa.GetGroup(), 4);
    std::array<int, 4> marks = {4, 5, 10, 9};
    std::array<int, 5> smarks = {4, 5, 4, 9, 10};
    EXPECT_EQ(pupa.GetFTermMarks(), marks);
    EXPECT_EQ(pupa.GetMarks(), smarks);
}

TEST(STermStudentConstructor, Copy){
    STermStudent lupa("Lupa", 4, 1, {5, 6, 3, 2}, {10, 8, 9, 10, 8});
    STermStudent new_lupa(lupa);
    EXPECT_EQ(lupa.GetRecordBookID(), new_lupa.GetRecordBookID());
    EXPECT_EQ(lupa.GetCourse(), new_lupa.GetCourse());
    EXPECT_EQ(lupa.GetGroup(), new_lupa.GetGroup());
    EXPECT_EQ(lupa.GetName(), new_lupa.GetName());
    EXPECT_NE(lupa.GetPersonalID(), new_lupa.GetPersonalID());
    EXPECT_EQ(lupa.GetMarks(), new_lupa.GetMarks());
    EXPECT_EQ(lupa.GetFTermMarks(), new_lupa.GetFTermMarks());
}

TEST(AverageMark, Student){
    Student zhoka("Zhoka", 3, 1);
    EXPECT_DOUBLE_EQ(zhoka.GetAverageMark(), 0);
}

TEST(AverageMark, FTermStudent){
    FTermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10});
    double mark = 33.0 / 4;
    EXPECT_DOUBLE_EQ(zhoka.GetAverageMark(), mark);
}

TEST(AverageMark, STermStudent){
    STermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10}, {4, 10, 4, 9, 7});
    double mark = 67.0 / 9;
    EXPECT_DOUBLE_EQ(zhoka.GetAverageMark(), mark);
}

TEST(AverageMark, All_Students){
    STermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10}, {4, 10, 4, 9, 7});
    STermStudent poka("Poka", 3, 1, {10, 5, 4, 10}, {4, 10, 4, 9, 7});
    FTermStudent koka("Koka", 3, 1, {9, 9, 5, 10});
    double mark = (67.0 / 9 + 63.0 / 9 + 33.0 / 4)/3;
    EXPECT_DOUBLE_EQ(StudentUtil::CalculateAverageMarkOfAll(), mark);
}

TEST(AverageMark, Students_After_Second_Session){
    STermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10}, {4, 10, 4, 9, 7});
    STermStudent poka("Poka", 3, 1, {10, 5, 4, 10}, {4, 10, 4, 9, 7});
    STermStudent buka("Buka", 2, 1, {4, 4, 4, 10}, {4, 4, 4, 9, 7});
    FTermStudent koka("Koka", 3, 1, {9, 9, 5, 10});
    Student woka("Woka", 3, 1);
    double mark = (67.0 / 9 + 63.0 / 9)/2;
    EXPECT_DOUBLE_EQ(StudentUtil::CalculateAverageMarkOfGroupAfterSession(3, 2), mark);
}

TEST(AverageMark, Students_After_Second_Session_Empty_Group){
    STermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10}, {4, 10, 4, 9, 7});
    STermStudent poka("Poka", 3, 1, {10, 5, 4, 10}, {4, 10, 4, 9, 7});
    STermStudent buka("Buka", 2, 1, {4, 4, 4, 10}, {4, 4, 4, 9, 7});
    FTermStudent koka("Koka", 3, 1, {9, 9, 5, 10});
    Student woka("Woka", 3, 1);
    EXPECT_DOUBLE_EQ(StudentUtil::CalculateAverageMarkOfGroupAfterSession(5, 2), 0);
}

TEST(AverageMark, Students_After_First_Session){
    FTermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10});
    FTermStudent poka("Poka", 3, 1, {10, 5, 4, 10});

    FTermStudent buka("Buka", 2, 1, {4, 4, 4, 10});
    FTermStudent koka("Koka", 3, 1, {9, 9, 5, 10});
    Student woka("Woka", 3, 1);
    double mark = (33.0 / 4 + 29.0 / 4 + 33.0 /4)/3;
    EXPECT_DOUBLE_EQ(StudentUtil::CalculateAverageMarkOfGroupAfterSession(3, 1), mark);
}
TEST(AverageMark, Students_After_First_Session_Empty_Group){
    FTermStudent zhoka("Zhoka", 3, 1, {9, 9, 5, 10});
    FTermStudent poka("Poka", 3, 1, {10, 5, 4, 10});
    FTermStudent buka("Buka", 2, 1, {4, 4, 4, 10});
    FTermStudent koka("Koka", 3, 1, {9, 9, 5, 10});
    Student woka("Woka", 3, 1);
    EXPECT_DOUBLE_EQ(StudentUtil::CalculateAverageMarkOfGroupAfterSession(12, 1), 0);
}

TEST(Print, Student){
    Student utka("Utka", 3, 1);
    std::string out = "Utka is a 1 course student from the group number 3";
    EXPECT_EQ(utka.to_string(), out);
}


TEST(Print, FTermStudent){
    FTermStudent dubas("Dubas", 3, 1, {5, 6, 7, 7});
    std::string out = "Dubas is a 1 course student from the group number 3\nHis/her first term marks are: 5 6 7 7 ";
    EXPECT_EQ(dubas.to_string(), out);
}

TEST(Print, STermStudent){
    STermStudent putin("Putin", 3, 1, {5, 6, 7, 7}, {10, 5, 10, 4, 9});
    std::string out = "Putin is a 1 course student from the group number 3\nHis/her first term marks are: 5 6 7 7 \nHis/her second term marks are: 10 5 10 4 9 ";
    EXPECT_EQ(putin.to_string(), out);
}
