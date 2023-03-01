// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Score Triangulation of Polygon
//
// https://leetcode.com/problems/minimum-score-triangulation-of-polygon/
//
// Question ID: 1039
// Difficult  : Medium
// Solve Date : 2022/02/15 18:46

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1039. Minimum Score Triangulation of Polygon|:
//
// You have a convex |n|-sided polygon where each vertex has an integer value.
// You are given an integer array |values| where |values[i]| is the value of the
// |iᵗʰ| vertex (i.e., clockwise order). You will triangulate the polygon into
// |n - 2| triangles. For each triangle, the value of that triangle is the
// product of the values of its vertices, and the total score of the
// triangulation is the sum of these values over all |n - 2| triangles in the
// triangulation. Return the smallest possible total score that you can achieve
// with some triangulation of the polygon.  
//

LEETCODE_BEGIN_RESOLVING(1039, MinimumScoreTriangulationOfPolygon, Solution);

class Solution {
public:
  int minScoreTriangulation(vector<int> &values) {
    int                 n = values.size();
    vector<vector<int>> dp(n - 1, vector<int>(n - 1));
    for (int k = 0; k < n - 1; ++k) {
      for (int i = 0, j = k; j < n - 1; ++i, ++j) {
        if (k == 0) {
          dp[i][j] = 0;
        } else if (k == 1) {
          dp[i][j] = values[i] * values[j] * values[j + 1];
        } else {
          int min_cost = numeric_limits<int>::max();
          for (int t = i; t < j; ++t) {
            int lc = dp[i][t], rc = dp[t + 1][j],
                mc   = values[i] * values[t + 1] * values[j + 1],
                tc   = lc + rc + mc;
            min_cost = min(min_cost, tc);
          }
          dp[i][j] = min_cost;
        }
      }
    }
    return dp[0][n - 2];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == values.length|
// * |3 <= n <= 50|
// * |1 <= values[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: values = [1,2,3]
// Output: 6
//
// The polygon is already triangulated, and the score of the only triangle is 6.

LEETCODE_SOLUTION_UNITTEST(1039, MinimumScoreTriangulationOfPolygon,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> values   = {1, 2, 3};
  int         expect   = 6;
  int         actual   = solution->minScoreTriangulation(values);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: values = [3,7,4,5]
// Output: 144
//
// There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or
// 3*4*5 + 3*4*7 = 144. The minimum score is 144.

LEETCODE_SOLUTION_UNITTEST(1039, MinimumScoreTriangulationOfPolygon,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> values   = {3, 7, 4, 5};
  int         expect   = 144;
  int         actual   = solution->minScoreTriangulation(values);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: values = [1,3,1,4,1,5]
// Output: 13
//
// The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.

LEETCODE_SOLUTION_UNITTEST(1039, MinimumScoreTriangulationOfPolygon,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> values   = {1, 3, 1, 4, 1, 5};
  int         expect   = 13;
  int         actual   = solution->minScoreTriangulation(values);
  LCD_EXPECT_EQ(expect, actual);
}
