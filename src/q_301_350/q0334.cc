#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 334.
 *      Increasing Triplet Subsequence
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ , return ‘true’ “ if there exists a
 *   triple of indices ” ‘(i, j, k)’ “ such that ” ‘i < j < k’ “ and ”
 *   ‘nums[i] < nums[j] < nums[k]’ . If no such indices exists, return
 *   ‘false’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 5 × 10⁵’
 *   • ‘-2³¹ ≤ nums[i] ≤ 2³¹ - 1’
 *
 */

struct q334 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    bool increasingTriplet(vector<int>& nums) {
      int first = numeric_limits<int>::max(),
          second = numeric_limits<int>::max();
      for (int i = 0; i < nums.size(); ++i) {
        if (first >= nums[i]) {
          first = nums[i];
        } else if (second >= nums[i]) {
          second = nums[i];
        } else {
          return true;
        }
      }
      return false;
    }
  };

  class Solution *solution;
};

TEST_F(q334, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3, 4, 5};
  bool exp = true;
  EXPECT_EQ(solution->increasingTriplet(nums), exp);
  delete solution;
}

TEST_F(q334, sample_input02) {
  solution = new Solution();
  vector<int> nums = {5, 4, 3, 2, 1};
  bool exp = false;
  EXPECT_EQ(solution->increasingTriplet(nums), exp);
  delete solution;
}

TEST_F(q334, sample_input03) {
  solution = new Solution();
  vector<int> nums = {2, 1, 5, 0, 4, 6};
  bool exp = true;
  EXPECT_EQ(solution->increasingTriplet(nums), exp);
  delete solution;
}