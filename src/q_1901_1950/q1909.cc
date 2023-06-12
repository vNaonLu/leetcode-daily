// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove One Element to Make the Array Strictly Increasing
//
// https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/
//
// Question ID: 1909
// Difficult  : Easy
// Solve Date : 2023/06/12 20:41

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1909. Remove One Element to Make the Array Strictly
// Increasing|:
//
// Given a 0-indexed integer array |nums|, return |true| if it can be made
// strictly increasing after removing exactly one element, or |false| otherwise.
// If the array is already strictly increasing, return |true|. The array |nums|
// is strictly increasing if |nums[i - 1] < nums[i]| for each index |(1 <= i <
// nums.length).|
//
//

LEETCODE_BEGIN_RESOLVING(1909, RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                         Solution);

class Solution {
public:
  bool canBeIncreasing(vector<int> &nums) {
    bool skipped = false;
    int  prev    = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] <= nums[prev]) {
        if (skipped) {
          return false;
        }
        skipped = true;
        if (i == 1 || nums[i] > nums[i - 2]) {
          prev = i;
        }
      } else {
        prev = i;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,10,5,7]
// Output: true
//
// By removing 10 at index 2 from nums, it becomes [1,2,5,7].
// [1,2,5,7] is strictly increasing, so return true.

LEETCODE_SOLUTION_UNITTEST(1909,
                           RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 10, 5, 7};
  bool        expect   = true;
  bool        actual   = solution->canBeIncreasing(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,1,2]
// Output: false
//
// [3,1,2] is the result of removing the element at index 0.
// [2,1,2] is the result of removing the element at index 1.
// [2,3,2] is the result of removing the element at index 2.
// [2,3,1] is the result of removing the element at index 3.
// No resulting array is strictly increasing, so return false.

LEETCODE_SOLUTION_UNITTEST(1909,
                           RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1, 2};
  bool        expect   = false;
  bool        actual   = solution->canBeIncreasing(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1]
// Output: false
//
// The result of removing any element is [1,1].
// [1,1] is not strictly increasing, so return false.

LEETCODE_SOLUTION_UNITTEST(1909,
                           RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  bool        expect   = false;
  bool        actual   = solution->canBeIncreasing(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1,2,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1909,
                           RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  bool        expect   = true;
  bool        actual   = solution->canBeIncreasing(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [105,924,32,968]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1909,
                           RemoveOneElementToMakeTheArrayStrictlyIncreasing,
                           extra_testcase_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {105, 924, 32, 968};
  bool        expect   = true;
  bool        actual   = solution->canBeIncreasing(nums);
  LCD_EXPECT_EQ(expect, actual);
}
