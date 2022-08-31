#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 414.
 *      Third Maximum Number
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ , return “the “third distinct maximum”
 *   number in this array. If the third maximum does not exist, return the
 *   “maximum” number” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 10⁴’
 *   • ‘-2³¹ ≤ nums[i] ≤ 2³¹ - 1’
 *
 */

struct q414 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int thirdMax(vector<int> &nums) {
      auto exist    = unordered_set<int64_t>();
      auto distinct = vector<int64_t>();
      for (auto x : nums) {
        auto [it, suc] = exist.emplace(x);
        if (suc) {
          distinct.emplace_back(x);
        }
      }
      if (distinct.size() < 3) {
        return *max_element(distinct.begin(), distinct.end());
      } else {
        auto it = distinct.begin() + 2;
        nth_element(distinct.begin(), it, distinct.end(), greater<int>{});
        return *it;
      }
    }
  };

  class Solution *solution;
};

TEST_F(q414, sample_input01) {
  solution         = new Solution();
  vector<int> nums = {3, 2, 1};
  int         exp  = 1;
  int         act  = solution->thirdMax(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q414, sample_input02) {
  solution         = new Solution();
  vector<int> nums = {1, 2};
  int         exp  = 2;
  int         act  = solution->thirdMax(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q414, sample_input03) {
  solution         = new Solution();
  vector<int> nums = {2, 2, 3, 1};
  int         exp  = 1;
  int         act  = solution->thirdMax(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}