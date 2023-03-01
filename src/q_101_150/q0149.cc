// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Points on a Line
//
// https://leetcode.com/problems/max-points-on-a-line/
//
// Question ID: 149
// Difficult  : Hard
// Solve Date : 2021/10/09 14:42

#include <iosfwd>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |149. Max Points on a Line|:
//
// Given an array of |points| where |points[i] = [xᵢ, yᵢ]| represents a point on
// the X-Y plane, return the maximum number of points that lie on the same
// straight line.  
//

LEETCODE_BEGIN_RESOLVING(149, MaxPointsOnALine, Solution);

class Solution {
public:
  int maxPoints(vector<vector<int>> &points) {
    int res = 0;
    for (auto pt1 = points.begin(); pt1 != points.end(); ++pt1) {
      unordered_map<double, int> slope;
      int                        same = 1;
      for (auto pt2 = pt1 + 1; pt2 != points.end(); ++pt2) {
        if (*pt1 == *pt2) {
          ++same;
        } else if ((*pt1)[0] == (*pt2)[0]) {
          ++slope[numeric_limits<double>::max()];
        } else {
          double s =
              (double)((*pt2)[1] - (*pt1)[1]) / (double)((*pt2)[0] - (*pt1)[0]);
          ++slope[s];
        }
      }
      int local_max = 0;
      for (auto it = slope.begin(); it != slope.end(); ++it)
        local_max = max(local_max, it->second);
      res = max(res, local_max + same);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 300|
// * |points[i].length == 2|
// * |-10⁴ <= xᵢ, yᵢ <= 10⁴|
// * All the |points| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(149, MaxPointsOnALine, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3}
  };
  int expect = 3;
  int actual = solution->maxPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(149, MaxPointsOnALine, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {3, 2},
      {5, 3},
      {4, 1},
      {2, 3},
      {1, 4}
  };
  int expect = 4;
  int actual = solution->maxPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}
