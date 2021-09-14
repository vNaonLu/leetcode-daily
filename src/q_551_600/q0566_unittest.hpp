
#ifndef Q566_UNITTEST_H__
#define Q566_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0566.hpp"

using namespace std;

TEST(q566, sample_input01) {
  vector<vector<int>> mat{{1, 2}, {3, 4}};
  int r = 1;
  int c = 4;
  vector<vector<int>> exp{{1, 2, 3, 4}};
  l566::Solution solver;
  EXPECT_EQ(solver.matrixReshape(mat, r, c), exp);
}

TEST(q566, sample_input02) {
  vector<vector<int>> mat{{1, 2}, {3, 4}};
  int r = 2;
  int c = 4;
  vector<vector<int>> exp{{1, 2}, {3, 4}};
  l566::Solution solver;
  EXPECT_EQ(solver.matrixReshape(mat, r, c), exp);
}

/**
[[1,2,3,4]]
[[1,2],[3,4]]
*/

#endif