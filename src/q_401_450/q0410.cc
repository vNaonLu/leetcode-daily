// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Split Array Largest Sum
//
// https://leetcode.com/problems/split-array-largest-sum/
//
// Question ID: 410
// Difficult  : Hard
// Solve Date : 2022/03/31 13:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |410. Split Array Largest Sum|:
//
// Given an integer array |nums| and an integer |k|, split |nums| into |k|
// non-empty subarrays such that the largest sum of any subarray is minimized.
// Return the minimized largest sum of the split.
// A subarray is a contiguous part of the array.
//  
//

LEETCODE_BEGIN_RESOLVING(410, SplitArrayLargestSum, Solution);

class Solution {
private:
  int helper(vector<int> &nums, int target) {
    int curr = 0, required = 1;

    for (auto &x : nums) {
      if (curr <= target - x) {
        curr += x;
      } else {
        curr = x;
        ++required;
      }
    }

    return required;
  }

public:
  int splitArray(vector<int> &nums, int m) {
    int sum = 0;
    int mx  = -1;
    for (auto &x : nums) {
      sum += x;
      mx = max(mx, x);
    }

    int l = mx, r = sum;
    int res = 0;
    while (l <= r) {
      int allowed = l + (r - l) / 2;
      if (helper(nums, allowed) <= m) {
        r   = allowed - 1;
        res = allowed;
      } else {
        l = allowed + 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] <= 10⁶|
// * |1 <= k <= min(50, nums.length)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [7,2,5,10,8], k = 2
// Output: 18
//
// There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum
// among the two subarrays is only 18.

LEETCODE_SOLUTION_UNITTEST(410, SplitArrayLargestSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 2, 5, 10, 8};
  int         k        = 2;
  int         expect   = 18;
  int         actual   = solution->splitArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5], k = 2
// Output: 9
//
// There are four ways to split nums into two subarrays.
// The best way is to split it into [1,2,3] and [4,5], where the largest sum
// among the two subarrays is only 9.

LEETCODE_SOLUTION_UNITTEST(410, SplitArrayLargestSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         k        = 2;
  int         expect   = 9;
  int         actual   = solution->splitArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
