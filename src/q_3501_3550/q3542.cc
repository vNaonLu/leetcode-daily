// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Convert All Elements to Zero
//
// https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/
//
// Question ID: 3542
// Difficult  : Medium
// Solve Date : 2025/11/10 19:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3542. Minimum Operations to Convert All Elements to Zero|:
//
// You are given an array |nums| of size |n|, consisting of non-negative
// integers. Your task is to apply some (possibly zero) operations on the array
// so that all elements become 0. In one operation, you can select a subarray
// |[i, j]| (where |0 <= i <= j < n|) and set all occurrences of the minimum
// non-negative integer in that subarray to 0. Return the minimum number of
// operations required to make all elements in the array 0.
//
//

LEETCODE_BEGIN_RESOLVING(3542, MinimumOperationsToConvertAllElementsToZero,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    nums.push_back(0);
    std::vector<int> stack;
    int              count = 0;
    for (int i = 0; i < nums.size(); i++) {

      while (!stack.empty()) {
        if (nums[i] > stack.back()) {
          stack.push_back(nums[i]);
          break;
        } else if (nums[i] < stack.back()) {
          stack.pop_back();
          count++;
        } else {
          break;
        }
      }
      if (stack.empty() && nums[i] != 0) {
        stack.push_back(nums[i]);
      }
    }
    return count;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3542, MinimumOperationsToConvertAllElementsToZero,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 2};
  int         expect   = 1;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,2,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3542, MinimumOperationsToConvertAllElementsToZero,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 2, 1};
  int         expect   = 3;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,1,2,1,2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3542, MinimumOperationsToConvertAllElementsToZero,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2, 1, 2};
  int         expect   = 4;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
