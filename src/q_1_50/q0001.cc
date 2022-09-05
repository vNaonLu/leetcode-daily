#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 1.
 *    Two Sum
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array of integers ‘nums’ and an integer ‘target’ , return
 *   “indices of the two numbers such that they add up to ‘target’ ”
 *   You may assume that each input would have “ “exactly” one solution” ,
 *   and you may not use the “same” element
 *   You can return the answer in any order.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘2 ≤ nums.length ≤ 10⁴’
 *   • ‘-10⁹ ≤ nums[i] ≤ 10⁹’
 *   • ‘-10⁹ ≤ target ≤ 10⁹’
 *   • “Only one valid answer exists.”
 *
 */

struct q1 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
      auto memo = unordered_map<int, int>();
      auto i    = (int)0;
      for (int i = 0; i < nums.size(); ++i) {
        auto find = memo.find(target - nums[i]);
        if (find != memo.end()) {
          return vector<int>{find->second, i};
        }
        memo.emplace(nums[i], i);
      }
      return vector<int>{-1, -1};
    }
  };

  class Solution *solution;
};

TEST_F(q1, sample_input01) {
  solution           = new Solution();
  vector<int> nums   = {2, 7, 11, 15};
  int         target = 9;
  vector<int> exp    = {0, 1};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->twoSum(nums, target), exp);
  delete solution;
}

TEST_F(q1, sample_input02) {
  solution           = new Solution();
  vector<int> nums   = {3, 2, 4};
  int         target = 6;
  vector<int> exp    = {1, 2};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->twoSum(nums, target), exp);
  delete solution;
}

TEST_F(q1, sample_input03) {
  solution           = new Solution();
  vector<int> nums   = {3, 3};
  int         target = 6;
  vector<int> exp    = {0, 1};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->twoSum(nums, target), exp);
  delete solution;
}