// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Rotate Function
//
// https://leetcode.com/problems/rotate-function/
//
// Question ID: 396
// Difficult  : Medium
// Solve Date : 2024/03/22 13:00

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |396. Rotate Function|:
//
// You are given an integer array |nums| of length |n|.
// Assume |arrₖ| to be an array obtained by rotating |nums| by |k| positions
// clock-wise. We define the rotation function |F| on |nums| as follow:
//
//  • |F(k) = 0 * arrₖ[0] + 1 * arrₖ[1] + ... + (n - 1) * arrₖ[n - 1].|
// Return the maximum value of |F(0), F(1), ..., F(n-1)|.
// The test cases are generated so that the answer fits in a 32-bit integer.
//
//

LEETCODE_BEGIN_RESOLVING(396, RotateFunction, Solution);

class Solution {
public:
  int maxRotateFunction(vector<int> &nums) {
    int n   = nums.size();
    int res = 0;
    int sum = 0;
    int pre = 0;
    for (int i = 0; i < n; ++i) {
      res += i * nums[i];
      sum += nums[i];
    }
    pre        = res;
    int rotate = 1;
    for (auto it = nums.rbegin(); rotate < n; ++it, ++rotate) {
      pre = pre + sum - n * *it;
      res = max(res, pre);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁵|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,2,6]
// Output: 26
//

LEETCODE_SOLUTION_UNITTEST(396, RotateFunction, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 6};
  int         expect   = 26;
  int         actual   = solution->maxRotateFunction(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [100]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(396, RotateFunction, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {100};
  int         expect   = 0;
  int         actual   = solution->maxRotateFunction(nums);
  LCD_EXPECT_EQ(expect, actual);
}
