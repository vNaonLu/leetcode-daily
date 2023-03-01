// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Moves to Make Array Complementary
//
// https://leetcode.com/problems/minimum-moves-to-make-array-complementary/
//
// Question ID: 1674
// Difficult  : Medium
// Solve Date : 2022/02/22 18:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1674. Minimum Moves to Make Array Complementary|:
//
// You are given an integer array |nums| of even length |n| and an integer
// |limit|. In one move, you can replace any integer from |nums| with another
// integer between |1| and |limit|, inclusive. The array |nums| is complementary
// if for all indices |i| (0-indexed), |nums[i] + nums[n - 1 - i]| equals the
// same number. For example, the array |[1,2,3,4]| is complementary because for
// all indices |i|, |nums[i] + nums[n - 1 - i] = 5|. Return the minimum number
// of moves required to make |nums| complementary.  
//

LEETCODE_BEGIN_RESOLVING(1674, MinimumMovesToMakeArrayComplementary, Solution);

class Solution {
public:
  int minMoves(vector<int> &nums, int limit) {
    int         n = nums.size(), res = n;
    vector<int> moves(2 * limit + 2, 0);
    for (int i = 0; i < n / 2; ++i) {
      int mn = min(nums[i], nums[n - i - 1]),
          mx = max(nums[i], nums[n - i - 1]);
      ++moves[mn + 1];
      --moves[mx + limit + 1];

      --moves[mn + mx];
      ++moves[mn + mx + 1];

      moves[mx + limit + 1] += 2;
      moves[2 * limit + 1] -= 2;

      moves[2] += 2;
      moves[mn + 1] -= 2;
    }

    for (int i = 2; i <= limit * 2; ++i) {
      moves[i] += moves[i - 1];
      res = min(res, moves[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 10⁵|
// * |1 <= nums[i] <= limit <= 10⁵|
// * |n| is even.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,4,3], limit = 4
// Output: 1
//
// In 1 move, you can change nums to [1,2,2,3] (underlined elements are
// changed). nums[0] + nums[3] = 1 + 3 = 4. nums[1] + nums[2] = 2 + 2 = 4.
// nums[2] + nums[1] = 2 + 2 = 4.
// nums[3] + nums[0] = 3 + 1 = 4.
// Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.

LEETCODE_SOLUTION_UNITTEST(1674, MinimumMovesToMakeArrayComplementary,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 3};
  int         limit    = 4;
  int         expect   = 1;
  int         actual   = solution->minMoves(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2,1], limit = 2
// Output: 2
//
// In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to
// 3 since 3 > limit.

LEETCODE_SOLUTION_UNITTEST(1674, MinimumMovesToMakeArrayComplementary,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 1};
  int         limit    = 2;
  int         expect   = 2;
  int         actual   = solution->minMoves(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,1,2], limit = 2
// Output: 0
//
// nums is already complementary.

LEETCODE_SOLUTION_UNITTEST(1674, MinimumMovesToMakeArrayComplementary,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2};
  int         limit    = 2;
  int         expect   = 0;
  int         actual   = solution->minMoves(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}
