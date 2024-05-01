// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Freedom Trail
//
// https://leetcode.com/problems/freedom-trail/
//
// Question ID: 514
// Difficult  : Hard
// Solve Date : 2024/04/27 17:20

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |514. Freedom Trail|:
//
// In the video game Fallout 4, the quest "Road to Freedom" requires players to
// reach a metal dial called the "Freedom Trail Ring" and use the dial to spell
// a specific keyword to open the door. Given a string |ring| that represents
// the code engraved on the outer ring and another string |key| that represents
// the keyword that needs to be spelled, return the minimum number of steps to
// spell all the characters in the keyword. Initially, the first character of
// the ring is aligned at the |"12:00"| direction. You should spell all the
// characters in |key| one by one by rotating |ring| clockwise or anticlockwise
// to make each character of the string key aligned at the |"12:00"| direction
// and then by pressing the center button. At the stage of rotating the ring to
// spell the key character |key[i]|:
//
//  1. You can rotate the ring clockwise or anticlockwise by one place, which
//  counts as one step. The final purpose of the rotation is to align one of
//  |ring|'s characters at the |"12:00"| direction, where this character must
//  equal |key[i]|.
//
//  2. If the character |key[i]| has been aligned at the |"12:00"| direction,
//  press the center button to spell, which also counts as one step. After the
//  pressing, you could begin to spell the next character in the key (next
//  stage). Otherwise, you have finished all the spelling.
//
//

LEETCODE_BEGIN_RESOLVING(514, FreedomTrail, Solution);

class Solution {
public:
  int findRotateSteps(string ring, string key) {
    vector<vector<int>> pos(26);
    int                 r = ring.size();
    int                 k = key.size();

    for (int i = 0; i < r; ++i) {
      pos[ring[i] - 'a'].push_back(i);
    }

    vector<vector<int>> dp(200, vector<int>(200, numeric_limits<int>::max()));

    for (auto p : pos[key[0] - 'a']) {
      dp[0][p] = min(p, r - p) + 1;
    }

    for (int i = 1; i < k; ++i) {
      for (auto j : pos[key[i - 1] - 'a']) {
        for (auto p : pos[key[i] - 'a']) {
          int step = abs(p - j);
          step     = min(step, r - step);
          dp[i][p] = min(dp[i][p], dp[i - 1][j] + step + 1);
        }
      }
    }
    return *min_element(dp[k - 1].begin(), dp[k - 1].begin() + r);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= ring.length, key.length <= 100|
// * |ring| and |key| consist of only lower case English letters.
// * It is guaranteed that |key| could always be spelled by rotating |ring|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ring = "godding", key = "gd"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(514, FreedomTrail, example_1) {
  auto   solution = MakeSolution();
  string ring     = "godding";
  string key      = "gd";
  int    expect   = 4;
  int    actual   = solution->findRotateSteps(ring, key);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ring = "godding", key = "godding"
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(514, FreedomTrail, example_2) {
  auto   solution = MakeSolution();
  string ring     = "godding";
  string key      = "godding";
  int    expect   = 13;
  int    actual   = solution->findRotateSteps(ring, key);
  LCD_EXPECT_EQ(expect, actual);
}
