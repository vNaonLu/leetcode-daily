// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If It Is a Straight Line
//
// https://leetcode.com/problems/check-if-it-is-a-straight-line/
//
// Question ID: 1232
// Difficult  : Easy
// Solve Date : 2022/04/18 18:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1232. Check If It Is a Straight Line|:
//
// You are given an array  |coordinates|, |coordinates[i] = [x, y]|, where |[x,
// y]| represents the coordinate of a point. Check if these points make a
// straight line in the XY plane.
//
//  
//
//  
//

LEETCODE_BEGIN_RESOLVING(1232, CheckIfItIsAStraightLine, Solution);

class Solution {
public:
  bool checkStraightLine(vector<vector<int>> &coordinates) {
    double x = coordinates[1][0] - coordinates[0][0],
           y = coordinates[1][1] - coordinates[0][1];

    for (int i = 1; i < coordinates.size() - 1; ++i) {
      double dx = coordinates[i + 1][0] - coordinates[i][0],
             dy = coordinates[i + 1][1] - coordinates[i][1];
      if (x * dy != y * dx) {
        return false;
      }

      x = dx;
      y = dy;
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= coordinates.length <= 1000|
// * |coordinates[i].length == 2|
// * |-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4|
// * |coordinates| contains no duplicate point.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1232, CheckIfItIsAStraightLine, example_1) {
  auto                solution    = MakeSolution();
  vector<vector<int>> coordinates = {
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 5},
      {5, 6},
      {6, 7}
  };
  bool expect = true;
  bool actual = solution->checkStraightLine(coordinates);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1232, CheckIfItIsAStraightLine, example_2) {
  auto                solution    = MakeSolution();
  vector<vector<int>> coordinates = {
      {1, 1},
      {2, 2},
      {3, 4},
      {4, 5},
      {5, 6},
      {7, 7}
  };
  bool expect = false;
  bool actual = solution->checkStraightLine(coordinates);
  LCD_EXPECT_EQ(expect, actual);
}
