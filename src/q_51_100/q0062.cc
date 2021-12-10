#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 62.
 *     Unique Paths
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   A robot is located at the top-left corner of a ‘m x n’ grid (marked
 *   'Start' in the diagram
 *   The robot can only move either down or right at any point in time. The
 *   robot is trying to reach the bottom-right corner of the grid (marked
 *   'Finish' in the diagram
 *   How many possible unique paths are there?
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ m, n ≤ 100’
 *   • It's guaranteed that the answer will be less than or equal to ‘2 × 10⁹’ .
 *
 */

struct q62 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int uniquePaths(int m, int n) {
      vector<vector<int>> dp(m, vector<int>(n, 0));
      for (int i = 0; i < m; ++i)
        dp[i][0] = 1;
      for (int i = 0; i < n; ++i)
        dp[0][i] = 1;
      for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      return dp.back().back();
    }
  };

  class Solution *solution;
};

TEST_F(q62, sample_input01) {
  solution = new Solution();
  int m = 3;
  int n = 7;
  int exp = 28;
  EXPECT_EQ(solution->uniquePaths(m, n), exp);
  delete solution;
}

TEST_F(q62, sample_input02) {
  solution = new Solution();
  int m = 3;
  int n = 2;
  int exp = 3;
  EXPECT_EQ(solution->uniquePaths(m, n), exp);
  delete solution;
}

TEST_F(q62, sample_input03) {
  solution = new Solution();
  int m = 7;
  int n = 3;
  int exp = 28;
  EXPECT_EQ(solution->uniquePaths(m, n), exp);
  delete solution;
}

TEST_F(q62, sample_input04) {
  solution = new Solution();
  int m = 3;
  int n = 3;
  int exp = 6;
  EXPECT_EQ(solution->uniquePaths(m, n), exp);
  delete solution;
}