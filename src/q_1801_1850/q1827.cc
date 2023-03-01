// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make the Array Increasing
//
// https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/
//
// Question ID: 1827
// Difficult  : Easy
// Solve Date : 2022/06/04 21:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1827. Minimum Operations to Make the Array Increasing|:
//
// You are given an integer array |nums| (0-indexed). In one operation, you can
// choose an element of the array and increment it by |1|.
//
//
//
//  • For example, if |nums = [1,2,3]|, you can choose to increment |nums[1]| to
//  make |nums = [1,3,3]|.
//
//
// Return the minimum number of operations needed to make |nums| strictly
// increasing.
//
// An array |nums| is strictly increasing if |nums[i] < nums[i+1]| for all |0 <=
// i < nums.length - 1|. An array of length |1| is trivially strictly
// increasing.
//
//
//

LEETCODE_BEGIN_RESOLVING(1827, MinimumOperationsToMakeTheArrayIncreasing,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    int res  = 0;
    int curr = nums.front();

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] <= curr) {
        res += curr - nums[i] + 1;
        ++curr;
      } else {
        curr = nums[i];
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1]
// Output: 3
//
// You can do the following operations:
// 1) Increment nums[2], so nums becomes [1,1,2].
// 2) Increment nums[1], so nums becomes [1,2,2].
// 3) Increment nums[2], so nums becomes [1,2,3].

LEETCODE_SOLUTION_UNITTEST(1827, MinimumOperationsToMakeTheArrayIncreasing,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 3;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,2,4,1]
// Output: 14
//

LEETCODE_SOLUTION_UNITTEST(1827, MinimumOperationsToMakeTheArrayIncreasing,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 2, 4, 1};
  int         expect   = 14;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [8]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1827, MinimumOperationsToMakeTheArrayIncreasing,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8};
  int         expect   = 0;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
