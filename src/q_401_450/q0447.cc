// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Boomerangs
//
// https://leetcode.com/problems/number-of-boomerangs/
//
// Question ID: 447
// Difficult  : Medium
// Solve Date : 2024/03/27 19:25

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |447. Number of Boomerangs|:
//
// You are given |n| |points| in the plane that are all distinct, where
// |points[i] = [xᵢ, yᵢ]|. A boomerang is a tuple of points |(i, j, k)| such
// that the distance between |i| and |j| equals the distance between |i| and |k|
// (the order of the tuple matters). Return the number of boomerangs.
//
//

LEETCODE_BEGIN_RESOLVING(447, NumberOfBoomerangs, Solution);

class Solution {
public:
  int numberOfBoomerangs(vector<vector<int>> &points) {
    int                 n = points.size();
    vector<vector<int>> dis(n, vector<int>(n, 0));
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        dis[i][j] = dis[j][i] = dist(points, i, j);
      }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
      auto &len = dis[i];
      sort(len.begin(), len.end());
      int last  = len[0];
      int count = 1;
      for (int j = 1; j < len.size(); ++j) {
        if (len[j] == last) {
          ++count;
        } else {
          res += count * (count - 1);
          count = 1;
          last  = len[j];
        }
      }
      res += count * (count - 1);
    }
    return res;
  }

private:
  int dist(vector<vector<int>> const &p, int i, int j) {
    auto &a = p[i];
    auto &b = p[j];
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == points.length|
// * |1 <= n <= 500|
// * |points[i].length == 2|
// * |-10⁴ <= xᵢ, yᵢ <= 10⁴|
// * All the points are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[0,0],[1,0],[2,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(447, NumberOfBoomerangs, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0, 0},
      {1, 0},
      {2, 0}
  };
  int expect = 2;
  int actual = solution->numberOfBoomerangs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,1],[2,2],[3,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(447, NumberOfBoomerangs, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3}
  };
  int expect = 2;
  int actual = solution->numberOfBoomerangs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: points = [[1,1]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(447, NumberOfBoomerangs, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1}
  };
  int expect = 0;
  int actual = solution->numberOfBoomerangs(points);
  LCD_EXPECT_EQ(expect, actual);
}
