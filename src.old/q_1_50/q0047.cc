#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 47.
 *     Permutations II
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a collection of numbers, ‘nums’ ,that might contain duplicates,
 *   return “all possible unique permutations “in any order” .” 
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 8’
 *   • ‘-10 ≤ nums[i] ≤ 10’
 *
 */

struct q47 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    void helper(vector<vector<int>> &r, vector<int> &c, unordered_map<int, int> &cnt, const int &size) {
      if (size == c.size()) {
        r.push_back(c);
      } else {
        for (auto it = cnt.begin(); it != cnt.end(); ++it) {
          if (it->second == 0) continue;
          --it->second;
          helper(r, c, cnt, size);
          c.push_back(it->first);
          helper(r, c, cnt, size);
          c.pop_back();
          ++it->second;
        }
      }
    }
   public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
      unordered_map<int, int> cnt;
      vector<vector<int>> res;
      vector<int> tmp;
      for (const auto &n : nums) ++cnt[n];
      helper(res, tmp, cnt, nums.size());
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q47, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> exp = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->permuteUnique(nums), exp);
  delete solution;
}