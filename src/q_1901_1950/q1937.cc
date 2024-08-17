// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Number of Points with Cost
//
// https://leetcode.com/problems/maximum-number-of-points-with-cost/
//
// Question ID: 1937
// Difficult  : Medium
// Solve Date : 2024/08/17 14:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1937. Maximum Number of Points with Cost|:
//
// You are given an |m x n| integer matrix |points| (0-indexed). Starting with
// |0| points, you want to maximize the number of points you can get from the
// matrix. To gain points, you must pick one cell in each row. Picking the cell
// at coordinates |(r, c)| will add |points[r][c]| to your score. However, you
// will lose points if you pick a cell too far from the cell that you picked in
// the previous row. For every two adjacent rows |r| and |r + 1| (where |0 <= r
// < m - 1|), picking cells at coordinates |(r, c₁)| and |(r + 1, c₂)| will
// subtract |abs(c₁ - c₂)| from your score. Return the maximum number of points
// you can achieve. |abs(x)| is defined as:
//
//  • |x| for |x >= 0|.
//
//  • |-x| for |x < 0|.
//
//

LEETCODE_BEGIN_RESOLVING(1937, MaximumNumberOfPointsWithCost, Solution);

class Solution {
public:
  long long maxPoints(vector<vector<int>> &points) {
    int             n = points[0].size();
    vector<int64_t> curr(n);
    vector<int64_t> prev(n);
    int64_t         res = 0;
    for (auto &v : points) {
      int64_t peak = 0;
      for (int i = 0; i < n; ++i) {
        peak    = max(peak - 1, prev[i]);
        curr[i] = peak;
      }
      peak = 0;
      for (int i = n - 1; i >= 0; --i) {
        peak    = max(peak - 1, prev[i]);
        curr[i] = max(curr[i], peak) + v[i];
      }
      prev.swap(curr);
    }
    res = *max_element(prev.begin(), prev.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == points.length|
// * |n == points[r].length|
// * |1 <= m, n <= 10⁵|
// * |1 <= m * n <= 10⁵|
// * |0 <= points[r][c] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,2,3],[1,5,1],[3,1,1]]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(1937, MaximumNumberOfPointsWithCost, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 2, 3},
      {1, 5, 1},
      {3, 1, 1}
  };
  long long expect = 9;
  long long actual = solution->maxPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,5],[2,3],[4,2]]
// Output: 11
//

LEETCODE_SOLUTION_UNITTEST(1937, MaximumNumberOfPointsWithCost, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 5},
      {2, 3},
      {4, 2}
  };
  long long expect = 11;
  long long actual = solution->maxPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}
