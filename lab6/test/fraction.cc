#include "gtest/gtest.h"
#include "fraction.h"

TEST(Constructor, Straight) {
    Fraction a(1, 2);
    ASSERT_EQ(a.GetNumerator(), 1);
    ASSERT_EQ(a.GetDenominator(), 2);
}

TEST(Constructor, Straight_Negative) {
    Fraction a(-1, -2);
    ASSERT_EQ(a.GetNumerator(), -1);
    ASSERT_EQ(a.GetDenominator(), -2);
}

TEST(Constructor, Straight_Zero_Den) {
    EXPECT_THROW( {Fraction a(1, 0);}, FractionConstructionFailed);
}

TEST(Constructor, Straight_Zero_Num) {
    Fraction a(0, -2);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), -2);
}

TEST(Constructor, Simplify_Zero_Den) {
    EXPECT_THROW( {Fraction a(1, 0, true);}, FractionConstructionFailed);
}

TEST(Constructor, No_Simplify_Zero_Den) {
    EXPECT_THROW( {Fraction a(1, 0, false);}, FractionConstructionFailed);
}

TEST(Constructor, Simplify_Straight) {
    Fraction a(33, 11, true);
    ASSERT_EQ(a.GetNumerator(), 3);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Constructor, No_Simplify_Straight) {
    Fraction a(33, 11, false);
    ASSERT_EQ(a.GetNumerator(), 33);
    ASSERT_EQ(a.GetDenominator(), 11);
}

TEST(Constructor, Simplify_Negative_Num) {
    Fraction a(-33, 11, true);
    ASSERT_EQ(a.GetNumerator(), -3);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Constructor, Simplify_Negative) {
    Fraction a(-33, -11, true);
    ASSERT_EQ(a.GetNumerator(), 3);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Constructor, Simplify_Zero_Num) {
    Fraction a(0, 11, true);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Constructor, Simplify_Negative_Den) {
    Fraction a(12, -3, true);
    ASSERT_EQ(a.GetNumerator(), 4);
    ASSERT_EQ(a.GetDenominator(), -1);
}

TEST(Util, Setter_Num_Straight){
    Fraction a(50, 25, true);
    a.SetNumerator(3);
    ASSERT_EQ(a.GetNumerator(), 3);
}

TEST(Util, Setter_Num_Zero){
    Fraction a(50, 25, true);
    a.SetNumerator(0);
    ASSERT_EQ(a.GetNumerator(), 0);
}

TEST(Util, Setter_Num_Negative){
    Fraction a(50, 25, true);
    a.SetNumerator(-3);
    ASSERT_EQ(a.GetNumerator(), -3);
}

TEST(Util, Setter_Den_Straight){
    Fraction a(50, 25, true);
    a.SetDenominator(10);
    ASSERT_EQ(a.GetDenominator(), 10);
}

TEST(Util, Setter_Num_Same){
    Fraction a(50, 25, true);
    a.SetNumerator(1); // Asign the same value
    ASSERT_EQ(a.GetNumerator(), 1);
}

TEST(Util, Setter_Den_Zero){
    Fraction a(50, 25, true);
    EXPECT_THROW( {a.SetDenominator(0);}, FractionConstructionFailed);
}

TEST(Addition, Straight){
    Fraction a(2, 3);
    Fraction b(1, 3);
    a.Add(b);
    ASSERT_EQ(a.GetNumerator(), 3);
    ASSERT_EQ(a.GetDenominator(), 3);
}

TEST(Addition, Straight_Simplify){
    Fraction a(2, 3);
    Fraction b(1, 3);
    a.Add(b, true);
    ASSERT_EQ(a.GetNumerator(), 1);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Addition, Straight_Neg_Num){
    Fraction a(-2, 3);
    Fraction b(1, 3);
    a.Add(b);
    ASSERT_EQ(a.GetNumerator(), -1);
    ASSERT_EQ(a.GetDenominator(), 3);
}

TEST(Addition, Straight_Neg_Nested){
    Fraction a(-2, -3);
    Fraction b(1, -3);
    a.Add(b);
    ASSERT_EQ(a.GetNumerator(), 1);
    ASSERT_EQ(a.GetDenominator(), 3);
}

TEST(Addition, Simplify_Neg_Nested_Zero){
    Fraction a(1, -3);
    Fraction b(1, 3);
    a.Add(b, true);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 1); // Default behavior of GCD
}

TEST(Multiply, Straight_Positive){
    Fraction a(2, 3);
    Fraction b(6, 5);
    a.Multiply(b);
    ASSERT_EQ(a.GetNumerator(), 12);
    ASSERT_EQ(a.GetDenominator(), 15);
}

TEST(Multiply, Straight_Positive_Zero){
    Fraction a(0, 3);
    Fraction b(6, 5);
    a.Multiply(b);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 15);
}

TEST(Multiply, Straight_Negative){
    Fraction a(-1, 3);
    Fraction b(6, -5);
    a.Multiply(b);
    ASSERT_EQ(a.GetNumerator(), -6);
    ASSERT_EQ(a.GetDenominator(), -15);
}

