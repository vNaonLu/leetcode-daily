// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Subarrays with Bounded Maximum
//
// https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
//
// Question ID: 795
// Difficult  : Medium
// Solve Date : 2024/07/06 14:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |795. Number of Subarrays with Bounded Maximum|:
//
// Given an integer array |nums| and two integers |left| and |right|, return the
// number of contiguous non-empty subarrays such that the value of the maximum
// array element in that subarray is in the range |[left, right]|. The test
// cases are generated so that the answer will fit in a 32-bit integer.
//
//

LEETCODE_BEGIN_RESOLVING(795, NumberOfSubarraysWithBoundedMaximum, Solution);

class Solution {
public:
  int numSubarrayBoundedMax(vector<int> &nums, int left, int right) {
    return helper(nums, right) - helper(nums, left - 1);
  }

private:
  int helper(const auto &nums, int bound) {
    int res = 0;
    int cnt = 0;
    for (auto x : nums) {
      cnt = x <= bound ? (cnt + 1) : 0;
      res += cnt;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
// * |0 <= left <= right <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,4,3], left = 2, right = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(795, NumberOfSubarraysWithBoundedMaximum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 4, 3};
  int         left     = 2;
  int         right    = 3;
  int         expect   = 3;
  int         actual   = solution->numSubarrayBoundedMax(nums, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,9,2,5,6], left = 2, right = 8
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(795, NumberOfSubarraysWithBoundedMaximum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 9, 2, 5, 6};
  int         left     = 2;
  int         right    = 8;
  int         expect   = 7;
  int         actual   = solution->numSubarrayBoundedMax(nums, left, right);
  LCD_EXPECT_EQ(expect, actual);
}
