// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Exceed Threshold Value I
//
// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/
//
// Question ID: 3065
// Difficult  : Easy
// Solve Date : 2024/03/06 20:30

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3065. Minimum Operations to Exceed Threshold Value I|:
//
// You are given a 0-indexed integer array |nums|, and an integer |k|.
// In one operation, you can remove one occurrence of the smallest element of
// |nums|. Return the minimum number of operations needed so that all elements
// of the array are greater than or equal to |k|.
//
//

LEETCODE_BEGIN_RESOLVING(3065, MinimumOperationsToExceedThresholdValueI,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    return count_if(nums.begin(), nums.end(), [k](auto x) { return x < k; });
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= k <= 10⁹|
// * The input is generated such that there is at least one index |i| such that
// |nums[i] >= k|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,11,10,1,3], k = 10
// Output: 3
//
// After one operation, nums becomes equal to [2, 11, 10, 3].
// After two operations, nums becomes equal to [11, 10, 3].
// After three operations, nums becomes equal to [11, 10].
// At this stage, all the elements of nums are greater than or equal to 10 so we
// can stop. It can be shown that 3 is the minimum number of operations needed
// so that all elements of the array are greater than or equal to 10.

LEETCODE_SOLUTION_UNITTEST(3065, MinimumOperationsToExceedThresholdValueI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 11, 10, 1, 3};
  int         k        = 10;
  int         expect   = 3;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,2,4,9], k = 1
// Output: 0
//
// All elements of the array are greater than or equal to 1 so we do not need to
// apply any operations on nums.

LEETCODE_SOLUTION_UNITTEST(3065, MinimumOperationsToExceedThresholdValueI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 4, 9};
  int         k        = 1;
  int         expect   = 0;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,2,4,9], k = 9
// Output: 4
//
// only a single element of nums is greater than or equal to 9 so we need to
// apply the operations 4 times on nums.

LEETCODE_SOLUTION_UNITTEST(3065, MinimumOperationsToExceedThresholdValueI,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 4, 9};
  int         k        = 9;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
