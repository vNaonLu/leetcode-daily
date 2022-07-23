#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1712.
 *       Ways to Split Array Into Three Subarrays
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   A split of an integer array is “good”
 *       - The array is split into three “non-empty” contiguous subarrays -
 *   named ‘left’ , ‘mid’ , ‘right’ respectively from left to
 *       - The sum of the elements in ‘left’ is less than or equal to the
 *   sum of the elements in ‘mid’ , and the sum of the elements in ‘mid’ is
 *   less than or equal to the sum of the elements in ‘right’
 *   Given ‘nums’ , an array of “non-negative” integers, return “the number
 *   of “good” ways to split” ‘nums’ . As the number may be too large,
 *   return it “modulo” ‘10^(9 )+ 7’
 *
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘3 ≤ nums.length ≤ 10⁵’
 *   • ‘0 ≤ nums[i] ≤ 10⁴’
 *
 */

struct q1712 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    inline constexpr static int kMod = 1e9 + 7;

  public:
    int waysToSplit(vector<int> &nums) {
      for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
        *it += *(it - 1);
      }

      int res = 0;
      for (int i = 0; i < nums.size() - 1; ++i) {
        int left = -1,
            right = -1;

        int lo = i + 1,
            hi = nums.size() - 2;
        while (lo <= hi) {
          int mid = lo + (hi - lo) / 2;
          if (nums[mid] - nums[i] <= nums.back() - nums[mid]) {
            right = mid;
            lo = mid + 1;
          } else {
            hi = mid - 1;
          }
        }

        lo = i + 1;
        hi = nums.size() - 2;
        while (lo <= hi) {
          int mid = lo + (hi - lo) / 2;
          if (nums[i] <= nums[mid] - nums[i]) {
            left = mid;
            hi = mid - 1;
          } else {
            lo = mid + 1;
          }
        }

        if (left == -1 || right == -1 || left > right) {
          continue;
        }

        res = (res + (right - left + 1) % kMod) % kMod;
      }

      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1712, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 1, 1};
  int exp = 1;
  int act = solution->waysToSplit(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1712, sample_input02) {
  solution = new Solution();
  vector<int> nums = {1, 2, 2, 2, 5, 0};
  int exp = 3;
  int act = solution->waysToSplit(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1712, sample_input03) {
  solution = new Solution();
  vector<int> nums = {3, 2, 1};
  int exp = 0;
  int act = solution->waysToSplit(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}