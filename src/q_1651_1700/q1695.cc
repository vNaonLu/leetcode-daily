// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Erasure Value
//
// https://leetcode.com/problems/maximum-erasure-value/
//
// Question ID: 1695
// Difficult  : Medium
// Solve Date : 2022/06/12 14:29

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1695. Maximum Erasure Value|:
//
// You are given an array of positive integers |nums| and want to erase a
// subarray containingunique elements. The score you get by erasing the subarray
// is equal to the sum of its elements. Return the maximum score you can get by
// erasing exactly one subarray. An array |b| is called to be a subarray of |a|
// if it forms a contiguous subsequence of |a|, that is, if it is equal to
// |a[l],a[l+1],...,a[r]| for some |(l,r)|.
//

LEETCODE_BEGIN_RESOLVING(1695, MaximumErasureValue, Solution);

class Solution {
public:
  int maximumUniqueSubarray(vector<int> &nums) {
    int         res = 0, local = 0, l = 0;
    vector<int> cnt(10001, 0);

    for (int i = 0; i < nums.size(); ++i) {
      local += nums[i];
      ++cnt[nums[i]];
      while (l <= i && cnt[nums[i]] > 1) {
        --cnt[nums[l]];
        local -= nums[l];
        ++l;
      }

      res = max(res, local);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,4,5,6]
// Output: 17
//
// The optimal subarray here is [2,4,5,6].

LEETCODE_SOLUTION_UNITTEST(1695, MaximumErasureValue, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 4, 5, 6};
  int         expect   = 17;
  int         actual   = solution->maximumUniqueSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,2,1,2,5,2,1,2,5]
// Output: 8
//
// The optimal subarray here is [5,2,1] or [1,2,5].

LEETCODE_SOLUTION_UNITTEST(1695, MaximumErasureValue, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 1, 2, 5, 2, 1, 2, 5};
  int         expect   = 8;
  int         actual   = solution->maximumUniqueSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
