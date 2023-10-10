// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Make Array Continuous
//
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/
//
// Question ID: 2009
// Difficult  : Hard
// Solve Date : 2023/10/10 12:16

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2009. Minimum Number of Operations to Make Array Continuous|:
//
// You are given an integer array |nums|. In one operation, you can replace any
// element in |nums| with any integer. |nums| is considered continuous if both
// of the following conditions are fulfilled:
//
//  • All elements in |nums| are unique.
//
//  • The difference between the maximum element and the minimum element in
//  |nums| equals |nums.length - 1|.
// For example, |nums = [4, 2, 5, 3]| is continuous, but |nums = [1, 2, 3, 5,
// 6]| is not continuous. Return the minimum number of operations to make |nums|
// continuous.
//
//

LEETCODE_BEGIN_RESOLVING(2009, MinimumNumberOfOperationsToMakeArrayContinuous,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    int n         = nums.size();
    int lo        = 0;
    int max_count = 1;
    int cur_count = 1;

    for (int hi = 1; hi < n; ++hi) {
      if (nums[hi] == nums[hi - 1]) {
        continue;
      }

      while (nums[hi] - nums[lo] > n - 1) {
        if (lo < n && nums[lo + 1] == nums[lo]) {
          ++cur_count;
        }
        ++lo;
        --cur_count;
      }
      ++cur_count;
      max_count = max(max_count, cur_count);
    }
    return n - max_count;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,5,3]
// Output: 0
//
//  nums is already continuous.

LEETCODE_SOLUTION_UNITTEST(2009, MinimumNumberOfOperationsToMakeArrayContinuous,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 5, 3};
  int         expect   = 0;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,5,6]
// Output: 1
//
//  One possible solution is to change the last element to 4.
// The resulting array is [1,2,3,5,4], which is continuous.

LEETCODE_SOLUTION_UNITTEST(2009, MinimumNumberOfOperationsToMakeArrayContinuous,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 5, 6};
  int         expect   = 1;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,10,100,1000]
// Output: 3
//
//  One possible solution is to:
// - Change the second element to 2.
// - Change the third element to 3.
// - Change the fourth element to 4.
// The resulting array is [1,2,3,4], which is continuous.

LEETCODE_SOLUTION_UNITTEST(2009, MinimumNumberOfOperationsToMakeArrayContinuous,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 10, 100, 1000};
  int         expect   = 3;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
