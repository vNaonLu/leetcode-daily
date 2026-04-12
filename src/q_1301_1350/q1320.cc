// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Distance to Type a Word Using Two Fingers
//
// https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/
//
// Question ID: 1320
// Difficult  : Hard
// Solve Date : 2026/04/12 16:35

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1320. Minimum Distance to Type a Word Using Two Fingers|:
//
// ![img](https://assets.leetcode.com/uploads/2020/01/02/leetcode_keyboard.png)
// You have a keyboard layout as shown above in the X-Y plane, where each
// English uppercase letter is located at some coordinate.
//
//  • For example, the letter |'A'| is located at coordinate |(0, 0)|, the
//  letter |'B'| is located at coordinate |(0, 1)|, the letter |'P'| is located
//  at coordinate |(2, 3)| and the letter |'Z'| is located at coordinate |(4,
//  1)|.
// Given the string |word|, return the minimum total distance to type such
// string using only two fingers. The distance between coordinates |(x₁, y₁)|
// and |(x₂, y₂)| is ||x₁ - x₂| + |y₁ - y₂||. Note that the initial positions of
// your two fingers are considered free so do not count towards your total
// distance, also your two fingers do not have to start at the first letter or
// the first two letters.
//
//

LEETCODE_BEGIN_RESOLVING(1320, MinimumDistanceToTypeAWordUsingTwoFingers,
                         Solution);

class Solution {
public:
  int cal(int a, int b) { return abs(a / 6 - b / 6) + abs(a % 6 - b % 6); }

  int minimumDistance(string s) {
    int n = s.size(), dp[300][26][26];

    for (int i = 0; i < n; i++) {
      int t = s[i] - 'A';
      for (int j = 0; j < 26; j++) {
        for (int k = 0; k < 26; k++) {
          dp[i + 1][j][k] = 1e6;
        }
      }
      for (int j = 0; j < 26; j++) {
        for (int k = 0; k < 26; k++) {
          dp[i + 1][j][t] = min(dp[i + 1][j][t], dp[i][j][k] + cal(k, t));
          dp[i + 1][t][k] = min(dp[i + 1][t][k], dp[i][j][k] + cal(j, t));
        }
      }
    }

    int ans = 1e6;
    for (int j = 0; j < 26; j++) {
      for (int k = 0; k < 26; k++) {
        ans = min(ans, dp[n][j][k]);
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= word.length <= 300|
// * |word| consists of uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "CAKE"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1320, MinimumDistanceToTypeAWordUsingTwoFingers,
                           example_1) {
  auto   solution = MakeSolution();
  string word     = "CAKE";
  int    expect   = 3;
  int    actual   = solution->minimumDistance(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "HAPPY"
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1320, MinimumDistanceToTypeAWordUsingTwoFingers,
                           example_2) {
  auto   solution = MakeSolution();
  string word     = "HAPPY";
  int    expect   = 6;
  int    actual   = solution->minimumDistance(word);
  LCD_EXPECT_EQ(expect, actual);
}
