// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Subsequence in Non-Increasing Order
//
// https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/
//
// Question ID: 1403
// Difficult  : Easy
// Solve Date : 2023/08/11 12:13

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1403. Minimum Subsequence in Non-Increasing Order|:
//
// Given the array |nums|, obtain a subsequence of the array whose sum of
// elements is strictly greater than the sum of the non included elements in
// such subsequence. If there are multiple solutions, return the subsequence
// with minimum size and if there still exist multiple solutions, return the
// subsequence with the maximum total sum of all its elements. A subsequence of
// an array can be obtained by erasing some (possibly zero) elements from the
// array. Note that the solution with the given constraints is guaranteed to be
// unique. Also return the answer sorted in non-increasing order.
//
//

LEETCODE_BEGIN_RESOLVING(1403, MinimumSubsequenceInNonIncreasingOrder,
                         Solution);

class Solution {
public:
  vector<int> minSubsequence(vector<int> &nums) {
    int         sum = accumulate(nums.begin(), nums.end(), 0);
    vector<int> res;
    sort(nums.begin(), nums.end(), greater<int>());
    int partial = 0;
    for (auto x : nums) {
      partial += x;
      res.emplace_back(x);
      if (partial > sum - partial) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 500|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,10,9,8]
// Output: [10,9]
//
// The subsequences [10,9] and [10,8] are minimal such that the sum of their
// elements is strictly greater than the sum of elements not included. However,
// the subsequence [10,9] has the maximum total sum of its elements.

LEETCODE_SOLUTION_UNITTEST(1403, MinimumSubsequenceInNonIncreasingOrder,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 10, 9, 8};
  vector<int> expect   = {10, 9};
  vector<int> actual   = solution->minSubsequence(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,4,7,6,7]
// Output: [7,7,6]
//
// The subsequence [7,7] has the sum of its elements equal to 14 which is not
// strictly greater than the sum of elements not included (14 = 4 + 4 + 6).
// Therefore, the subsequence [7,6,7] is the minimal satisfying the conditions.
// Note the subsequence has to be returned in non-decreasing order.

LEETCODE_SOLUTION_UNITTEST(1403, MinimumSubsequenceInNonIncreasingOrder,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 7, 6, 7};
  vector<int> expect   = {7, 7, 6};
  vector<int> actual   = solution->minSubsequence(nums);
  LCD_EXPECT_EQ(expect, actual);
}
