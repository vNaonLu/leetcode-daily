// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximize Area of Square Hole in Grid
//
// https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/
//
// Question ID: 2943
// Difficult  : Medium
// Solve Date : 2026/01/15 20:52

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2943. Maximize Area of Square Hole in Grid|:
//
// You are given the two integers, |n| and |m| and two integer arrays, |hBars|
// and |vBars|. The grid has |n + 2| horizontal and |m + 2| vertical bars,
// creating 1 x 1 unit cells. The bars are indexed starting from |1|. You can
// remove some of the bars in |hBars| from horizontal bars and some of the bars
// in |vBars| from vertical bars. Note that other bars are fixed and cannot be
// removed. Return an integer denoting the maximum area of a square-shaped hole
// in the grid, after removing some bars (possibly none).
//
//

LEETCODE_BEGIN_RESOLVING(2943, MaximizeAreaOfSquareHoleInGrid, Solution);

class Solution {
public:
  int maximizeSquareHoleArea(int n, int m, vector<int> &hBars,
                             vector<int> &vBars) {
    auto len = 1 + min(findLen(hBars), findLen(vBars));
    return len * len;
  }

private:
  int findLen(vector<int> &bars) {
    sort(bars.begin(), bars.end());
    int len = 1;
    int mx  = 1;
    for (int i = 0; i < bars.size() - 1; ++i) {
      len = 1 + (-(bars[i] + 1 == bars[i + 1]) & len);
      mx  = max(len, mx);
    }
    return mx;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
// * |1 <= m <= 10⁹|
// * |1 <= hBars.length <= 100|
// * |2 <= hBars[i] <= n + 1|
// * |1 <= vBars.length <= 100|
// * |2 <= vBars[i] <= m + 1|
// * All values in |hBars| are distinct.
// * All values in |vBars| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2943, MaximizeAreaOfSquareHoleInGrid, example_1) {
  auto        solution = MakeSolution();
  int         n        = 2;
  int         m        = 1;
  vector<int> hBars    = {2, 3};
  vector<int> vBars    = {2};
  int         expect   = 4;
  int         actual   = solution->maximizeSquareHoleArea(n, m, hBars, vBars);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, m = 1, hBars = [2], vBars = [2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2943, MaximizeAreaOfSquareHoleInGrid, example_2) {
  auto        solution = MakeSolution();
  int         n        = 1;
  int         m        = 1;
  vector<int> hBars    = {2};
  vector<int> vBars    = {2};
  int         expect   = 4;
  int         actual   = solution->maximizeSquareHoleArea(n, m, hBars, vBars);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2943, MaximizeAreaOfSquareHoleInGrid, example_3) {
  auto        solution = MakeSolution();
  int         n        = 2;
  int         m        = 3;
  vector<int> hBars    = {2, 3};
  vector<int> vBars    = {2, 4};
  int         expect   = 4;
  int         actual   = solution->maximizeSquareHoleArea(n, m, hBars, vBars);
  LCD_EXPECT_EQ(expect, actual);
}
