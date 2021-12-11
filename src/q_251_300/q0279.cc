#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 279.
 *      Perfect Squares
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer ‘n’ , return “the least number of perfect square
 *   numbers that sum to” ‘n’
 *   A “perfect square” is an integer that is the square of an integer; in
 *   other words, it is the product of some integer with itself. For
 *   example, ‘1’ , ‘4’ , ‘9’ , and ‘16’ are perfect squares while ‘3’ and
 *   ‘11’ are not.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 10⁴’
 *
 */

struct q279 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int numSquares(int n) {
      vector<int> dp(n + 1, numeric_limits<int>::max());
      dp[0] = 0;
      dp[1] = 1;
      for (int i = 2; i <= n; ++i) {
        for (int j = 1; j * j <= i; ++j) {
          dp[i] = min(dp[i], 1 + dp[i - j * j]);
        }
      }
      return dp.back();
    }
  };

  class Solution *solution;
};

TEST_F(q279, sample_input01) {
  solution = new Solution();
  int n = 12;
  int exp = 3;
  EXPECT_EQ(solution->numSquares(n), exp);
  delete solution;
}

TEST_F(q279, sample_input02) {
  solution = new Solution();
  int n = 13;
  int exp = 2;
  EXPECT_EQ(solution->numSquares(n), exp);
  delete solution;
}