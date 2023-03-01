// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Peak Element
//
// https://leetcode.com/problems/find-peak-element/
//
// Question ID: 162
// Difficult  : Medium
// Solve Date : 2021/09/20 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |162. Find Peak Element|:
//
// A peak element is an element that is strictly greater than its neighbors.
// Given a 0-indexed integer array |nums|, find a peak element, and return its
// index. If the array contains multiple peaks, return the index to any of the
// peaks. You may imagine that |nums[-1] = nums[n] = -∞|. In other words, an
// element is always considered to be strictly greater than a neighbor that is
// outside the array. You must write an algorithm that runs in |O(log n)| time.
//  
//

LEETCODE_BEGIN_RESOLVING(162, FindPeakElement, Solution);

class Solution {
private:
  template <typename iterator>
  iterator solve(iterator beg, iterator end) {
    auto len = distance(beg, end) - 1;

    if (len == 0) {

      return beg;
    } else {
      auto mid = beg + len / 2;

      return *mid > *(mid + 1) ? solve(beg, mid + 1) : solve(mid + 1, end);
    }
  }

public:
  int findPeakElement(vector<int> &nums) {
    return distance(nums.begin(), solve(nums.begin(), nums.end()));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * |nums[i] != nums[i + 1]| for all valid |i|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1]
// Output: 2
//
// 3 is a peak element and your function should return the index number 2.

LEETCODE_SOLUTION_UNITTEST(162, FindPeakElement, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1};
  int         expect   = 2;
  int         actual   = solution->findPeakElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,1,3,5,6,4]
// Output: 5
//
// Your function can return either index number 1 where the peak element is 2,
// or index number 5 where the peak element is 6.

LEETCODE_SOLUTION_UNITTEST(162, FindPeakElement, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 3, 5, 6, 4};
  int         expect   = 5;
  int         actual   = solution->findPeakElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}
