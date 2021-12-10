#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 189.
 *      Rotate Array
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array, rotate the array to the right by ‘k’ steps, where ‘k’
 *   is non-negative.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 10⁵’
 *   • ‘-2³¹ ≤ nums[i] ≤ 2³¹ - 1’
 *   • ‘0 ≤ k ≤ 10⁵’
 *   • Try to come up with as many solutions as you can. There are at least “three” different ways to solve this problem.
 *   • Could you do it in-place with ‘O(1)’ extra space?
 *
 */

struct q189 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
      int n = nums.size();
      vector<int> tmp(nums.end() - k % n, nums.end());
      nums.insert(nums.begin(), tmp.begin(), tmp.end());
      nums.resize(n);
    }
  };

  class Solution *solution;
};

TEST_F(q189, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
  int k = 3;
  vector<int> exp = {5, 6, 7, 1, 2, 3, 4};
  solution->rotate(nums, k);
  // Assume the first argument is answer.
  EXPECT_EQ(nums, exp);
  delete solution;
}

TEST_F(q189, sample_input02) {
  solution = new Solution();
  vector<int> nums = {-1, -100, 3, 99};
  int k = 2;
  vector<int> exp = {3, 99, -1, -100};
  solution->rotate(nums, k);
  // Assume the first argument is answer.
  EXPECT_EQ(nums, exp);
  delete solution;
}