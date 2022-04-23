#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 704.
 *      Binary Search
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array of integers ‘nums’ which is sorted in ascending order,
 *   and an integer ‘target’ , write a function to search ‘target’ in
 *   ‘nums’ . If ‘target’ exists, then return its index. Otherwise, return
 *   ‘-1’
 *   You must write an algorithm with ‘O(log n)’ runtime complexity.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 10⁴’
 *   • ‘-10⁴ < nums[i], target < 10⁴’
 *   • All the integers in ‘nums’ are “unique” .
 *   • ‘nums’ is sorted in ascending order.
 *
 */

struct q704 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int search(vector<int>& nums, int target) {
      int l = 0, r = nums.size() - 1;
      while (l <= r) {
        int m = l + (r - l) / 2;
        if (nums[m] == target) {
          return m;
        } else if (nums[m] > target) {
          r = m - 1;
        } else {
          l = m + 1;
        }
      }

      return -1;
    }
  };

  class Solution *solution;
};

TEST_F(q704, sample_input01) {
  solution = new Solution();
  vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 9;
  int exp = 4;
  int act = solution->search(nums, target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q704, sample_input02) {
  solution = new Solution();
  vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 2;
  int exp = -1;
  int act = solution->search(nums, target);
  EXPECT_EQ(act, exp);
  delete solution;
}