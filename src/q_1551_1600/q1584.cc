// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Min Cost to Connect All Points
//
// https://leetcode.com/problems/min-cost-to-connect-all-points/
//
// Question ID: 1584
// Difficult  : Medium
// Solve Date : 2022/04/26 18:35

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1584. Min Cost to Connect All Points|:
//
// You are given an array |points| representing integer coordinates of some
// points on a 2D-plane, where |points[i] = [xᵢ, yᵢ]|. The cost of connecting
// two points |[xᵢ, yᵢ]| and |[xⱼ, yⱼ]| is the manhattan distance between them:
// ||xᵢ - xⱼ| + |yᵢ - yⱼ||, where ||val|| denotes the absolute value of |val|.
// Return the minimum cost to make all points connected. All points are
// connected if there is exactly one simple path between any two points.  
//

LEETCODE_BEGIN_RESOLVING(1584, MinCostToConnectAllPoints, Solution);

class Solution {
public:
  int minCostConnectPoints(vector<vector<int>> &points) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
                 pq;
    int          n = points.size();
    vector<bool> mst(n, false);
    pq.emplace(0, 0);

    int res = 0, edges = n;

    while (edges) {
      auto [cost, curr] = pq.top();
      pq.pop();

      if (mst[curr])
        continue;

      mst[curr] = true;
      res += cost;
      --edges;

      for (int i = 0; i < n; ++i) {
        if (!mst[i]) {
          pq.emplace(abs(points[curr][0] - points[i][0]) +
                         abs(points[curr][1] - points[i][1]),
                     i);
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 1000|
// * |-10⁶ <= xᵢ, yᵢ <= 10⁶|
// * All pairs |(xᵢ, yᵢ)| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
//
// ![img](https://assets.leetcode.com/uploads/2020/08/26/c.png)
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.

LEETCODE_SOLUTION_UNITTEST(1584, MinCostToConnectAllPoints, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0,  0},
      {2,  2},
      {3, 10},
      {5,  2},
      {7,  0}
  };
  int expect = 20;
  int actual = solution->minCostConnectPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[3,12],[-2,5],[-4,1]]
// Output: 18
//

LEETCODE_SOLUTION_UNITTEST(1584, MinCostToConnectAllPoints, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 3, 12},
      {-2,  5},
      {-4,  1}
  };
  int expect = 18;
  int actual = solution->minCostConnectPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}
