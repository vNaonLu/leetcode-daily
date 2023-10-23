// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Score of a Good Subarray
//
// https://leetcode.com/problems/maximum-score-of-a-good-subarray/
//
// Question ID: 1793
// Difficult  : Hard
// Solve Date : 2023/10/22 15:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1793. Maximum Score of a Good Subarray|:
//
// You are given an array of integers |nums| (0-indexed) and an integer |k|.
// The score of a subarray |(i, j)| is defined as |min(nums[i], nums[i+1], ...,
// nums[j]) * (j - i + 1)|. A good subarray is a subarray where |i <= k <= j|.
// Return the maximum possible score of a good subarray.
//
//

LEETCODE_BEGIN_RESOLVING(1793, MaximumScoreOfAGoodSubarray, Solution);

class Solution {
public:
  int maximumScore(vector<int> &nums, int k) {
    int n = nums.size();
    if (n == 1) {
      return nums[0];
    }

    int res = 0;
    int mn  = nums[k];
    int i   = k;
    int j   = k;
    while (i > 0 || j < n - 1) {
      if (i == 0) {
        ++j;
      } else if (j == (n - 1)) {
        --i;
      } else if (nums[i - 1] < nums[j + 1]) {
        ++j;
      } else {
        --i;
      }
      mn  = min({mn, nums[i], nums[j]});
      res = max(res, mn * (j - i + 1));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 2 * 10⁴|
// * |0 <= k < nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,4,3,7,4,5], k = 3
// Output: 15
//
// The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 *
// 5 = 15.

LEETCODE_SOLUTION_UNITTEST(1793, MaximumScoreOfAGoodSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 3, 7, 4, 5};
  int         k        = 3;
  int         expect   = 15;
  int         actual   = solution->maximumScore(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,5,4,5,4,1,1,1], k = 0
// Output: 20
//
// The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) * (4-0+1) = 4 *
// 5 = 20.

LEETCODE_SOLUTION_UNITTEST(1793, MaximumScoreOfAGoodSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 4, 5, 4, 1, 1, 1};
  int         k        = 0;
  int         expect   = 20;
  int         actual   = solution->maximumScore(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
