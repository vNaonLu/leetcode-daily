// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Value at a Given Index in a Bounded Array
//
// https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/
//
// Question ID: 1802
// Difficult  : Medium
// Solve Date : 2022/07/30 17:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1802. Maximum Value at a Given Index in a Bounded Array|:
//
// You are given three positive integers: |n|, |index|, and |maxSum|. You want
// to construct an array |nums| (0-indexed) that satisfies the following
// conditions:
//
//  • |nums.length == n|
//
//  • |nums[i]| is a positive integer where |0 <= i < n|.
//
//  • |abs(nums[i] - nums[i+1]) <= 1| where |0 <= i < n-1|.
//
//  • The sum of all the elements of |nums| does not exceed |maxSum|.
//
//  • |nums[index]| is maximized.
// Return |nums[index]| of the constructed array.
// Note that |abs(x)| equals |x| if |x >= 0|, and |-x| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1802, MaximumValueAtAGivenIndexInABoundedArray,
                         Solution);

class Solution {
private:
  bool helper(int n, int i, double maxSum, double x) {
    double leftSum =
        x < i + 1 ? (1 + x) * x / 2 + (i - x + 1) : (x + x - i) * (i + 1) / 2;
    double rightSum = x < n - i - 1 + 1
                          ? (1 + x) * x / 2 + (n - i - x) - x
                          : (x + x - (n - i - 1)) * (n - i) / 2 - x;

    return leftSum + rightSum <= maxSum;
  }

public:
  int maxValue(int n, int index, int maxSum) {
    int lo = 1, hi = maxSum, res = 1;

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;

      if (helper(n, index, maxSum, mid)) {
        res = mid;
        lo  = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= maxSum <= 10⁹|
// * |0 <= index < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, index = 2, maxSum = 6
// Output: 2
//
// nums = [1,2,2,1] is one array that satisfies all the conditions.
// There are no arrays that satisfy all the conditions and have nums[2] == 3, so
// 2 is the maximum nums[2].

LEETCODE_SOLUTION_UNITTEST(1802, MaximumValueAtAGivenIndexInABoundedArray,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  index    = 2;
  int  maxSum   = 6;
  int  expect   = 2;
  int  actual   = solution->maxValue(n, index, maxSum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, index = 1, maxSum = 10
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1802, MaximumValueAtAGivenIndexInABoundedArray,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  index    = 1;
  int  maxSum   = 10;
  int  expect   = 3;
  int  actual   = solution->maxValue(n, index, maxSum);
  LCD_EXPECT_EQ(expect, actual);
}
