#include <gtest/gtest.h>

#include "controller.h"

s21::Model t_model;
s21::Controller control(&t_model);

TEST(calc, all) {
  double res = 0;

  res = control.calc_expression("2^x", -10);
  ASSERT_DOUBLE_EQ(res, pow(2, -10));

  res = control.calc_expression("-453+564");
  ASSERT_DOUBLE_EQ(res, -453 + 564);

  res = control.calc_expression("42*(67^3)/5");
  ASSERT_DOUBLE_EQ(res, 42 * (pow(67, 3)) / 5);

  res = control.calc_expression("-5*(-6+10.8/4)");
  ASSERT_DOUBLE_EQ(res, -5 * (-6 + 10.8 / 4));

  res = control.calc_expression("-2342-((-245+345)mod65)");
  ASSERT_DOUBLE_EQ(res, -2342 - ((-245 + 345) % 65));

  res = control.calc_expression("2*x^3", 3);
  ASSERT_DOUBLE_EQ(res, (2 * pow(3, 3)));

  res = control.calc_expression("cos(3)+sin(3)");
  ASSERT_DOUBLE_EQ(res, cos(3) + sin(3));

  res = control.calc_expression("log(3+ln(6)*acos(1)^asin(0))");
  ASSERT_DOUBLE_EQ(res, log10(3 + log(6) * pow(acos(1), asin(0))));

  res = control.calc_expression("sqrt(tan(3+atan(9)))");
  ASSERT_DOUBLE_EQ(res, sqrt(tan(3 + atan(9))));

  res = control.calc_expression("4235/0");
  ASSERT_DOUBLE_EQ(res, 4235 / 0.0);

  res = control.calc_expression("-56.564/0");
  ASSERT_DOUBLE_EQ(res, -56.564 / 0.0);

  res = control.calc_expression("sqrt(x)-1/2*tan(x^2-2)", 54);
  ASSERT_DOUBLE_EQ(res, 10.212896954152978);
}

TEST(credit, all) {
  std::string s;

  s = control.cred_params(10000, 12, 5, 2);
  EXPECT_EQ(s, "856.074818 272.897815 10272.897815");

  s = control.cred_params(250000, 12, 10, 1);
  EXPECT_EQ(s, "22916.666667...21006.944444 13541.666667 263541.666667");
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
