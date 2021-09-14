
#ifndef Q977_UNITTEST_H__
#define Q977_UNITTEST_H__

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "q0977.hpp"

using namespace std;

TEST(q977, sample_input01) {
  vector<int> i{-4, -1, 0, 3, 10};
  vector<int> exp{0, 1, 9, 16, 100};
  l977::Solution solver;
  EXPECT_EQ(solver.sortedSquares(i), exp);
}

TEST(q977, sample_input02) {
  vector<int> i{-7, -3, 2, 3, 11};
  vector<int> exp{4, 9, 9, 49, 121};
  l977::Solution solver;
  EXPECT_EQ(solver.sortedSquares(i), exp);
}

#endif