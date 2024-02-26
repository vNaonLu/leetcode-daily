// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Area of Longest Diagonal Rectangle
//
// https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/
//
// Question ID: 3000
// Difficult  : Easy
// Solve Date : 2024/02/20 19:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3000. Maximum Area of Longest Diagonal Rectangle|:
//
// You are given a 2D 0-indexed integer array |dimensions|.
// For all indices |i|, |0 <= i < dimensions.length|, |dimensions[i][0]|
// represents the length and |dimensions[i][1]| represents the width of the
// rectangle |i|. Return the area of the rectangle having the longest diagonal.
// If there are multiple rectangles with the longest diagonal, return the area
// of the rectangle having the maximum area.
//
//

LEETCODE_BEGIN_RESOLVING(3000, MaximumAreaOfLongestDiagonalRectangle, Solution);

class Solution {
public:
  int areaOfMaxDiagonal(vector<vector<int>> &dimensions) {
    int res = 0;
    int dig = 0;
    for (auto &v : dimensions) {
      int cur = v[0] * v[0] + v[1] * v[1];
      if (dig <= cur) {
        res = dig == cur ? max(res, v[0] * v[1]) : (v[0] * v[1]);
        dig = cur;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= dimensions.length <= 100|
// * |dimensions[i].length == 2|
// * |1 <= dimensions[i][0], dimensions[i][1] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dimensions = [[9,3],[8,6]]
// Output: 48
//
// For index = 0, length = 9 and width = 3. Diagonal length = sqrt(9 * 9 + 3 *
// 3) = sqrt(90) ≈ 9.487. For index = 1, length = 8 and width = 6. Diagonal
// length = sqrt(8 * 8 + 6 * 6) = sqrt(100) = 10. So, the rectangle at index 1
// has a greater diagonal length therefore we return area = 8 * 6 = 48.

LEETCODE_SOLUTION_UNITTEST(3000, MaximumAreaOfLongestDiagonalRectangle,
                           example_1) {
  auto                solution   = MakeSolution();
  vector<vector<int>> dimensions = {
      {9, 3},
      {8, 6}
  };
  int expect = 48;
  int actual = solution->areaOfMaxDiagonal(dimensions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dimensions = [[3,4],[4,3]]
// Output: 12
//
// Length of diagonal is the same for both which is 5, so maximum area = 12.

LEETCODE_SOLUTION_UNITTEST(3000, MaximumAreaOfLongestDiagonalRectangle,
                           example_2) {
  auto                solution   = MakeSolution();
  vector<vector<int>> dimensions = {
      {3, 4},
      {4, 3}
  };
  int expect = 12;
  int actual = solution->areaOfMaxDiagonal(dimensions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  [[4,7],[8,9],[5,3],[6,10],[2,9],[3,10],[2,2],[5,8],[5,10],[5,6],[8,9],[10,7],[8,9],[3,7],[2,6],[5,1],[7,4],[1,10],[1,7],[6,9],[3,3],[4,6],[8,2],[10,6],[7,9],[9,2],[1,2],[3,8],[10,2],[4,1],[9,7],[10,3],[6,9],[9,8],[7,7],[5,7],[5,4],[6,5],[1,8],[2,3],[7,10],[3,9],[5,7],[2,4],[5,6],[9,5],[8,8],[8,10],[6,8],[5,1],[10,8],[7,4],[2,1],[2,7],[10,3],[2,5],[7,6],[10,5],[10,9],[5,7],[10,6],[4,3],[10,4],[1,5],[8,9],[3,1],[2,5],[9,10],[6,6],[5,10],[10,2],[6,10],[1,1],[8,6],[1,7],[6,3],[9,3],[1,4],[1,1],[10,4],[7,9],[4,5],[2,8],[7,9],[7,3],[4,9],[2,8],[4,6],[9,1],[8,4],[2,4],[7,8],[3,5],[7,6],[8,6],[4,7],[25,60],[39,52],[16,63],[33,56]]
// Output: 2028
//

LEETCODE_SOLUTION_UNITTEST(3000, MaximumAreaOfLongestDiagonalRectangle,
                           extra_testcase_1) {
  auto                solution   = MakeSolution();
  vector<vector<int>> dimensions = {
      { 4,  7},
      { 8,  9},
      { 5,  3},
      { 6, 10},
      { 2,  9},
      { 3, 10},
      { 2,  2},
      { 5,  8},
      { 5, 10},
      { 5,  6},
      { 8,  9},
      {10,  7},
      { 8,  9},
      { 3,  7},
      { 2,  6},
      { 5,  1},
      { 7,  4},
      { 1, 10},
      { 1,  7},
      { 6,  9},
      { 3,  3},
      { 4,  6},
      { 8,  2},
      {10,  6},
      { 7,  9},
      { 9,  2},
      { 1,  2},
      { 3,  8},
      {10,  2},
      { 4,  1},
      { 9,  7},
      {10,  3},
      { 6,  9},
      { 9,  8},
      { 7,  7},
      { 5,  7},
      { 5,  4},
      { 6,  5},
      { 1,  8},
      { 2,  3},
      { 7, 10},
      { 3,  9},
      { 5,  7},
      { 2,  4},
      { 5,  6},
      { 9,  5},
      { 8,  8},
      { 8, 10},
      { 6,  8},
      { 5,  1},
      {10,  8},
      { 7,  4},
      { 2,  1},
      { 2,  7},
      {10,  3},
      { 2,  5},
      { 7,  6},
      {10,  5},
      {10,  9},
      { 5,  7},
      {10,  6},
      { 4,  3},
      {10,  4},
      { 1,  5},
      { 8,  9},
      { 3,  1},
      { 2,  5},
      { 9, 10},
      { 6,  6},
      { 5, 10},
      {10,  2},
      { 6, 10},
      { 1,  1},
      { 8,  6},
      { 1,  7},
      { 6,  3},
      { 9,  3},
      { 1,  4},
      { 1,  1},
      {10,  4},
      { 7,  9},
      { 4,  5},
      { 2,  8},
      { 7,  9},
      { 7,  3},
      { 4,  9},
      { 2,  8},
      { 4,  6},
      { 9,  1},
      { 8,  4},
      { 2,  4},
      { 7,  8},
      { 3,  5},
      { 7,  6},
      { 8,  6},
      { 4,  7},
      {25, 60},
      {39, 52},
      {16, 63},
      {33, 56}
  };
  int expect = 2028;
  int actual = solution->areaOfMaxDiagonal(dimensions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [[6,5],[8,6],[2,10],[8,1],[9,2],[3,5],[3,5]]
// Output: 20
//

LEETCODE_SOLUTION_UNITTEST(3000, MaximumAreaOfLongestDiagonalRectangle,
                           extra_testcase_2) {
  auto                solution   = MakeSolution();
  vector<vector<int>> dimensions = {
      {6,  5},
      {8,  6},
      {2, 10},
      {8,  1},
      {9,  2},
      {3,  5},
      {3,  5}
  };
  int expect = 20;
  int actual = solution->areaOfMaxDiagonal(dimensions);
  LCD_EXPECT_EQ(expect, actual);
}
