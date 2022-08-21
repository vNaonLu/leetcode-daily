#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 659.
 *      Split Array into Consecutive Subsequences
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given an integer array ‘nums’ that is “sorted in
 *   non-decreasing order”
 *   Determine if it is possible to split ‘nums’ into “one or more
 *   subsequences” such that “both” of the following conditions are
 *       - Each subsequence is a “consecutive increasing sequence” (i.e.
 *   each integer is “exactly one” more than the previous
 *       - All subsequences have a length of ‘3’ “ or more”
 *   Return ‘true’ “ if you can split ” ‘nums’ “ according to the above
 *   conditions, or ” ‘false’ “ otherwise”
 *   A “subsequence” of an array is a new array that is formed from the
 *   original array by deleting some (can be none) of the elements without
 *   disturbing the relative positions of the remaining elements. (i.e.,
 *   ‘[1,3,5]’ is a subsequence of ‘[<u>1</u>,2,<u>3</u>,4,<u>5</u>]’ while
 *   ‘[1,3,2]’ is not).
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 10⁴’
 *   • ‘-1000 ≤ nums[i] ≤ 1000’
 *   • ‘nums’ is sorted in “non-decreasing” order.
 *
 */

struct q659 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    bool isPossible(vector<int> &nums) {
      auto freq = unordered_map<int, int>();
      auto need = unordered_map<int, int>();
      for (auto x : nums) {
        ++freq[x];
      }

      for (auto x : nums) {
        if (freq[x] == 0) {
          /// all are taken
          continue;
        }

        if (need[x] > 0) {
          --need[x];
          --freq[x];

          ++need[x + 1];
        } else if (freq[x] > 0 && freq[x + 1] > 0 && freq[x + 2] > 0) {
          --freq[x];
          --freq[x + 1];
          --freq[x + 2];

          ++need[x + 3];
        } else {

          return false;
        }
      }

      return true;
    }
  };

  class Solution *solution;
};

TEST_F(q659, sample_input01) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3, 3, 4, 5};
  bool exp = true;
  bool act = solution->isPossible(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q659, sample_input02) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 5};
  bool exp = true;
  bool act = solution->isPossible(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q659, sample_input03) {
  solution = new Solution();
  vector<int> nums = {1, 2, 3, 4, 4, 5};
  bool exp = false;
  bool act = solution->isPossible(nums);
  EXPECT_EQ(act, exp);
  delete solution;
}