// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximize the Distance Between Points on a Square
//
// https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/
//
// Question ID: 3464
// Difficult  : Hard
// Solve Date : 2026/04/25 12:54

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3464. Maximize the Distance Between Points on a Square|:
//
// You are given an integer |side|, representing the edge length of a square
// with corners at |(0, 0)|, |(0, side)|, |(side, 0)|, and |(side, side)| on a
// Cartesian plane. You are also given a positive integer |k| and a 2D integer
// array |points|, where |points[i] = [xᵢ, yᵢ]| represents the coordinate of a
// point lying on the boundary of the square. You need to select |k| elements
// among |points| such that the minimum Manhattan distance between any two
// points is maximized. Return the maximum possible minimum Manhattan distance
// between the selected |k| points. The Manhattan Distance between two cells
// |(xᵢ, yᵢ)| and |(xⱼ, yⱼ)| is ||xᵢ - xⱼ| + |yᵢ - yⱼ||.
//
//

LEETCODE_BEGIN_RESOLVING(3464, MaximizeTheDistanceBetweenPointsOnASquare,
                         Solution);

class Solution {
public:
  int maxDistance(int side, vector<vector<int>> &points, int k) {
    vector<int64_t> res;
    for (auto &p : points) {
      int x = p[0], y = p[1];
      if (x == 0)
        res.push_back(y);
      else if (y == side)
        res.push_back((int64_t)side + x);
      else if (x == side)
        res.push_back((int64_t)side * 3 - y);
      else
        res.push_back((int64_t)side * 4 - x);
    }
    sort(res.begin(), res.end());

    auto check = [&](int n) {
      int         m = res.size();
      vector<int> idx(k);
      int64_t     curr = res[0];
      idx[0]           = 0;
      for (int i = 1; i < k; i++) {
        auto it = lower_bound(res.begin(), res.end(), curr + n);
        if (it == res.end())
          return false;
        idx[i] = distance(res.begin(), it);
        curr   = *it;
      }
      if (res[idx[k - 1]] - res[0] <= (int64_t)side * 4 - n)
        return true;

      for (idx[0] = 1; idx[0] < idx[1]; idx[0]++) {
        for (int j = 1; j < k; j++) {
          while (idx[j] < m && res[idx[j]] < res[idx[j - 1]] + n) {
            idx[j]++;
          }
          if (idx[j] == m)
            return false;
        }
        if (res[idx[k - 1]] - res[idx[0]] <= (int64_t)side * 4 - n)
          return true;
      }
      return false;
    };

    int left  = 1;
    int right = (1LL * side * 4) / k + 1;
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      if (check(mid))
        left = mid;
      else
        right = mid;
    }
    return left;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= side <= 10⁹|
// * |4 <= points.length <= min(4 * side, 15 * 10³)|
// * |points[i] == [xi, yi]|
// * The input is generated such that:
// • | points[i] | lies on the boundary of the square.
// * All |points[i]| are unique.
// * |4 <= k <= min(25, points.length)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3464, MaximizeTheDistanceBetweenPointsOnASquare,
                           example_1) {
  auto                solution = MakeSolution();
  int                 side     = 2;
  vector<vector<int>> points   = {
      {0, 2},
      {2, 0},
      {2, 2},
      {0, 0}
  };
  int k      = 4;
  int expect = 2;
  int actual = solution->maxDistance(side, points, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3464, MaximizeTheDistanceBetweenPointsOnASquare,
                           example_2) {
  auto                solution = MakeSolution();
  int                 side     = 2;
  vector<vector<int>> points   = {
      {0, 0},
      {1, 2},
      {2, 0},
      {2, 2},
      {2, 1}
  };
  int k      = 4;
  int expect = 1;
  int actual = solution->maxDistance(side, points, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3464, MaximizeTheDistanceBetweenPointsOnASquare,
                           example_3) {
  auto                solution = MakeSolution();
  int                 side     = 2;
  vector<vector<int>> points   = {
      {0, 0},
      {0, 1},
      {0, 2},
      {1, 2},
      {2, 0},
      {2, 2},
      {2, 1}
  };
  int k      = 5;
  int expect = 1;
  int actual = solution->maxDistance(side, points, k);
  LCD_EXPECT_EQ(expect, actual);
}
