// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Mountain in Array
//
// https://leetcode.com/problems/longest-mountain-in-array/
//
// Question ID: 845
// Difficult  : Medium
// Solve Date : 2024/08/27 18:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |845. Longest Mountain in Array|:
//
// You may recall that an array |arr| is a mountain array if and only if:
//
//  • |arr.length >= 3|
//
//  • There exists some index |i| (0-indexed) with |0 < i < arr.length - 1| such
//  that:
//
//
//    • |arr[0] < arr[1] < ... < arr[i - 1] < arr[i]|
//
//    • |arr[i] > arr[i + 1] > ... > arr[arr.length - 1]|
//
//
// Given an integer array |arr|, return the length of the longest subarray,
// which is a mountain. Return |0| if there is no mountain subarray.
//
//

LEETCODE_BEGIN_RESOLVING(845, LongestMountainInArray, Solution);

class Solution {
public:
  int longestMountain(vector<int> &arr) {
    int         n   = arr.size();
    int         res = 0;
    vector<int> up(n);
    vector<int> down(n);
    for (int i = n - 2; i >= 0; --i) {
      if (arr[i] > arr[i + 1]) {
        down[i] = down[i + 1] + 1;
      }
    }
    for (int i = 0; i < n; ++i) {
      if (i > 0 && arr[i] > arr[i - 1]) {
        up[i] = up[i - 1] + 1;
      }
      if (up[i] && down[i]) {
        res = max(res, up[i] + down[i] + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |0 <= arr[i] <= 10⁴|
// * Can you solve it using only one pass?
// * Can you solve it in |O(1)| space?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,1,4,7,3,2,5]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(845, LongestMountainInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 1, 4, 7, 3, 2, 5};
  int         expect   = 5;
  int         actual   = solution->longestMountain(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [2,2,2]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(845, LongestMountainInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 2, 2};
  int         expect   = 0;
  int         actual   = solution->longestMountain(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [2,1,4,7,3,2,5]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(845, LongestMountainInArray, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 1, 4, 7, 3, 2, 5};
  int         expect   = 5;
  int         actual   = solution->longestMountain(arr);
  LCD_EXPECT_EQ(expect, actual);
}
