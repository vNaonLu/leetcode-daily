// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Turbulent Subarray
//
// https://leetcode.com/problems/longest-turbulent-subarray/
//
// Question ID: 978
// Difficult  : Medium
// Solve Date : 2021/09/15 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |978. Longest Turbulent Subarray|:
//
// Given an integer array |arr|, return the length of a maximum size turbulent
// subarray of |arr|. A subarray is turbulent if the comparison sign flips
// between each adjacent pair of elements in the subarray. More formally, a
// subarray |[arr[i], arr[i + 1], ..., arr[j]]| of |arr| is said to be turbulent
// if and only if:
//
//  • For |i <= k < j|:
//
//
//    • |arr[k] > arr[k + 1]| when |k| is odd, and
//
//    • |arr[k] < arr[k + 1]| when |k| is even.
//
//
//
//  • Or, for |i <= k < j|:
//
//
//    • |arr[k] > arr[k + 1]| when |k| is even, and
//
//    • |arr[k] < arr[k + 1]| when |k| is odd.
//
//
//  
//

LEETCODE_BEGIN_RESOLVING(978, LongestTurbulentSubarray, Solution);

class Solution {
public:
  int maxTurbulenceSize(vector<int> &arr) {
    if (arr.size() == 0)
      return 0;
    else if (arr.size() == 1)
      return 1;
    int       res = 0, cur = 0;
    long long diff = 0;
    for (int i = 1; i < arr.size(); ++i) {
      long long curd = arr[i] - arr[i - 1];
      if (diff * curd >= 0) {
        cur = curd == 0 ? 0 : 1;
      }
      diff = curd;
      res  = max(res, ++cur);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 4 * 10⁴|
// * |0 <= arr[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [9,4,2,10,7,8,8,1,9]
// Output: 5
//
// arr[1] > arr[2] < arr[3] > arr[4] < arr[5]

LEETCODE_SOLUTION_UNITTEST(978, LongestTurbulentSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {9, 4, 2, 10, 7, 8, 8, 1, 9};
  int         expect   = 5;
  int         actual   = solution->maxTurbulenceSize(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [4,8,12,16]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(978, LongestTurbulentSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 8, 12, 16};
  int         expect   = 2;
  int         actual   = solution->maxTurbulenceSize(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [100]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(978, LongestTurbulentSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {100};
  int         expect   = 1;
  int         actual   = solution->maxTurbulenceSize(arr);
  LCD_EXPECT_EQ(expect, actual);
}
