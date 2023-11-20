// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Element After Decreasing and Rearranging
//
// https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/
//
// Question ID: 1846
// Difficult  : Medium
// Solve Date : 2023/11/15 19:07

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1846. Maximum Element After Decreasing and Rearranging|:
//
// You are given an array of positive integers |arr|. Perform some operations
// (possibly none) on |arr| so that it satisfies these conditions:
//
//  • The value of the first element in |arr| must be |1|.
//
//  • The absolute difference between any 2 adjacent elements must be less than
//  or equal to |1|. In other words, |abs(arr[i] - arr[i - 1]) <= 1| for each
//  |i| where |1 <= i < arr.length| (0-indexed). |abs(x)| is the absolute value
//  of |x|.
// There are 2 types of operations that you can perform any number of times:
//
//  • Decrease the value of any element of |arr| to a smaller positive integer.
//
//  • Rearrange the elements of |arr| to be in any order.
// Return the maximum possible value of an element in |arr| after performing the
// operations to satisfy the conditions.
//
//

LEETCODE_BEGIN_RESOLVING(1846, MaximumElementAfterDecreasingAndRearranging,
                         Solution);

class Solution {
public:
  int maximumElementAfterDecrementingAndRearranging(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    int res = 1;
    for (int i = 1; i < arr.size(); ++i) {
      if (arr[i] > res) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁵|
// * |1 <= arr[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,2,1,2,1]
// Output: 2
//
// We can satisfy the conditions by rearranging |arr| so it becomes
// |[1,2,2,2,1]|. The largest element in |arr| is 2.

LEETCODE_SOLUTION_UNITTEST(1846, MaximumElementAfterDecreasingAndRearranging,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 2, 1, 2, 1};
  int         expect   = 2;
  int actual = solution->maximumElementAfterDecrementingAndRearranging(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [100,1,1000]
// Output: 3
//
// One possible way to satisfy the conditions is by doing the following:
// 1. Rearrange |arr| so it becomes |[1,100,1000]|.
// 2. Decrease the value of the second element to 2.
// 3. Decrease the value of the third element to 3.
// Now |arr = [1,2,3], which |satisfies the conditions.
// The largest element in |arr is 3.|

LEETCODE_SOLUTION_UNITTEST(1846, MaximumElementAfterDecreasingAndRearranging,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {100, 1, 1000};
  int         expect   = 3;
  int actual = solution->maximumElementAfterDecrementingAndRearranging(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,2,3,4,5]
// Output: 5
//
// The array already satisfies the conditions, and the largest element is 5.

LEETCODE_SOLUTION_UNITTEST(1846, MaximumElementAfterDecreasingAndRearranging,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5};
  int         expect   = 5;
  int actual = solution->maximumElementAfterDecrementingAndRearranging(arr);
  LCD_EXPECT_EQ(expect, actual);
}
