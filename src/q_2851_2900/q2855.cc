// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Right Shifts to Sort the Array
//
// https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/
//
// Question ID: 2855
// Difficult  : Easy
// Solve Date : 2024/01/18 19:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2855. Minimum Right Shifts to Sort the Array|:
//
// You are given a 0-indexed array |nums| of length |n| containing distinct
// positive integers. Return the minimum number of right shifts required to sort
// |nums| and |-1| if this is not possible. A right shift is defined as shifting
// the element at index |i| to index |(i + 1) % n|, for all indices.
//
//

LEETCODE_BEGIN_RESOLVING(2855, MinimumRightShiftsToSortTheArray, Solution);

class Solution {
public:
  int minimumRightShifts(vector<int> &nums) {
    int n     = nums.size();
    int res   = -1;
    int count = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i - 1] > nums[i]) {
        res = i;
        ++count;
      }
    }
    if (res == -1) {
      return 0;
    }

    if (count > 1 || nums[0] < nums[n - 1]) {
      return -1;
    }
    return n - res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
// * |nums| contains distinct integers.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,5,1,2]
// Output: 2
//
// After the first right shift, nums = [2,3,4,5,1].
// After the second right shift, nums = [1,2,3,4,5].
// Now nums is sorted; therefore the answer is 2.

LEETCODE_SOLUTION_UNITTEST(2855, MinimumRightShiftsToSortTheArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 1, 2};
  int         expect   = 2;
  int         actual   = solution->minimumRightShifts(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3,5]
// Output: 0
//
// nums is already sorted therefore, the answer is 0.

LEETCODE_SOLUTION_UNITTEST(2855, MinimumRightShiftsToSortTheArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5};
  int         expect   = 0;
  int         actual   = solution->minimumRightShifts(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,1,4]
// Output: -1
//
// It's impossible to sort the array using right shifts.

LEETCODE_SOLUTION_UNITTEST(2855, MinimumRightShiftsToSortTheArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 4};
  int         expect   = -1;
  int         actual   = solution->minimumRightShifts(nums);
  LCD_EXPECT_EQ(expect, actual);
}
