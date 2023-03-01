// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Reduce X to Zero
//
// https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
//
// Question ID: 1658
// Difficult  : Medium
// Solve Date : 2022/06/11 12:29

#include <iosfwd>
#include <limits>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1658. Minimum Operations to Reduce X to Zero|:
//
// You are given an integer array |nums| and an integer |x|. In one operation,
// you can either remove the leftmost or the rightmost element from the array
// |nums| and subtract its value from |x|. Note that this modifies the array for
// future operations. Return the minimum number of operations to reduce |x| to
// exactly |0| if it is possible, otherwise, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(1658, MinimumOperationsToReduceXToZero, Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int x) {
    int sum    = accumulate(nums.begin(), nums.end(), 0);
    int target = sum - x;
    int res = numeric_limits<int>::min(), curr = 0, l = 0;
    for (int i = 0; i < nums.size(); ++i) {
      curr += nums[i];
      while (l <= i && curr > target) {
        curr -= nums[l++];
      }

      if (curr == target) {
        res = max(res, i - l + 1);
      }
    }

    return res == numeric_limits<int>::min() ? -1 : (nums.size() - res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁴|
// * |1 <= x <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,4,2,3], x = 5
// Output: 2
//
// The optimal solution is to remove the last two elements to reduce x to zero.

LEETCODE_SOLUTION_UNITTEST(1658, MinimumOperationsToReduceXToZero, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 4, 2, 3};
  int         x        = 5;
  int         expect   = 2;
  int         actual   = solution->minOperations(nums, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,6,7,8,9], x = 4
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1658, MinimumOperationsToReduceXToZero, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 6, 7, 8, 9};
  int         x        = 4;
  int         expect   = -1;
  int         actual   = solution->minOperations(nums, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,20,1,1,3], x = 10
// Output: 5
//
// The optimal solution is to remove the last three elements and the first two
// elements (5 operations in total) to reduce x to zero.

LEETCODE_SOLUTION_UNITTEST(1658, MinimumOperationsToReduceXToZero, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 20, 1, 1, 3};
  int         x        = 10;
  int         expect   = 5;
  int         actual   = solution->minOperations(nums, x);
  LCD_EXPECT_EQ(expect, actual);
}
