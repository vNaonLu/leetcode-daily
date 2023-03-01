// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Jumps to Reach Home
//
// https://leetcode.com/problems/minimum-jumps-to-reach-home/
//
// Question ID: 1654
// Difficult  : Medium
// Solve Date : 2022/03/20 13:57

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1654. Minimum Jumps to Reach Home|:
//
// A certain bug's home is on the x-axis at position |x|. Help them get there
// from position |0|. The bug jumps according to the following rules:
//
//  • It can jump exactly |a| positions forward (to the right).
//
//  • It can jump exactly |b| positions backward (to the left).
//
//  • It cannot jump backward twice in a row.
//
//  • It cannot jump to any |forbidden| positions.
// The bug may jump forward beyond its home, but it cannot jump to positions
// numbered with negative integers. Given an array of integers |forbidden|,
// where |forbidden[i]| means that the bug cannot jump to the position
// |forbidden[i]|, and integers |a|, |b|, and |x|, return the minimum number of
// jumps needed for the bug to reach its home. If there is no possible sequence
// of jumps that lands the bug on position |x|, return |-1.|  
//

LEETCODE_BEGIN_RESOLVING(1654, MinimumJumpsToReachHome, Solution);

class Solution {
public:
  int minimumJumps(vector<int> &forbidden, int a, int b, int x) {
    unordered_set<int> forbid, fwvisit, bwvisit;
    for (auto &x : forbidden) {
      forbid.insert(x);
    }

    int                    res = 0;
    queue<pair<int, bool>> pos;
    pos.emplace(0, false);

    while (!pos.empty()) {
      auto temp = move(pos);

      while (!temp.empty()) {
        auto [curr, last_is_bw] = temp.front();
        temp.pop();

        if (curr == x)
          return res;

        if (!forbid.count(curr + a) && !fwvisit.count(curr + a) &&
            curr + a <= 10000) {
          fwvisit.insert(curr + a);
          pos.emplace(curr + a, false);
        }

        if (!last_is_bw && !forbid.count(curr - b) &&
            !bwvisit.count(curr - b) && curr - b > 0) {
          bwvisit.insert(curr - b);
          pos.emplace(curr - b, true);
        }
      }

      ++res;
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= forbidden.length <= 1000|
// * |1 <= a, b, forbidden[i] <= 2000|
// * |0 <= x <= 2000|
// * All the elements in |forbidden| are distinct.
// * Position |x| is not forbidden.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
//
// 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.

LEETCODE_SOLUTION_UNITTEST(1654, MinimumJumpsToReachHome, example_1) {
  auto        solution  = MakeSolution();
  vector<int> forbidden = {14, 4, 18, 1, 15};
  int         a         = 3;
  int         b         = 15;
  int         x         = 9;
  int         expect    = 3;
  int         actual    = solution->minimumJumps(forbidden, a, b, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1654, MinimumJumpsToReachHome, example_2) {
  auto        solution  = MakeSolution();
  vector<int> forbidden = {8, 3, 16, 6, 12, 20};
  int         a         = 15;
  int         b         = 13;
  int         x         = 11;
  int         expect    = -1;
  int         actual    = solution->minimumJumps(forbidden, a, b, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
// Output: 2
//
// One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug
// home.

LEETCODE_SOLUTION_UNITTEST(1654, MinimumJumpsToReachHome, example_3) {
  auto        solution  = MakeSolution();
  vector<int> forbidden = {1, 6, 2, 14, 5, 17, 4};
  int         a         = 16;
  int         b         = 9;
  int         x         = 7;
  int         expect    = 2;
  int         actual    = solution->minimumJumps(forbidden, a, b, x);
  LCD_EXPECT_EQ(expect, actual);
}
