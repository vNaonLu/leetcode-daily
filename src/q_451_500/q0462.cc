// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Moves to Equal Array Elements II
//
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
//
// Question ID: 462
// Difficult  : Medium
// Solve Date : 2022/06/30 12:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |462. Minimum Moves to Equal Array Elements II|:
//
// Given an integer array |nums| of size |n|, return the minimum number of moves
// required to make all array elements equal. In one move, you can increment or
// decrement an element of the array by |1|. Test cases are designed so that the
// answer will fit in a 32-bit integer.
//

LEETCODE_BEGIN_RESOLVING(462, MinimumMovesToEqualArrayElementsII, Solution);

class Solution {
public:
  int minMoves2(vector<int> &nums) {
    nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
    int m = nums[nums.size() / 2], res = 0;
    for (auto &x : nums) {
      res += abs(m - x);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: 2
//
// Only two moves are needed (remember each move increments or decrements one
// element): [1,2,3] => [2,2,3] => [2,2,2]

LEETCODE_SOLUTION_UNITTEST(462, MinimumMovesToEqualArrayElementsII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 2;
  int         actual   = solution->minMoves2(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,10,2,9]
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(462, MinimumMovesToEqualArrayElementsII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 10, 2, 9};
  int         expect   = 16;
  int         actual   = solution->minMoves2(nums);
  LCD_EXPECT_EQ(expect, actual);
}
