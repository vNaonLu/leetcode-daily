#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 905.
 *      Sort Array By Parity
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ , move all the even integers at the
 *   beginning of the array followed by all the odd
 *   Return “ “any array” that satisfies this condition” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 5000’
 *   • ‘0 ≤ nums[i] ≤ 5000’
 *
 */

struct q905 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    vector<int> sortArrayByParity(vector<int>& nums) {
      int i = nums.size() - 1,
          j = 0;

      while (i > j) {
        if ((nums[i] & 1) == 0) {
          if (nums[j] & 1) {
            swap(nums[j++], nums[i--]);
          } else {
            ++j;
          }
        } else {
          --i;
        }
      }

      return nums;
    }
  };

  class Solution *solution;
};

TEST_F(q905, sample_input01) {
  solution = new Solution();
  vector<int> nums = {3, 1, 2, 4};
  vector<int> exp = {4, 2, 1, 3};
  vector<int> act = solution->sortArrayByParity(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q905, sample_input02) {
  solution = new Solution();
  vector<int> nums = {0};
  vector<int> exp = {0};
  vector<int> act = solution->sortArrayByParity(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}