// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Moves to Equal Array Elements
//
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
//
// Question ID: 453
// Difficult  : Medium
// Solve Date : 2024/04/04 15:32

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |453. Minimum Moves to Equal Array Elements|:
//
// Given an integer array |nums| of size |n|, return the minimum number of moves
// required to make all array elements equal. In one move, you can increment |n
// - 1| elements of the array by |1|.
//
//

LEETCODE_BEGIN_RESOLVING(453, MinimumMovesToEqualArrayElements, Solution);

class Solution {
public:
  int minMoves(vector<int> &nums) {
    auto mn  = *min_element(nums.begin(), nums.end());
    auto sum = accumulate(nums.begin(), nums.end(), 0);
    return sum - (nums.size() * mn);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
// * The answer is guaranteed to fit in a 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(453, MinimumMovesToEqualArrayElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 3;
  int         actual   = solution->minMoves(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(453, MinimumMovesToEqualArrayElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->minMoves(nums);
  LCD_EXPECT_EQ(expect, actual);
}
