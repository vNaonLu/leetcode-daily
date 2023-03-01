// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Peak Index in a Mountain Array
//
// https://leetcode.com/problems/peak-index-in-a-mountain-array/
//
// Question ID: 852
// Difficult  : Medium
// Solve Date : 2021/10/13 13:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |852. Peak Index in a Mountain Array|:
//
// An array |arr| a mountain if the following properties hold:
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
// Given a mountain array |arr|, return the index |i| such that |arr[0] < arr[1]
// < ... < arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]|. You
// must solve it in |O(log(arr.length))| time complexity.  
//

LEETCODE_BEGIN_RESOLVING(852, PeakIndexInAMountainArray, Solution);

class Solution {
public:
  int peakIndexInMountainArray(vector<int> &arr) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (mid > 0 && mid < arr.size() - 1) {
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
          return mid;
        } else if (arr[mid] < arr[mid + 1]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      } else if (mid == 0) {
        return arr[mid] > arr[mid] ? mid : mid + 1;
      } else {
        return arr[mid] > arr[mid - 1] ? mid : mid - 1;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= arr.length <= 10⁵|
// * |0 <= arr[i] <= 10⁶|
// * |arr| is guaranteed to be a mountain array.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [0,1,0]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(852, PeakIndexInAMountainArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 1, 0};
  int         expect   = 1;
  int         actual   = solution->peakIndexInMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [0,2,1,0]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(852, PeakIndexInAMountainArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 2, 1, 0};
  int         expect   = 1;
  int         actual   = solution->peakIndexInMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [0,10,5,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(852, PeakIndexInAMountainArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 10, 5, 2};
  int         expect   = 1;
  int         actual   = solution->peakIndexInMountainArray(arr);
  LCD_EXPECT_EQ(expect, actual);
}
