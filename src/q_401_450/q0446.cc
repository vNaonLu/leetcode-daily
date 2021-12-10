#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 446.
 *      Arithmetic Slices II - Subsequence
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ , return “the number of all the
 *   “arithmetic subsequences” of” ‘nums’
 *   A sequence of numbers is called arithmetic if it consists of “at least
 *   three elements” and if the difference between any two consecutive
 *   elements is the
 *       - For example, ‘[1, 3, 5, 7, 9]’ , ‘[7, 7, 7, 7]’ , and ‘[3, -1,
 *   -5, -9]’ are arithmetic
 *       - For example, ‘[1, 1, 2, 5, 7]’ is not an arithmetic
 *   A “subsequence” of an array is a sequence that can be formed by
 *   removing some elements (possibly none) of the
 *       - For example, ‘[2,5,10]’ is a subsequence of ‘[1,2,1, “<u>2</u>”
 *   ,4,1,<u> “5” </u>,<u> “10” </u>]’
 *   The test cases are generated so that the answer fits in “32-bit”
 *   integer.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 1000’
 *   • ‘-2³¹ ≤ nums[i] ≤ 2³¹ - 1’
 *
 */

struct q446 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int numberOfArithmeticSlices(vector<int>& nums) {
      int n = nums.size();
      long long res = 0;
      vector<map<long long, int>> cnt(n);
      for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          long long d = (long long)nums[i] - (long long)nums[j];
          int sum = 0;
          if (cnt[j].find(d) != cnt[j].end()) {
            sum = cnt[j][d];
          }
          cnt[i][d] += sum + 1;
          res += sum;
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q446, sample_input01) {
  solution = new Solution();
  vector<int> nums = {2, 4, 6, 8, 10};
  int exp = 7;
  EXPECT_EQ(solution->numberOfArithmeticSlices(nums), exp);
  delete solution;
}

TEST_F(q446, sample_input02) {
  solution = new Solution();
  vector<int> nums = {7, 7, 7, 7, 7};
  int exp = 16;
  EXPECT_EQ(solution->numberOfArithmeticSlices(nums), exp);
  delete solution;
}