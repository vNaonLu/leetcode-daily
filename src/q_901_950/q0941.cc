// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Mountain Array
//
// https://leetcode.com/problems/valid-mountain-array/
//
// Question ID: 941
// Difficult  : Easy
// Solve Date : 2022/01/25 18:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |941. Valid Mountain Array|:
//
// Given an array of integers |arr|, return |true| if and only if it is a valid
// mountain array. Recall that arr is a mountain array if and only if:
//
//  • |arr.length >= 3|
//
//  • There exists some |i| with |0 < i < arr.length - 1| such that:
//
//
//    • |arr[0] < arr[1] < ... < arr[i - 1] < arr[i] |
//
//    • |arr[i] > arr[i + 1] > ... > arr[arr.length - 1]|
//
//
// ![img](https://assets.leetcode.com/uploads/2019/10/20/hint_valid_mountain_array.png)
//  
//

LEETCODE_BEGIN_RESOLVING(941, ValidMountainArray, Solution);

class Solution {
public:
  bool validMountainArray(vector<int> &arr) {
    if (arr.size() < 3)
      return false;
    auto prev = arr.begin(), curr = prev + 1;
    /// increasing
    while (curr != arr.end() && *curr > *prev) {
      ++prev, ++curr;
    }
    if (curr == arr.end() || prev == arr.begin())
      return false;
    /// decreasing
    while (curr != arr.end() && *curr < *prev) {
      ++prev, ++curr;
    }
    return curr == arr.end();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |0 <= arr[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(941, ValidMountainArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 1};
  bool        expect   = false;
  bool        actual   = solution->validMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [3,5,5]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(941, ValidMountainArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 5, 5};
  bool        expect   = false;
  bool        actual   = solution->validMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [0,3,2,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(941, ValidMountainArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 3, 2, 1};
  bool        expect   = true;
  bool        actual   = solution->validMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}
