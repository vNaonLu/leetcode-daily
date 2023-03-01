// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Subarray to be Removed to Make Array Sorted
//
// https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
//
// Question ID: 1574
// Difficult  : Medium
// Solve Date : 2022/07/27 18:21

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1574. Shortest Subarray to be Removed to Make Array Sorted|:
//
// Given an integer array |arr|, remove a subarray (can be empty) from |arr|
// such that the remaining elements in |arr| are non-decreasing. Return the
// length of the shortest subarray to remove. A subarray is a contiguous
// subsequence of the array.
//

LEETCODE_BEGIN_RESOLVING(1574, ShortestSubarrayToBeRemovedToMakeArraySorted,
                         Solution);

class Solution {
public:
  int findLengthOfShortestSubarray(vector<int> &arr) {
    int n  = arr.size();
    int lo = 0, hi = n - 1;
    while (hi > 0 && arr[hi - 1] <= arr[hi]) {
      --hi;
    }

    int res = hi;
    while (lo < hi && (lo == 0 || arr[lo - 1] <= arr[lo])) {
      while (hi < n && arr[hi] < arr[lo]) {
        ++hi;
      }

      res = min(res, hi - lo - 1);
      ++lo;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁵|
// * |0 <= arr[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,10,4,2,3,5]
// Output: 3
//
// The shortest subarray we can remove is [10,4,2] of length 3. The remaining
// elements after that will be [1,2,3,3,5] which are sorted. Another correct
// solution is to remove the subarray [3,10,4].

LEETCODE_SOLUTION_UNITTEST(1574, ShortestSubarrayToBeRemovedToMakeArraySorted,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 10, 4, 2, 3, 5};
  int         expect   = 3;
  int         actual   = solution->findLengthOfShortestSubarray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [5,4,3,2,1]
// Output: 4
//
// Since the array is strictly decreasing, we can only keep a single element.
// Therefore we need to remove a subarray of length 4, either [5,4,3,2] or
// [4,3,2,1].

LEETCODE_SOLUTION_UNITTEST(1574, ShortestSubarrayToBeRemovedToMakeArraySorted,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {5, 4, 3, 2, 1};
  int         expect   = 4;
  int         actual   = solution->findLengthOfShortestSubarray(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,2,3]
// Output: 0
//
// The array is already non-decreasing. We do not need to remove any elements.

LEETCODE_SOLUTION_UNITTEST(1574, ShortestSubarrayToBeRemovedToMakeArraySorted,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3};
  int         expect   = 0;
  int         actual   = solution->findLengthOfShortestSubarray(arr);
  LCD_EXPECT_EQ(expect, actual);
}
