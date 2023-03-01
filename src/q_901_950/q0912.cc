// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort an Array
//
// https://leetcode.com/problems/sort-an-array/
//
// Question ID: 912
// Difficult  : Medium
// Solve Date : 2022/04/05 18:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |912. Sort an Array|:
//
// Given an array of integers |nums|, sort the array in ascending order and
// return it. You must solve the problem without using any built-in functions in
// |O(nlog(n))| time complexity and with the smallest space complexity possible.
//  
//

LEETCODE_BEGIN_RESOLVING(912, SortAnArray, Solution);

class Solution {
private:
  inline void combine(vector<int> &arr, int l, int r) {
    vector<int> tmp(arr.begin() + l, arr.begin() + r);
    int         m = (r - l) / 2;
    int         i = 0, j = m, idx = l;
    while (i != m && j != tmp.size()) {
      if (tmp[i] < tmp[j]) {
        arr[idx++] = tmp[i++];
      } else {
        arr[idx++] = tmp[j++];
      }
    }
    while (i != m) {
      arr[idx++] = tmp[i++];
    }
    while (j != tmp.size()) {
      arr[idx++] = tmp[j++];
    }
  }

  inline void merge_sort(vector<int> &arr, int l, int r) {
    if (l >= r - 1) {
      return;
    }
    int m = l + (r - l) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m, r);
    combine(arr, l, r);
  }

public:
  vector<int> sortArray(vector<int> &nums) {
    merge_sort(nums, 0, nums.size());
    return nums;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁴|
// * |-5 * 10⁴ <= nums[i] <= 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,2,3,1]
// Output: [1,2,3,5]
//
// After sorting the array, the positions of some numbers are not changed (for
// example, 2 and 3), while the positions of other numbers are changed (for
// example, 1 and 5).

LEETCODE_SOLUTION_UNITTEST(912, SortAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 3, 1};
  vector<int> expect   = {1, 2, 3, 5};
  vector<int> actual   = solution->sortArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,1,1,2,0,0]
// Output: [0,0,1,1,2,5]
//
// Note that the values of nums are not necessairly unique.

LEETCODE_SOLUTION_UNITTEST(912, SortAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 1, 1, 2, 0, 0};
  vector<int> expect   = {0, 0, 1, 1, 2, 5};
  vector<int> actual   = solution->sortArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
