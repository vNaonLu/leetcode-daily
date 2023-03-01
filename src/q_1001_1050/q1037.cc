// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Boomerang
//
// https://leetcode.com/problems/valid-boomerang/
//
// Question ID: 1037
// Difficult  : Easy
// Solve Date : 2022/11/20 15:06

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1037. Valid Boomerang|:
//
// Given an array |points| where |points[i] = [xᵢ, yᵢ]| represents a point on
// the X-Y plane, return |true| if these points are a boomerang. A boomerang is
// a set of three points that are all distinct and not in a straight line.
//

LEETCODE_BEGIN_RESOLVING(1037, ValidBoomerang, Solution);

class Solution {
public:
  bool isBoomerang(vector<vector<int>> &p) {
    return p[0][0] * (p[1][1] - p[2][1]) + p[1][0] * (p[2][1] - p[0][1]) +
               p[2][0] * (p[0][1] - p[1][1]) !=
           0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |points.length == 3|
// * |points[i].length == 2|
// * |0 <= xᵢ, yᵢ <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[2,3],[3,2]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1037, ValidBoomerang, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 3},
      {3, 2}
  };
  bool expect = true;
  bool actual = solution->isBoomerang(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,1],[2,2],[3,3]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1037, ValidBoomerang, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3}
  };
  bool expect = false;
  bool actual = solution->isBoomerang(points);
  LCD_EXPECT_EQ(expect, actual);
}
