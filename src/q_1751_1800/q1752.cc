// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Array Is Sorted and Rotated
//
// https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/
//
// Question ID: 1752
// Difficult  : Easy
// Solve Date : 2022/02/06 14:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1752. Check if Array Is Sorted and Rotated|:
//
// Given an array |nums|, return |true| if the array was originally sorted in
// non-decreasing order, then rotated some number of positions (including zero).
// Otherwise, return |false|. There may be duplicates in the original array.
// Note: An array |A| rotated by |x| positions results in an array |B| of the
// same length such that |A[i] == B[(i+x) % A.length]|, where |%| is the modulo
// operation.  
//

LEETCODE_BEGIN_RESOLVING(1752, CheckIfArrayIsSortedAndRotated, Solution);

class Solution {
public:
  bool check(vector<int> &nums) {
    int min_idx = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] < nums[min_idx])
        min_idx = i;
      else if (nums[i] == nums[min_idx] && nums[i] < nums[i - 1])
        min_idx = i;
    }
    int n    = nums.size();
    int curr = (min_idx + 1) % n, last = min_idx;
    while (curr != min_idx) {
      if (nums[curr] < nums[last])
        return false;
      ++curr;
      ++last;
      if (curr >= n)
        curr %= n;
      if (last >= n)
        last %= n;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,5,1,2]
// Output: true
//
// [1,2,3,4,5] is the original sorted array.
// You can rotate the array by x = 3 positions to begin on the the element of
// value 3: [3,4,5,1,2].

LEETCODE_SOLUTION_UNITTEST(1752, CheckIfArrayIsSortedAndRotated, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 1, 2};
  bool        expect   = true;
  bool        actual   = solution->check(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,3,4]
// Output: false
//
// There is no sorted array once rotated that can make nums.

LEETCODE_SOLUTION_UNITTEST(1752, CheckIfArrayIsSortedAndRotated, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3, 4};
  bool        expect   = false;
  bool        actual   = solution->check(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3]
// Output: true
//
// [1,2,3] is the original sorted array.
// You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.

LEETCODE_SOLUTION_UNITTEST(1752, CheckIfArrayIsSortedAndRotated, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  bool        expect   = true;
  bool        actual   = solution->check(nums);
  LCD_EXPECT_EQ(expect, actual);
}
