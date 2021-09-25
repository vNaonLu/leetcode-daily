
#ifndef Q764_UNITTEST_H__
#define Q764_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0764.hpp"

using namespace std;

TEST(q764, sample_input01) {
  int n = 5;
  vector<vector<int>> mines{{4, 2}};
  int exp = 2;
  l764::Solution solver;
  EXPECT_EQ(solver.orderOfLargestPlusSign(n, mines), exp);
}

TEST(q764, sample_input02) {
  int n =1;
  vector<vector<int>> mines{{0, 0}};
  int exp = 0;
  l764::Solution solver;
  EXPECT_EQ(solver.orderOfLargestPlusSign(n, mines), exp);
}

#endif