#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 229.
 *      Majority Element II
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array of size ‘n’ , find all elements that appear
 *   more than ‘&lfloor; n/3 &rfloor;’ times.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 5 × 10⁴’
 *   • ‘-10⁹ ≤ nums[i] ≤ 10⁹’
 *
 */

struct q229 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    vector<int> majorityElement(vector<int> &nums) {
      auto n    = nums.size();
      auto freq = unordered_map<int, int>();
      auto res  = set<int>();

      for (auto x : nums) {
        ++freq[x];
        if (freq[x] > n / 3) {
          res.emplace(x);
        }
      }

      return vector<int>(res.begin(), res.end());
    }
  };

  class Solution *solution;
};

TEST_F(q229, sample_input01) {
  solution         = new Solution();
  vector<int> nums = {3, 2, 3};
  vector<int> exp  = {3};
  vector<int> act  = solution->majorityElement(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q229, sample_input02) {
  solution         = new Solution();
  vector<int> nums = {1};
  vector<int> exp  = {1};
  vector<int> act  = solution->majorityElement(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q229, sample_input03) {
  solution         = new Solution();
  vector<int> nums = {1, 2};
  vector<int> exp  = {1, 2};
  vector<int> act  = solution->majorityElement(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}