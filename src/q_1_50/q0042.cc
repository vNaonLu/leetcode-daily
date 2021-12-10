#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 42.
 *     Trapping Rain Water
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given ‘n’ non-negative integers representing an elevation map where
 *   the width of each bar is ‘1’ , compute how much water it can trap
 *   after raining.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = height.length’
 *   • ‘1 ≤ n ≤ 2 × 10⁴’
 *   • ‘0 ≤ height[i] ≤ 10⁵’
 *
 */

struct q42 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int trap(vector<int>& height) {
      vector<int> dp(height.size(), 0);
      int res = 0;
      dp[0] = height[0];
      for (int i = 1; i < height.size(); ++i)
        dp[i] = max(dp[i - 1], height[i]);
      *(dp.end() - 1) = min(dp.back(), height.back());
      for (int i = height.size() - 2; i >= 0; --i)
        dp[i] = min(dp[i], max(dp[i + 1], height[i]));
      for (int i = 0; i < dp.size(); ++i)
        res += max(0, dp[i] - height[i]);
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q42, sample_input01) {
  solution = new Solution();
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int exp = 6;
  EXPECT_EQ(solution->trap(height), exp);
  delete solution;
}

TEST_F(q42, sample_input02) {
  solution = new Solution();
  vector<int> height = {4, 2, 0, 3, 2, 5};
  int exp = 9;
  EXPECT_EQ(solution->trap(height), exp);
  delete solution;
}