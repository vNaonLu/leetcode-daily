// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make Binary Array Elements Equal to One I
//
// https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/
//
// Question ID: 3191
// Difficult  : Medium
// Solve Date : 2025/03/19 19:15

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3191. Minimum Operations to Make Binary Array Elements Equal
// to One I|:
//
// You are given a binary array |nums|.
// You can do the following operation on the array any number of times (possibly
// zero):
//
//  • Choose any 3 consecutive elements from the array and flip all of them.
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
// Return the minimum number of operations required to make all elements in
// |nums| equal to 1. If it is impossible, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3191,
                         MinimumOperationsToMakeBinaryArrayElementsEqualToOneI,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < nums.size() - 2; ++i) {
      if (nums[i] == 1) {
        continue;
      }

      ++res;
      nums[i]     = !nums[i];
      nums[i + 1] = !nums[i + 1];
      nums[i + 2] = !nums[i + 2];
    }

    if (nums.back() == 0 || nums[nums.size() - 2] == 0) {
      return -1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,1,1,0,0]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    3191, MinimumOperationsToMakeBinaryArrayElementsEqualToOneI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 1, 1, 0, 0};
  int         expect   = 3;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,1,1]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(
    3191, MinimumOperationsToMakeBinaryArrayElementsEqualToOneI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 1, 1};
  int         expect   = -1;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
