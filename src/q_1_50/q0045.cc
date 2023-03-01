// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jump Game II
//
// https://leetcode.com/problems/jump-game-ii/
//
// Question ID: 45
// Difficult  : Medium
// Solve Date : 2021/10/01 11:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |45. Jump Game II|:
//
// You are given a 0-indexed array of integers |nums| of length |n|. You are
// initially positioned at |nums[0]|. Each element |nums[i]| represents the
// maximum length of a forward jump from index |i|. In other words, if you are
// at |nums[i]|, you can jump to any |nums[i + j]| where:
//
//  • |0 <= j <= nums[i]| and
//
//  • |i + j < n|
// Return the minimum number of jumps to reach |nums[n - 1]|. The test cases are
// generated such that you can reach |nums[n - 1]|.  
//

LEETCODE_BEGIN_RESOLVING(45, JumpGameII, Solution);

class Solution {
public:
  int jump(vector<int> &nums) {
    int res     = 0;
    int cur_max = 0, last = 0;
    for (int i = 0; i < nums.size() && last < nums.size() - 1; ++i) {
      cur_max = max(cur_max, i + nums[i]);
      if (i == last) {
        ++res;
        last = cur_max;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |0 <= nums[i] <= 1000|
// * It's guaranteed that you can reach |nums[n - 1]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,1,1,4]
// Output: 2
//
// The minimum number of jumps to reach the last index is 2. Jump 1 step from
// index 0 to 1, then 3 steps to the last index.

LEETCODE_SOLUTION_UNITTEST(45, JumpGameII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1, 1, 4};
  int         expect   = 2;
  int         actual   = solution->jump(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,0,1,4]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(45, JumpGameII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 0, 1, 4};
  int         expect   = 2;
  int         actual   = solution->jump(nums);
  LCD_EXPECT_EQ(expect, actual);
}
