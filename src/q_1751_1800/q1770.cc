// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Score from Performing Multiplication Operations
//
// https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/
//
// Question ID: 1770
// Difficult  : Hard
// Solve Date : 2022/09/16 17:52

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1770. Maximum Score from Performing Multiplication
// Operations|:
//
// You are given two 0-indexed integer arrays |nums| and |multipliers| of size
// |n| and |m| respectively, where |n >= m|. You begin with a score of |0|. You
// want to perform exactly |m| operations. On the |iᵗʰ| operation (0-indexed)
// you will:
//
//  • Choose one integer |x| from either the start or the end of the array
//  |nums|.
//
//  • Add |multipliers[i] * x| to your score.
//
//
//    • Note that |multipliers[0]| corresponds to the first operation,
//    |multipliers[1]| to the second operation, and so on.
//
//
//
//  • Remove |x| from |nums|.
// Return the maximum score after performing |m| operations.
//

LEETCODE_BEGIN_RESOLVING(1770,
                         MaximumScoreFromPerformingMultiplicationOperations,
                         Solution);

class Solution {
public:
  int maximumScore(vector<int> &nums, vector<int> &multipliers) {
    auto n  = nums.size();
    auto m  = multipliers.size();
    auto dp = vector<int>(m + 1);

    for (int i = m - 1; i >= 0; --i) {
      auto next = dp;
      for (int j = i; j >= 0; --j) {
        dp[j] = max(multipliers[i] * nums[j] + next[j + 1],
                    multipliers[i] * nums[n - 1 - (i - j)] + next[j]);
      }
    }

    return dp.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |m == multipliers.length|
// * |1 <= m <= 300|
// * |m <= n <= 10⁵| | |
// * |-1000 <= nums[i], multipliers[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3], multipliers = [3,2,1]
// Output: 14
//
// An optimal solution is as follows:
// - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
// - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
// - Choose from the end, [1], adding 1 * 1 = 1 to the score.
// The total score is 9 + 4 + 1 = 14.

LEETCODE_SOLUTION_UNITTEST(1770,
                           MaximumScoreFromPerformingMultiplicationOperations,
                           example_1) {
  auto        solution    = MakeSolution();
  vector<int> nums        = {1, 2, 3};
  vector<int> multipliers = {3, 2, 1};
  int         expect      = 14;
  int         actual      = solution->maximumScore(nums, multipliers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
// Output: 102
//
// An optimal solution is as follows:
// - Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the
// score.
// - Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
// - Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
// - Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
// - Choose from the end, [-2,7], adding 7 * 6 = 42 to the score.
// The total score is 50 + 15 - 9 + 4 + 42 = 102.

LEETCODE_SOLUTION_UNITTEST(1770,
                           MaximumScoreFromPerformingMultiplicationOperations,
                           example_2) {
  auto        solution    = MakeSolution();
  vector<int> nums        = {-5, -3, -3, -2, 7, 1};
  vector<int> multipliers = {-10, -5, 3, 4, 6};
  int         expect      = 102;
  int         actual      = solution->maximumScore(nums, multipliers);
  LCD_EXPECT_EQ(expect, actual);
}
