// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Minimum Operations to Make All Elements Divisible by Three
//
// https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/
//
// Question ID: 3190
// Difficult  : Easy
// Solve Date : 2024/06/26 21:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3190. Find Minimum Operations to Make All Elements Divisible
// by Three|:
//
// You are given an integer array |nums|. In one operation, you can add or
// subtract 1 from any element of |nums|. Return the minimum number of
// operations to make all elements of |nums| divisible by 3.
//
//

LEETCODE_BEGIN_RESOLVING(3190,
                         FindMinimumOperationsToMakeAllElementsDivisibleByThree,
                         Solution);

class Solution {
public:
  int minimumOperations(vector<int> &nums) {
    int res = 0;
    for (auto x : nums) {
      if (x % 3 != 0) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    3190, FindMinimumOperationsToMakeAllElementsDivisibleByThree, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 3;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,6,9]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    3190, FindMinimumOperationsToMakeAllElementsDivisibleByThree, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 6, 9};
  int         expect   = 0;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
