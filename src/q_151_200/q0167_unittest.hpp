
#ifndef Q167_UNITTEST_H__
#define Q167_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0167.hpp"

using namespace std;

TEST(q167, sample_input01) {
  vector<int> i{2, 7, 11, 15};
  int t = 9;
  vector<int> e{1, 2};
  l167::Solution solver;
  EXPECT_EQ(solver.twoSum(i, t), e);
}

TEST(q167, sample_input02) {
  vector<int> i{2, 3, 4};
  int t = 6;
  vector<int> e{1, 3};
  l167::Solution solver;
  EXPECT_EQ(solver.twoSum(i, t), e);
}

TEST(q167, sample_input03) {
  vector<int> i{-1, 0};
  int t = -1;
  vector<int> e{1, 2};
  l167::Solution solver;
  EXPECT_EQ(solver.twoSum(i, t), e);
}

#endif