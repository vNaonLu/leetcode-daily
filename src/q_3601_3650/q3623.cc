// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Number of Trapezoids I
//
// https://leetcode.com/problems/count-number-of-trapezoids-i/
//
// Question ID: 3623
// Difficult  : Medium
// Solve Date : 2025/12/02 18:48

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3623. Count Number of Trapezoids I|:
//
// You are given a 2D integer array |points|, where |points[i] = [xᵢ, yᵢ]|
// represents the coordinates of the |iᵗʰ| point on the Cartesian plane. A
// horizontal trapezoid is a convex quadrilateral with at least one pair of
// horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if and
// only if they have the same slope. Return the  number of unique horizontal
// trapezoids that can be formed by choosing any four distinct points from
// |points|. Since the answer may be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3623, CountNumberOfTrapezoidsI, Solution);

class Solution {
public:
  static int countTrapezoids(vector<vector<int>> &points) {
    const long long mod = 1e9 + 7, n = points.size();
    int            *y = (int *)alloca(n * sizeof(int));
    int             i = 0;
    for (auto &p : points)
      y[i++] = p[1];
    sort(y, y + n);
    long long sum = 0, c2 = 0, c = 0;
    int       f = 1, prev = y[0];
    for (int i = 1; i < n; i++) {
      if (prev == y[i])
        f++;
      else {
        c = f * (f - 1LL) / 2LL;
        sum += c;
        c2 += c * c;
        f    = 1;
        prev = y[i];
      }
    }
    c = f * (f - 1LL) / 2LL;
    sum += c;
    c2 += c * c;
    return (sum * sum - c2) / 2 % mod;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |4 <= points.length <= 10⁵|
// * |–10⁸ <= xᵢ, yᵢ <= 10⁸|
// * All points are pairwise distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3623, CountNumberOfTrapezoidsI, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 0},
      {2, 0},
      {3, 0},
      {2, 2},
      {3, 2}
  };
  int expect = 3;
  int actual = solution->countTrapezoids(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[0,0],[1,0],[0,1],[2,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3623, CountNumberOfTrapezoidsI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0, 0},
      {1, 0},
      {0, 1},
      {2, 1}
  };
  int expect = 1;
  int actual = solution->countTrapezoids(points);
  LCD_EXPECT_EQ(expect, actual);
}
