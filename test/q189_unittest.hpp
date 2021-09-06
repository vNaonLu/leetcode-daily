
#ifndef Q189_UNITTEST_H__
#define Q189_UNITTEST_H__

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../src/q189.hpp"

using namespace std;

TEST(q189, sample_input01) {
  vector<int> i{1, 2, 3, 4, 5, 6, 7};
  int k = 3;
  vector<int> exp{5, 6, 7, 1, 2, 3, 4};
  l189::Solution solver;
  solver.rotate(i, k);
  EXPECT_EQ(i, exp);
}

TEST(q189, sample_input02) {
  vector<int> i{-1, -100, 3, 99};
  int k = 2;
  vector<int> exp{3, 99, -1, -100};
  l189::Solution solver;
  solver.rotate(i, k);
  EXPECT_EQ(i, exp);
}

#endif