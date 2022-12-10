#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 349.
 *      Intersection of Two Arrays
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given two integer arrays ‘nums1’ and ‘nums2’ , return “an array of
 *   their intersection” . Each element in the result must be “unique” and
 *   you may return the result in “any order” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums1.length, nums2.length ≤ 1000’
 *   • ‘0 ≤ nums1[i], nums2[i] ≤ 1000’
 *
 */

struct q349 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
      auto nums1_map = unordered_set<int>(nums1.begin(), nums1.end());
      auto res       = unordered_set<int>();
      for (auto x : nums2) {
        if (nums1_map.count(x)) {
          res.emplace(x);
        }
      }
      return vector<int>{res.begin(), res.end()};
    }
  };

  class Solution *solution;
};

TEST_F(q349, sample_input01) {
  solution          = new Solution();
  vector<int> nums1 = {1, 2, 2, 1};
  vector<int> nums2 = {2, 2};
  vector<int> exp   = {2};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->intersection(nums1, nums2), exp);
  delete solution;
}

TEST_F(q349, sample_input02) {
  solution          = new Solution();
  vector<int> nums1 = {4, 9, 5};
  vector<int> nums2 = {9, 4, 9, 8, 4};
  vector<int> exp   = {9, 4};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->intersection(nums1, nums2), exp);
  delete solution;
}