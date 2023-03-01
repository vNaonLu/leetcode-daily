// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jump Game
//
// https://leetcode.com/problems/jump-game/
//
// Question ID: 55
// Difficult  : Medium
// Solve Date : 2021/09/30 13:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |55. Jump Game|:
//
// You are given an integer array |nums|. You are initially positioned at the
// array's first index, and each element in the array represents your maximum
// jump length at that position. Return |true| if you can reach the last index,
// or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(55, JumpGame, Solution);

class Solution {
public:
  bool canJump(vector<int> &nums) {
    int current_position = 0;
    for (int i = 0; i < nums.size() && current_position < nums.size(); ++i) {
      if (current_position < i)
        return false;
      current_position = max(current_position, nums[i] + i);
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,1,1,4]
// Output: true
//
// Jump 1 step from index 0 to 1, then 3 steps to the last index.

LEETCODE_SOLUTION_UNITTEST(55, JumpGame, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1, 1, 4};
  bool        expect   = true;
  bool        actual   = solution->canJump(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,1,0,4]
// Output: false
//
// You will always arrive at index 3 no matter what. Its maximum jump length is
// 0, which makes it impossible to reach the last index.

LEETCODE_SOLUTION_UNITTEST(55, JumpGame, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 0, 4};
  bool        expect   = false;
  bool        actual   = solution->canJump(nums);
  LCD_EXPECT_EQ(expect, actual);
}
