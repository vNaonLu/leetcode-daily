#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2535.
 *       Difference Between Element Sum and Digit Sum of an Array
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given a positive integer array ‘nums’
 *       - The “element sum” is the sum of all the elements in ‘nums’
 *       - The “digit sum” is the sum of all the digits (not necessarily
 *   distinct) that appear in ‘nums’
 *   Return “the “absolute” difference between the “element sum” and “digit
 *   sum” of ” ‘nums’
 *    “Note” that the absolute difference between two integers ‘x’ and ‘y’
 *   is defined as ‘|x - y|’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 2000’
 *   • ‘1 ≤ nums[i] ≤ 2000’
 *
 * see more details:
 * https://leetcode.com/problems/difference-between-element-sum-and-digit-sum-of-an-array/
 */

struct q2535 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    int digitSum(int x) {
      int res = 0;
      while (x != 0) {
        res += x % 10;
        x /= 10;
      }
      return res;
    }

  public:
    int differenceOfSum(vector<int> &nums) {
      int sum       = 0;
      int digit_sum = 0;
      for (auto x : nums) {
        sum += x;
        digit_sum += digitSum(x);
      }
      return abs(sum - digit_sum);
    }
  };

  class Solution *solution;
};

TEST_F(q2535, sample_input01) {
  solution         = new Solution();
  vector<int> nums = {1, 15, 6, 3};
  int         exp  = 9;
  int         act  = solution->differenceOfSum(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2535, sample_input02) {
  solution         = new Solution();
  vector<int> nums = {1, 2, 3, 4};
  int         exp  = 0;
  int         act  = solution->differenceOfSum(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}
