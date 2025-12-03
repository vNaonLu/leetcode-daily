// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Number of Trapezoids II
//
// https://leetcode.com/problems/count-number-of-trapezoids-ii/
//
// Question ID: 3625
// Difficult  : Hard
// Solve Date : 2025/12/03 19:59

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3625. Count Number of Trapezoids II|:
//
// You are given a 2D integer array |points| where |points[i] = [xᵢ, yᵢ]|
// represents the coordinates of the |iᵗʰ| point on the Cartesian plane. Return
// the number of unique trapezoids that can be formed by choosing any four
// distinct points from |points|. A trapezoid is a convex quadrilateral with at
// least one pair of parallel sides. Two lines are parallel if and only if they
// have the same slope.
//
//

LEETCODE_BEGIN_RESOLVING(3625, CountNumberOfTrapezoidsII, Solution);

class Solution {
public:
  int countTrapezoids(vector<vector<int>> &points) {
    int                                 n   = points.size();
    int                                 inf = 1e9 + 7;
    unordered_map<float, vector<float>> slopeToIntercept;
    unordered_map<int, vector<float>>   midToSlope;
    int                                 ans = 0;
    for (int i = 0; i < n; i++) {
      int x1 = points[i][0];
      int y1 = points[i][1];
      for (int j = i + 1; j < n; j++) {
        int   x2 = points[j][0];
        int   y2 = points[j][1];
        int   dx = x1 - x2;
        int   dy = y1 - y2;
        float k, b;
        if (x2 == x1) {
          k = inf;
          b = x1;
        } else {
          k = (float)(y2 - y1) / (x2 - x1);
          b = (float)(y1 * dx - x1 * dy) / dx;
        }
        int mid = (x1 + x2) * 10000 + (y1 + y2);
        slopeToIntercept[k].push_back(b);
        midToSlope[mid].push_back(k);
      }
    }
    for (auto &[_, sti] : slopeToIntercept) {
      if (sti.size() == 1) {
        continue;
      }
      map<float, int> cnt;
      for (float b : sti) {
        cnt[b]++;
      }
      int sum = 0;
      for (auto &[_, count] : cnt) {
        ans += sum * count;
        sum += count;
      }
    }
    for (auto &[_, mts] : midToSlope) {
      if (mts.size() == 1) {
        continue;
      }
      map<float, int> cnt;
      for (float k : mts) {
        cnt[k]++;
      }
      int sum = 0;
      for (auto &[_, count] : cnt) {
        ans -= sum * count;
        sum += count;
      }
    }
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |4 <= points.length <= 500|
// * |–1000 <= xᵢ, yᵢ <= 1000|
// * All points are pairwise distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3625, CountNumberOfTrapezoidsII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {-3,  2},
      { 3,  0},
      { 2,  3},
      { 3,  2},
      { 2, -3}
  };
  int expect = 2;
  int actual = solution->countTrapezoids(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[0,0],[1,0],[0,1],[2,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3625, CountNumberOfTrapezoidsII, example_2) {
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
