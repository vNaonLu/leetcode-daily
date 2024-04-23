// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Target Sum
//
// https://leetcode.com/problems/target-sum/
//
// Question ID: 494
// Difficult  : Medium
// Solve Date : 2024/04/19 19:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |494. Target Sum|:
//
// You are given an integer array |nums| and an integer |target|.
// You want to build an expression out of nums by adding one of the symbols
// |'+'| and |'-'| before each integer in nums and then concatenate all the
// integers.
//
//  • For example, if |nums = [2, 1]|, you can add a |'+'| before |2| and a
//  |'-'| before |1| and concatenate them to build the expression |"+2-1"|.
// Return the number of different expressions that you can build, which
// evaluates to |target|.
//
//

LEETCODE_BEGIN_RESOLVING(494, TargetSum, Solution);

class Solution {
public:
  int findTargetSumWays(vector<int> &nums, int target) {
    int res = 0;
    int tmp = 0;
    helper(nums.begin(), nums.end(), target, &tmp, &res);
    return res;
  }

private:
  template <typename It>
  void helper(It beg, It end, int target, int *cur, int *res) {
    if (beg == end) {
      *res += target == *cur ? 1 : 0;
      return;
    }

    *cur -= *beg;
    helper(beg + 1, end, target, cur, res);
    *cur += *beg;
    *cur += *beg;
    helper(beg + 1, end, target, cur, res);
    *cur -= *beg;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 20|
// * |0 <= nums[i] <= 1000|
// * |0 <= sum(nums[i]) <= 1000|
// * |-1000 <= target <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1,1,1], target = 3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(494, TargetSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1};
  int         target   = 3;
  int         expect   = 5;
  int         actual   = solution->findTargetSumWays(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], target = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(494, TargetSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         target   = 1;
  int         expect   = 1;
  int         actual   = solution->findTargetSumWays(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}
