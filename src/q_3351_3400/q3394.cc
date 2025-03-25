// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Check if Grid can be Cut into Sections
//
// https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/
//
// Question ID: 3394
// Difficult  : Medium
// Solve Date : 2025/03/25 21:15

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3394. Check if Grid can be Cut into Sections|:
//
// You are given an integer |n| representing the dimensions of an |n x n| grid,
// with the origin at the bottom-left corner of the grid. You are also given a
// 2D array of coordinates |rectangles|, where |rectangles[i]| is in the form
// |[startₓ, start_{y}, endₓ, end_{y}]|, representing a rectangle on the grid.
// Each rectangle is defined as follows:
//
//  • |(startₓ, start_{y})|: The bottom-left corner of the rectangle.
//
//  • |(endₓ, end_{y})|: The top-right corner of the rectangle.
// Note that the rectangles do not overlap. Your task is to determine if it is
// possible to make either two horizontal or two vertical cuts on the grid such
// that:
//
//  • Each of the three resulting sections formed by the cuts contains at least
//  one rectangle.
//
//  • Every rectangle belongs to exactly one section.
// Return |true| if such cuts can be made; otherwise, return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3394, CheckIfGridCanBeCutIntoSections, Solution);

class Solution {
public:
  bool checkValidCuts(int n, vector<vector<int>> &rectangles) {
    vector<vector<int>> xv;
    vector<vector<int>> yv;
    for (auto &v : rectangles) {
      xv.push_back({v[0], v[2]});
      yv.push_back({v[1], v[3]});
    }
    return helper(xv) || helper(yv);
  }

private:
  bool helper(auto &v) {
    sort(v.begin(), v.end());
    int res = 0;
    int mx  = v[0][1];
    for (auto &x : v) {
      int beg = x[0];
      int end = x[1];
      if (mx <= beg) {
        ++res;
      }
      mx = max(mx, end);
    }
    return res >= 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n <= 10⁹|
// * |3 <= rectangles.length <= 10⁵|
// * |0 <= rectangles[i][0] < rectangles[i][2] <= n|
// * |0 <= rectangles[i][1] < rectangles[i][3] <= n|
// * No two rectangles overlap.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3394, CheckIfGridCanBeCutIntoSections, example_1) {
  auto                solution   = MakeSolution();
  int                 n          = 5;
  vector<vector<int>> rectangles = {
      {1, 0, 5, 2},
      {0, 2, 2, 4},
      {3, 2, 5, 3},
      {0, 4, 4, 5}
  };
  bool expect = true;
  bool actual = solution->checkValidCuts(n, rectangles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3394, CheckIfGridCanBeCutIntoSections, example_2) {
  auto                solution   = MakeSolution();
  int                 n          = 4;
  vector<vector<int>> rectangles = {
      {0, 0, 1, 1},
      {2, 0, 3, 4},
      {0, 2, 2, 3},
      {3, 0, 4, 3}
  };
  bool expect = true;
  bool actual = solution->checkValidCuts(n, rectangles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4, rectangles =
//  [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3394, CheckIfGridCanBeCutIntoSections, example_3) {
  auto                solution   = MakeSolution();
  int                 n          = 4;
  vector<vector<int>> rectangles = {
      {0, 2, 2, 4},
      {1, 0, 3, 2},
      {2, 2, 3, 4},
      {3, 0, 4, 2},
      {3, 2, 4, 4}
  };
  bool expect = false;
  bool actual = solution->checkValidCuts(n, rectangles);
  LCD_EXPECT_EQ(expect, actual);
}
