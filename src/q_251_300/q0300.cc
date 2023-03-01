// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Increasing Subsequence
//
// https://leetcode.com/problems/longest-increasing-subsequence/
//
// Question ID: 300
// Difficult  : Medium
// Solve Date : 2021/10/04 12:12

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |300. Longest Increasing Subsequence|:
//
// Given an integer array |nums|, return the length of the longest strictly
// increasing subsequence.  
//

LEETCODE_BEGIN_RESOLVING(300, LongestIncreasingSubsequence, Solution);

class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    int         res = 0;
    vector<int> piles(nums.size(), numeric_limits<int>::max());
    for (int i = 0; i < nums.size(); ++i) {
      int idx =
          lower_bound(piles.begin(), piles.end(), nums[i]) - piles.begin();
      piles[idx] = nums[i];
      res        = max(res, idx + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2500|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
//
// The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

LEETCODE_SOLUTION_UNITTEST(300, LongestIncreasingSubsequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 9, 2, 5, 3, 7, 101, 18};
  int         expect   = 4;
  int         actual   = solution->lengthOfLIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,0,3,2,3]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(300, LongestIncreasingSubsequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0, 3, 2, 3};
  int         expect   = 4;
  int         actual   = solution->lengthOfLIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [7,7,7,7,7,7,7]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(300, LongestIncreasingSubsequence, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 7, 7, 7, 7, 7, 7};
  int         expect   = 1;
  int         actual   = solution->lengthOfLIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}
