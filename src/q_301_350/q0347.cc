#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 347.
 *      Top K Frequent Elements
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ and an integer ‘k’ , return “the” ‘k’
 *   “most frequent elements” . You may return the answer in “any order” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 10⁵’
 *   • ‘k’ is in the range ‘[1, the number of unique elements in the array]’ .
 *   • It is “guaranteed” that the answer is “unique” .
 *
 */

struct q347 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
      unordered_map<int, int> cnt;
      for (const auto& n : nums) ++cnt[n];
      set<pair<int, int>> ordered;
      for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        ordered.insert(make_pair(it->second, it->first));
      }
      vector<int> res;
      for (auto it = ordered.rbegin(); it != ordered.rend(); ++it) {
        res.push_back((*it).second);
        if (res.size() == k) break;
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q347, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 1, 1, 2, 2, 3};
  int k = 2;
  vector<int> exp = {1, 2};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->topKFrequent(nums, k), exp);
  delete solution;
}

TEST_F(q347, sample_input02) {
  solution = new Solution();
  vector<int> nums = {1};
  int k = 1;
  vector<int> exp = {1};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->topKFrequent(nums, k), exp);
  delete solution;
}