TEST(Multiply, Simplify_Positive){
    Fraction a(2, 3);
    Fraction b(6, 5);
    a.Multiply(b,true);
    ASSERT_EQ(a.GetNumerator(), 4);
    ASSERT_EQ(a.GetDenominator(), 5);
}
TEST(Multiply, Simplify_Positive_Zero){
    Fraction a(2, 3);
    Fraction b(0, 5);
    a.Multiply(b,true);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Multiply, Simplify_Negative){
    Fraction a(-2, 3);
    Fraction b(10, -5);
    a.Multiply(b,true);
    ASSERT_EQ(a.GetNumerator(), 4);
    ASSERT_EQ(a.GetDenominator(), 3);
}

TEST(Divide, Straight_Positive){
    Fraction a(4, 3);
    Fraction b(2, 3);
    a.Divide(b);
    ASSERT_EQ(a.GetNumerator(), 12);
    ASSERT_EQ(a.GetDenominator(), 6);
}

TEST(Divide, Straight_Positive_Zero){
    Fraction a(0, 3);
    Fraction b(6, 5);
    a.Divide(b);
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 18);
}

TEST(Divide, Straight_Positive_Zero_Den){
    Fraction a(7, 3);
    Fraction b(0, 5);
    EXPECT_THROW( {a.Divide(b);}, FractionConstructionFailed);
}

TEST(Divide, Straight_Negative){
    Fraction a(-1, 3);
    Fraction b(6, -5);
    a.Divide(b);
    ASSERT_EQ(a.GetNumerator(), 5);
    ASSERT_EQ(a.GetDenominator(), 18);
}

TEST(Divide, Simplify_Positive){
    Fraction a(15, 2);
    Fraction b(3, 2);
    a.Divide(b,true);
    ASSERT_EQ(a.GetNumerator(), 5);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(Divide, Simplify_Negative){
    Fraction a(-2, 3);
    Fraction b(-10, 5);
    a.Divide(b,true);
    ASSERT_EQ(a.GetNumerator(), 1);
    ASSERT_EQ(a.GetDenominator(), 3);
}

TEST(To_string, Straight){
    Fraction a(2, 3);
    ASSERT_EQ(a.to_string(), "2/3");
}

TEST(To_string, Negative){
    Fraction a(-2, 3);
    ASSERT_EQ(a.to_string(), "-2/3");
}

TEST(To_string, Both_Negative){
    Fraction a(-2, -3);
    ASSERT_EQ(a.to_string(), "-2/-3");
}


TEST(To_string, Negative_Plus_Integer){
    Fraction a(-10, 3);
    ASSERT_EQ(a.to_string(), "-(3 + 1/3)");
}
TEST(To_string, Positive_Plus_Integer){
    Fraction a(10, 3);
    ASSERT_EQ(a.to_string(), "3 + 1/3");
}

TEST(To_string, Zero){
    Fraction a(0, 3);
    ASSERT_EQ(a.to_string(), "0");
}

TEST(To_string, Integer){
    Fraction a(2, 1);
    ASSERT_EQ(a.to_string(), "2");
}

TEST(To_string, Negative_Integer){
    Fraction a(-2, 1);
    ASSERT_EQ(a.to_string(), "-2");
}

TEST(GCD, Positive){
    int res = Fraction::GCD(4, 2);
    ASSERT_EQ(res, 2);
}

TEST(GCD, Negative){
    int res = Fraction::GCD(-4, 2);
    ASSERT_EQ(res, 2);
}

TEST(GCD, Both_Negative){
    int res = Fraction::GCD(-4, -2);
    ASSERT_EQ(res, 2);
}

TEST(GCD, Zero){
    int res = Fraction::GCD(4, 0);
    ASSERT_EQ(res, 4);
}

TEST(GCD, Both_Zeros){
    EXPECT_THROW( {Fraction::GCD(0, 0);}, ZerosInGCD);
}

TEST(ConvertToSimple, Straight){
    Fraction a(4, 2);
    a.ConvertToSimple();
    ASSERT_EQ(a.GetNumerator(), 2);
    ASSERT_EQ(a.GetDenominator(), 1);
}

TEST(ConvertToSimple, Negative){
    Fraction a(-4, 2);
    a.ConvertToSimple();
    ASSERT_EQ(a.GetNumerator(), -2);
    ASSERT_EQ(a.GetDenominator(), 1);
}
TEST(ConvertToSimple, Both_Negative){
    Fraction a(-4, -2);
    a.ConvertToSimple();
    ASSERT_EQ(a.GetNumerator(), 2);
    ASSERT_EQ(a.GetDenominator(), 1);
}
TEST(ConvertToSimple, Zero){
    Fraction a(0, -2);
    a.ConvertToSimple();
    ASSERT_EQ(a.GetNumerator(), 0);
    ASSERT_EQ(a.GetDenominator(), 1);
}
TEST(ConvertToSimple, Simple){
    Fraction a(7, 13);
    a.ConvertToSimple();
    ASSERT_EQ(a.GetNumerator(), 7);
    ASSERT_EQ(a.GetDenominator(), 13);
}

TEST(Print, Straight){
    Fraction a(7, 13);
    int den = a.GetDenominator();
    int num = a.GetNumerator();
    a.Print();
    ASSERT_EQ(a.GetNumerator(), num);
    ASSERT_EQ(a.GetDenominator(), den);
}
