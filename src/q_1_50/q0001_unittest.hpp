
#ifndef Q1_UNITTEST_H__
#define Q1_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0001.hpp"

using namespace std;

TEST(q1, sample_input01) {
  vector<int> i{2, 7, 11, 15};
  int target = 9;
  vector<int> exp{0, 1};
  l1::Solution solver;
  EXPECT_EQ(solver.twoSum(i, target), exp);
}

TEST(q1, sample_input02) {
  vector<int> i{3, 2, 4};
  int target = 6;
  vector<int> exp{1, 2};
  l1::Solution solver;
  EXPECT_EQ(solver.twoSum(i, target), exp);
}

TEST(q1, sample_input03) {
  vector<int> i{3, 3};
  int target = 6;
  vector<int> exp{0, 1};
  l1::Solution solver;
  EXPECT_EQ(solver.twoSum(i, target), exp);
}

#endif