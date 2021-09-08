
#ifndef Q118_UNITTEST_H__
#define Q118_UNITTEST_H__

#include <gtest/gtest.h>

#include "../src/q0118.hpp"

using namespace std;

TEST(q118, sapmle_input01) {
  int numRows = 5;
  vector<vector<int>> exp{{1}, { 1, 1 }, { 1, 2, 1 }, { 1, 3, 3, 1 }, { 1, 4, 6, 4, 1 }};
  l118::Solution solver;
  EXPECT_EQ(solver.generate(numRows), exp);
}

TEST(q118, sapmle_input02) {
  int numRows = 1;
  vector<vector<int>> exp{{1}};
  l118::Solution solver;
  EXPECT_EQ(solver.generate(numRows), exp);
}

#endif