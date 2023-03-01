// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time to Make Rope Colorful
//
// https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
//
// Question ID: 1578
// Difficult  : Medium
// Solve Date : 2022/10/03 12:31

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1578. Minimum Time to Make Rope Colorful|:
//
// Alice has |n| balloons arranged on a rope. You are given a 0-indexed string
// |colors| where |colors[i]| is the color of the |iᵗʰ| balloon. Alice wants the
// rope to be colorful. She does not want two consecutive balloons to be of the
// same color, so she asks Bob for help. Bob can remove some balloons from the
// rope to make it colorful. You are given a 0-indexed integer array
// |neededTime| where |neededTime[i]| is the time (in seconds) that Bob needs to
// remove the |iᵗʰ| balloon from the rope. Return the minimum time Bob needs to
// make the rope colorful.
//

LEETCODE_BEGIN_RESOLVING(1578, MinimumTimeToMakeRopeColorful, Solution);

class Solution {
public:
  int minCost(string colors, vector<int> &neededTime) {
    auto res = (int)0;
    auto cur = (int)0;
    for (int i = 0; i < colors.size(); ++i) {
      if (i > 0 && colors[i] != colors[i - 1]) {
        cur = 0;
      }

      res += min(cur, neededTime[i]);
      cur = max(cur, neededTime[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == colors.length == neededTime.length|
// * |1 <= n <= 10⁵|
// * |1 <= neededTime[i] <= 10⁴|
// * |colors| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = "abaac", neededTime = [1,2,3,4,5]
// Output: 3
//
// In the above image, 'a' is blue, 'b' is red, and 'c' is green.
// Bob can remove the blue balloon at index 2. This takes 3 seconds.
// There are no longer two consecutive balloons of the same color. Total time
// = 3.

LEETCODE_SOLUTION_UNITTEST(1578, MinimumTimeToMakeRopeColorful, example_1) {
  auto        solution   = MakeSolution();
  string      colors     = "abaac";
  vector<int> neededTime = {1, 2, 3, 4, 5};
  int         expect     = 3;
  int         actual     = solution->minCost(colors, neededTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: colors = "abc", neededTime = [1,2,3]
// Output: 0
//
// The rope is already colorful. Bob does not need to remove any balloons from
// the rope.

LEETCODE_SOLUTION_UNITTEST(1578, MinimumTimeToMakeRopeColorful, example_2) {
  auto        solution   = MakeSolution();
  string      colors     = "abc";
  vector<int> neededTime = {1, 2, 3};
  int         expect     = 0;
  int         actual     = solution->minCost(colors, neededTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: colors = "aabaa", neededTime = [1,2,3,4,1]
// Output: 2
//
// Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second to
// remove. There are no longer two consecutive balloons of the same color. Total
// time = 1 + 1 = 2.

LEETCODE_SOLUTION_UNITTEST(1578, MinimumTimeToMakeRopeColorful, example_3) {
  auto        solution   = MakeSolution();
  string      colors     = "aabaa";
  vector<int> neededTime = {1, 2, 3, 4, 1};
  int         expect     = 2;
  int         actual     = solution->minCost(colors, neededTime);
  LCD_EXPECT_EQ(expect, actual);
}
