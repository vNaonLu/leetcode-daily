// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Trapping Rain Water
//
// https://leetcode.com/problems/trapping-rain-water/
//
// Question ID: 42
// Difficult  : Hard
// Solve Date : 2021/10/18 13:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |42. Trapping Rain Water|:
//
// Given |n| non-negative integers representing an elevation map where the width
// of each bar is |1|, compute how much water it can trap after raining.  
//

LEETCODE_BEGIN_RESOLVING(42, TrappingRainWater, Solution);

class Solution {
public:
  int trap(vector<int> &height) {
    vector<int> dp(height.size(), 0);
    int         res = 0;
    dp[0]           = height[0];
    for (int i = 1; i < height.size(); ++i)
      dp[i] = max(dp[i - 1], height[i]);
    *(dp.end() - 1) = min(dp.back(), height.back());
    for (int i = height.size() - 2; i >= 0; --i)
      dp[i] = min(dp[i], max(dp[i + 1], height[i]));
    for (int i = 0; i < dp.size(); ++i)
      res += max(0, dp[i] - height[i]);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == height.length|
// * |1 <= n <= 2 * 10⁴|
// * |0 <= height[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
//
// The above elevation map (black section) is represented by array
// [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
// are being trapped.

LEETCODE_SOLUTION_UNITTEST(42, TrappingRainWater, example_1) {
  auto        solution = MakeSolution();
  vector<int> height   = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int         expect   = 6;
  int         actual   = solution->trap(height);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: height = [4,2,0,3,2,5]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(42, TrappingRainWater, example_2) {
  auto        solution = MakeSolution();
  vector<int> height   = {4, 2, 0, 3, 2, 5};
  int         expect   = 9;
  int         actual   = solution->trap(height);
  LCD_EXPECT_EQ(expect, actual);
}
