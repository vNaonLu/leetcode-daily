// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Element Appearing More Than 25% In Sorted Array
//
// https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/
//
// Question ID: 1287
// Difficult  : Easy
// Solve Date : 2022/11/27 16:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1287. Element Appearing More Than 25% In Sorted Array|:
//
// Given an integer array sorted in non-decreasing order, there is exactly one
// integer in the array that occurs more than 25% of the time, return that
// integer.
//

LEETCODE_BEGIN_RESOLVING(1287, ElementAppearingMoreThan25InSortedArray,
                         Solution);

class Solution {
public:
  int findSpecialInteger(vector<int> &arr) {
    auto n    = arr.size();
    auto cand = vector<int>{arr[n / 4], arr[n / 2], arr[(n * 3) / 4]};
    for (auto x : cand) {
      auto beg = lower_bound(arr.begin(), arr.end(), x);
      auto end = upper_bound(arr.begin(), arr.end(), x);
      if (4 * distance(beg, end) > n) {
        return x;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |0 <= arr[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,2,6,6,6,6,7,10]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1287, ElementAppearingMoreThan25InSortedArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 2, 6, 6, 6, 6, 7, 10};
  int         expect   = 6;
  int         actual   = solution->findSpecialInteger(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1287, ElementAppearingMoreThan25InSortedArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1};
  int         expect   = 1;
  int         actual   = solution->findSpecialInteger(arr);
  LCD_EXPECT_EQ(expect, actual);
}
