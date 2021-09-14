
#ifndef Q283_UNITTEST_H__
#define Q283_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0283.hpp"

using namespace std;

TEST(q283, sample_input01) {
  vector<int> i{0, 1, 0, 3, 12};
  vector<int> e{1, 3, 12, 0, 0};
  l283::Solution solver;
  solver.moveZeroes(i);
  EXPECT_EQ(i, e);
}

TEST(q283, sample_input02) {
  vector<int> i{0};
  vector<int> e{0};
  l283::Solution solver;
  solver.moveZeroes(i);
  EXPECT_EQ(i, e);
}

#endif