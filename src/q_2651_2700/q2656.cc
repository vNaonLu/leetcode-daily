// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Sum With Exactly K Elements
//
// https://leetcode.com/problems/maximum-sum-with-exactly-k-elements/
//
// Question ID: 2656
// Difficult  : Easy
// Solve Date : 2023/05/11 18:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2656. Maximum Sum With Exactly K Elements |:
//
// You are given a 0-indexed integer array |nums| and an integer |k|. Your task
// is to perform the following operation exactly |k| times in order to maximize
// your score:
//
//  1. Select an element |m| from |nums|.
//
//  2. Remove the selected element |m| from the array.
//
//  3. Add a new element with a value of |m + 1| to the array.
//
//  4. Increase your score by |m|.
// Return the maximum score you can achieve after performing the operation
// exactly |k| times.
//
//

LEETCODE_BEGIN_RESOLVING(2656, MaximumSumWithExactlyKElements, Solution);

class Solution {
public:
  int maximizeSum(vector<int> &nums, int k) {
    auto mx = *max_element(nums.begin(), nums.end());
    return (k * (mx + mx + k - 1)) / 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
// * |1 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5], k = 3
// Output: 18
//
// We need to choose exactly 3 elements from nums to maximize the sum.
// For the first iteration, we choose 5. Then sum is 5 and nums = [1,2,3,4,6]
// For the second iteration, we choose 6. Then sum is 5 + 6 and nums =
// [1,2,3,4,7] For the third iteration, we choose 7. Then sum is 5 + 6 + 7 = 18
// and nums = [1,2,3,4,8] So, we will return 18. It can be proven, that 18 is
// the maximum answer that we can achieve.

LEETCODE_SOLUTION_UNITTEST(2656, MaximumSumWithExactlyKElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         k        = 3;
  int         expect   = 18;
  int         actual   = solution->maximizeSum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,5,5], k = 2
// Output: 11
//
// We need to choose exactly 2 elements from nums to maximize the sum.
// For the first iteration, we choose 5. Then sum is 5 and nums = [5,5,6]
// For the second iteration, we choose 6. Then sum is 5 + 6 = 11 and nums =
// [5,5,7] So, we will return 11. It can be proven, that 11 is the maximum
// answer that we can achieve.

LEETCODE_SOLUTION_UNITTEST(2656, MaximumSumWithExactlyKElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 5};
  int         k        = 2;
  int         expect   = 11;
  int         actual   = solution->maximizeSum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
