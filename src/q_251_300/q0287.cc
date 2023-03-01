// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Duplicate Number
//
// https://leetcode.com/problems/find-the-duplicate-number/
//
// Question ID: 287
// Difficult  : Medium
// Solve Date : 2022/03/29 18:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |287. Find the Duplicate Number|:
//
// Given an array of integers |nums| containing  |n + 1| integers where each
// integer is in the range |[1, n]| inclusive. There is only one repeated number
// in |nums|, return this repeated number. You must solve the problem without
// modifying the array |nums| and uses only constant extra space.  
//

LEETCODE_BEGIN_RESOLVING(287, FindTheDuplicateNumber, Solution);

class Solution {
public:
  int findDuplicate(vector<int> &nums) {
    int res = -1;
    for (auto &x : nums) {
      int idx = abs(x);
      if (nums[idx] < 0) {
        res = idx;
        break;
      }
      nums[idx] *= -1;
    }

    for (auto &x : nums) {
      x = abs(x);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |nums.length == n + 1|
// * |1 <= nums[i] <= n|
// * All the integers in |nums| appear only once except for precisely one
// integer which appears two or more times.
// * How can we prove that at least one duplicate number must exist in |nums|?
// * Can you solve the problem in linear runtime complexity?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,4,2,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(287, FindTheDuplicateNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 4, 2, 2};
  int         expect   = 2;
  int         actual   = solution->findDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,3,4,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(287, FindTheDuplicateNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 3, 4, 2};
  int         expect   = 3;
  int         actual   = solution->findDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}
