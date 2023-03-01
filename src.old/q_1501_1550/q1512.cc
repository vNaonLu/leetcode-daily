#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1512.
 *       Number of Good Pairs
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array of integers ‘nums’ , return “the number of “good pairs”
 *   ”
 *   A pair ‘(i, j)’ is called “good” if ‘nums[i] = nums[j]’ and ‘i’ < ‘j’
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 100’
 *   • ‘1 ≤ nums[i] ≤ 100’
 *
 */

struct q1512 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int numIdenticalPairs(vector<int> &nums) {
      auto memo = unordered_map<int, int>();
      auto res  = (int)0;
      for (auto x : nums) {
        auto &cnt = memo[x];
        res += cnt++;
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1512, sample_input01) {
  solution         = new Solution();
  vector<int> nums = {1, 2, 3, 1, 1, 3};
  int         exp  = 4;
  int         act  = solution->numIdenticalPairs(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1512, sample_input02) {
  solution         = new Solution();
  vector<int> nums = {1, 1, 1, 1};
  int         exp  = 6;
  int         act  = solution->numIdenticalPairs(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1512, sample_input03) {
  solution         = new Solution();
  vector<int> nums = {1, 2, 3};
  int         exp  = 0;
  int         act  = solution->numIdenticalPairs(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}