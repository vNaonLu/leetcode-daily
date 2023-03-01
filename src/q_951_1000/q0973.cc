// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K Closest Points to Origin
//
// https://leetcode.com/problems/k-closest-points-to-origin/
//
// Question ID: 973
// Difficult  : Medium
// Solve Date : 2021/10/09 15:18

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |973. K Closest Points to Origin|:
//
// Given an array of |points| where |points[i] = [xᵢ, yᵢ]| represents a point on
// the X-Y plane and an integer |k|, return the |k| closest points to the origin
// |(0, 0)|. The distance between two points on the X-Y plane is the Euclidean
// distance (i.e., |√(x₁ - x₂)² + (y₁ - y₂)²|). You may return the answer in any
// order. The answer is guaranteed to be unique (except for the order that it is
// in).  
//

LEETCODE_BEGIN_RESOLVING(973, KClosestPointsToOrigin, Solution);

class Solution {
private:
  using pii = pair<int, int>;

public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    vector<vector<int>>                            res;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < points.size(); ++i)
      pq.push(make_pair(
          points[i][0] * points[i][0] + points[i][1] * points[i][1], i));
    while (k--) {
      auto top = pq.top();
      pq.pop();
      res.push_back(points[top.second]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= points.length <= 10⁴|
// * |-10⁴ < xᵢ, yᵢ < 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,3],[-2,2]], k = 1
// Output: [[-2,2]]
//
// The distance between (1, 3) and the origin is sqrt(10).
// The distance between (-2, 2) and the origin is sqrt(8).
// Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
// We only want the closest k = 1 points from the origin, so the answer is just
// [[-2,2]].

LEETCODE_SOLUTION_UNITTEST(973, KClosestPointsToOrigin, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 1, 3},
      {-2, 2}
  };
  int                 k      = 1;
  vector<vector<int>> expect = {
      {-2, 2}
  };
  vector<vector<int>> actual = solution->kClosest(points, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[3,3],[5,-1],[-2,4]], k = 2
// Output: [[3,3],[-2,4]]
//
// The answer [[-2,4],[3,3]] would also be accepted.

LEETCODE_SOLUTION_UNITTEST(973, KClosestPointsToOrigin, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 3,  3},
      { 5, -1},
      {-2,  4}
  };
  int                 k      = 2;
  vector<vector<int>> expect = {
      { 3, 3},
      {-2, 4}
  };
  vector<vector<int>> actual = solution->kClosest(points, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}
