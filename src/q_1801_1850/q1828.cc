// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Queries on Number of Points Inside a Circle
//
// https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/
//
// Question ID: 1828
// Difficult  : Medium
// Solve Date : 2022/02/10 16:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1828. Queries on Number of Points Inside a Circle|:
//
// You are given an array |points| where |points[i] = [xᵢ, yᵢ]| is the
// coordinates of the |iᵗʰ| point on a 2D plane. Multiple points can have the
// same coordinates. You are also given an array |queries| where |queries[j] =
// [xⱼ, yⱼ, rⱼ]| describes a circle centered at |(xⱼ, yⱼ)| with a radius of
// |rⱼ|. For each query |queries[j]|, compute the number of points inside the
// |jᵗʰ| circle. Points on the border of the circle are considered inside.
// Return an array |answer|, where |answer[j]| is the answer to the |jᵗʰ| query.
//  
//

LEETCODE_BEGIN_RESOLVING(1828, QueriesOnNumberOfPointsInsideACircle, Solution);

class Solution {
public:
  vector<int> countPoints(vector<vector<int>> &points,
                          vector<vector<int>> &queries) {
    vector<int> res;
    for (const auto &circle : queries) {
      int pts_cnt = 0, radius_sq = circle[2] * circle[2];
      for (const auto &pt : points) {
        int dx = pt[0] - circle[0], dy = pt[1] - circle[1];
        if (dx * dx + dy * dy <= radius_sq)
          ++pts_cnt;
      }
      res.emplace_back(pts_cnt);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 500|
// * |points[i].length == 2|
// * |0 <= x^{​​​​​​i}, y^{​​​​​​i} <= 500|
// * |1 <= queries.length <= 500|
// * |queries[j].length == 3|
// * |0 <= xⱼ, yⱼ <= 500|
// * |1 <= rⱼ <= 500|
// * All coordinates are integers.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,3],[3,3],[5,3],[2,2]], queries =
//  [[2,3,1],[4,3,1],[1,1,2]]
// Output: [3,2,2]
// Explanation: The points and circles are shown above.
// queries[0] is the green circle, queries[1] is the red circle, and queries[2]
// is the blue circle.
//

LEETCODE_SOLUTION_UNITTEST(1828, QueriesOnNumberOfPointsInsideACircle,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 3},
      {3, 3},
      {5, 3},
      {2, 2}
  };
  vector<vector<int>> queries = {
      {2, 3, 1},
      {4, 3, 1},
      {1, 1, 2}
  };
  vector<int> expect = {3, 2, 2};
  vector<int> actual = solution->countPoints(points, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,1],[2,2],[3,3],[4,4],[5,5]], queries =
//  [[1,2,2],[2,2,2],[4,3,2],[4,3,3]]
// Output: [2,3,2,4]
// Explanation: The points and circles are shown above.
// queries[0] is green, queries[1] is red, queries[2] is blue, and queries[3] is
// purple.
//

LEETCODE_SOLUTION_UNITTEST(1828, QueriesOnNumberOfPointsInsideACircle,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3},
      {4, 4},
      {5, 5}
  };
  vector<vector<int>> queries = {
      {1, 2, 2},
      {2, 2, 2},
      {4, 3, 2},
      {4, 3, 3}
  };
  vector<int> expect = {2, 3, 2, 4};
  vector<int> actual = solution->countPoints(points, queries);
  LCD_EXPECT_EQ(expect, actual);
}
