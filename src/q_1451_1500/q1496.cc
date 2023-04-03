// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path Crossing
//
// https://leetcode.com/problems/path-crossing/
//
// Question ID: 1496
// Difficult  : Easy
// Solve Date : 2023/03/28 19:17

#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1496. Path Crossing|:
//
// Given a string |path|, where |path[i] = 'N'|, |'S'|, |'E'| or |'W'|, each
// representing moving one unit north, south, east, or west, respectively. You
// start at the origin |(0, 0)| on a 2D plane and walk on the path specified by
// |path|. Return |true| if the path crosses itself at any point, that is, if at
// any time you are on a location you have previously visited. Return |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1496, PathCrossing, Solution);

class Solution {
public:
  bool isPathCrossing(string path) {
    int                 x = 0;
    int                 y = 0;
    set<pair<int, int>> memo;
    memo.emplace(0, 0);
    for (auto c : path) {
      switch (c) {
      case 'N': {
        ++y;
      } break;
      case 'S': {
        --y;
      } break;
      case 'E': {
        ++x;
      } break;
      case 'W': {
        --x;
      } break;
      }
      if (!memo.emplace(x, y).second) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= path.length <= 10⁴|
// * |path[i]| is either |'N'|, |'S'|, |'E'|, or |'W'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: path = "NES"
// Output: false
//
// Notice that the path doesn't cross any point more than once.

LEETCODE_SOLUTION_UNITTEST(1496, PathCrossing, example_1) {
  auto   solution = MakeSolution();
  string path     = "NES";
  bool   expect   = false;
  bool   actual   = solution->isPathCrossing(path);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: path = "NESWW"
// Output: true
//
// Notice that the path visits the origin twice.

LEETCODE_SOLUTION_UNITTEST(1496, PathCrossing, example_2) {
  auto   solution = MakeSolution();
  string path     = "NESWW";
  bool   expect   = true;
  bool   actual   = solution->isPathCrossing(path);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "NNSWWEWSSESSWENNW"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1496, PathCrossing, extra_testcase_1) {
  auto   solution = MakeSolution();
  string path     = "NNSWWEWSSESSWENNW";
  bool   expect   = true;
  bool   actual   = solution->isPathCrossing(path);
  LCD_EXPECT_EQ(expect, actual);
}
