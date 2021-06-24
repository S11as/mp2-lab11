#include "Arithmetic.h"

#include <gtest.h>
#include "cmath"

TEST(TestSuite, can_calculate_plus) {
    char *ss = "2+2";
    double ans = 4;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_minus) {
    char *ss = "12-5";
    double ans = 7;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_multiplication) {
    char *ss = "12*5";
    double ans = 60;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_division) {
    char *ss = "20/5";
    double ans = 4;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, division_by_zero_fails) {
    char *ss = "20/0";
    EXPECT_ANY_THROW(TPolish::calculate(ss););
}

TEST(TestSuite, can_calculate_pow) {
    char *ss = "3^3";
    double ans = 27;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_long_expression) {
    char *ss = "3^3*(444+555)";
    double ans = 26973;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_doubles) {
    char *ss = "1.324*5-3.2";
    double ans = 3.42;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(ans, res);
}

TEST(TestSuite, can_calculate_sin) {
    char *ss = "sin(3.1415)";
    double ans = 0;
    double eps = 0.0001;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(abs(ans - res) < eps, true);
}

TEST(TestSuite, can_calculate_cos) {
    char *ss = "cos(0.7856)";
    double ans = 0.7069;
    double eps = 0.0001;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(abs(ans - res) < eps, true);
}

TEST(TestSuite, can_calculate_sqrt) {
    char *ss = "sqrt(4)";
    double ans = 2;
    double eps = 0.0001;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(abs(ans - res) < eps, true);
}

TEST(TestSuite, can_calculate_complicated_expression) {
    char *ss = "(5+33)*5.33-7*cos(0.12)-sqrt(sin(0.25))";
    double ans = 195.0929;
    double eps = 0.0001;
    double res = TPolish::calculate(ss);
    EXPECT_EQ(abs(ans - res) < eps, true);
}


