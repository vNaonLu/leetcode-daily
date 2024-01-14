// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Furthest Point From Origin
//
// https://leetcode.com/problems/furthest-point-from-origin/
//
// Question ID: 2833
// Difficult  : Easy
// Solve Date : 2024/01/14 12:35

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2833. Furthest Point From Origin|:
//
// You are given a string |moves| of length |n| consisting only of characters
// |'L'|, |'R'|, and |'_'|. The string represents your movement on a number line
// starting from the origin |0|. In the |iᵗʰ| move, you can choose one of the
// following directions:
//
//  • move to the left if |moves[i] = 'L'| or |moves[i] = '_'|
//
//  • move to the right if |moves[i] = 'R'| or |moves[i] = '_'|
// Return the distance from the origin of the furthest point you can get to
// after |n| moves.
//
//

LEETCODE_BEGIN_RESOLVING(2833, FurthestPointFromOrigin, Solution);

class Solution {
public:
  int furthestDistanceFromOrigin(string moves) {
    int cnt1 = 0;
    int cnt0 = 0;
    for (auto x : moves) {
      if (x == 'L') {
        --cnt1;
        --cnt0;
      } else if (x == '_') {
        --cnt0;
        ++cnt1;
      } else if (x == 'R') {
        ++cnt0;
        ++cnt1;
      }
    }
    return max(abs(cnt1), abs(cnt0));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= moves.length == n <= 50|
// * |moves| consists only of characters |'L'|, |'R'| and |'_'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: moves = "L_RL__R"
// Output: 3
//
// The furthest point we can reach from the origin 0 is point -3 through the
// following sequence of moves "LLRLLLR".

LEETCODE_SOLUTION_UNITTEST(2833, FurthestPointFromOrigin, example_1) {
  auto   solution = MakeSolution();
  string moves    = "L_RL__R";
  int    expect   = 3;
  int    actual   = solution->furthestDistanceFromOrigin(moves);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: moves = "_R__LL_"
// Output: 5
//
// The furthest point we can reach from the origin 0 is point -5 through the
// following sequence of moves "LRLLLLL".

LEETCODE_SOLUTION_UNITTEST(2833, FurthestPointFromOrigin, example_2) {
  auto   solution = MakeSolution();
  string moves    = "_R__LL_";
  int    expect   = 5;
  int    actual   = solution->furthestDistanceFromOrigin(moves);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: moves = "_______"
// Output: 7
//
// The furthest point we can reach from the origin 0 is point 7 through the
// following sequence of moves "RRRRRRR".

LEETCODE_SOLUTION_UNITTEST(2833, FurthestPointFromOrigin, example_3) {
  auto   solution = MakeSolution();
  string moves    = "_______";
  int    expect   = 7;
  int    actual   = solution->furthestDistanceFromOrigin(moves);
  LCD_EXPECT_EQ(expect, actual);
}
