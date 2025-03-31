// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Index of a Valid Split
//
// https://leetcode.com/problems/minimum-index-of-a-valid-split/
//
// Question ID: 2780
// Difficult  : Medium
// Solve Date : 2025/03/27 19:38

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2780. Minimum Index of a Valid Split|:
//
// An element |x| of an integer array |arr| of length |m| is dominant if more
// than half the elements of |arr| have a value of |x|. You are given a
// 0-indexed integer array |nums| of length |n| with one dominant element. You
// can split |nums| at an index |i| into two arrays |nums[0, ..., i]| and
// |nums[i + 1, ..., n - 1]|, but the split is only valid if:
//
//  • |0 <= i < n - 1|
//
//  • |nums[0, ..., i]|, and |nums[i + 1, ..., n - 1]| have the same dominant
//  element.
// Here, |nums[i, ..., j]| denotes the subarray of |nums| starting at index |i|
// and ending at index |j|, both ends being inclusive. Particularly, if |j < i|
// then |nums[i, ..., j]| denotes an empty subarray. Return the minimum index of
// a valid split. If no valid split exists, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2780, MinimumIndexOfAValidSplit, Solution);

class Solution {
public:
  int minimumIndex(vector<int> &nums) {
    auto find_dominant_element = [](const vector<int> &arr) {
      int candidate = -1, count = 0;

      // Boyer-Moore Majority Vote algorithm
      for (int num : arr) {
        if (count == 0) {
          candidate = num;
          count     = 1;
        } else if (num == candidate) {
          count++;
        } else {
          count--;
        }
      }

      count = count_if(arr.begin(), arr.end(),
                       [&](int num) { return num == candidate; });
      return (count > arr.size() / 2) ? candidate : -1;
    };

    int dominant = find_dominant_element(nums);
    if (dominant == -1)
      return -1;

    int left_count           = 0,
        total_dominant_count = count(nums.begin(), nums.end(), dominant);

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[i] == dominant) {
        left_count++;
      }

      int left_subarray_count  = left_count;
      int right_subarray_count = total_dominant_count - left_count;

      if (left_subarray_count > (i + 1) / 2 &&
          right_subarray_count > (nums.size() - i - 1) / 2) {
        return i;
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |nums| has exactly one dominant element.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2780, MinimumIndexOfAValidSplit, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 2};
  int         expect   = 2;
  int         actual   = solution->minimumIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,3,1,1,1,7,1,2,1]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2780, MinimumIndexOfAValidSplit, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3, 1, 1, 1, 7, 1, 2, 1};
  int         expect   = 4;
  int         actual   = solution->minimumIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,3,3,3,7,2,2]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2780, MinimumIndexOfAValidSplit, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 3, 3, 7, 2, 2};
  int         expect   = -1;
  int         actual   = solution->minimumIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}
