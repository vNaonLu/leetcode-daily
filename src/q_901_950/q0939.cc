// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Area Rectangle
//
// https://leetcode.com/problems/minimum-area-rectangle/
//
// Question ID: 939
// Difficult  : Medium
// Solve Date : 2024/09/26 19:52

#include <iosfwd>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |939. Minimum Area Rectangle|:
//
// You are given an array of points in the X-Y plane |points| where |points[i] =
// [xᵢ, yᵢ]|. Return the minimum area of a rectangle formed from these points,
// with sides parallel to the X and Y axes. If there is not any such rectangle,
// return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(939, MinimumAreaRectangle, Solution);

class Solution {
public:
  int minAreaRect(vector<vector<int>> &points) {
    unordered_map<int, unordered_set<int>> mp;
    for (auto &v : points) {
      mp[v[0]].emplace(v[1]);
    }

    optional<int> res;
    for (int i = 0; i < points.size(); ++i) {
      for (int j = i + 1; j < points.size(); ++j) {
        int x1 = points[i][0];
        int x2 = points[j][0];
        int y1 = points[i][1];
        int y2 = points[j][1];

        if (x1 == x2 || y1 == y2) {
          continue;
        }

        if (mp[x1].count(y2) && mp[x2].count(y1)) {
          auto area = abs(x1 - x2) * abs(y1 - y2);
          res       = min(res.value_or(area), area);
        }
      }
    }
    return res.value_or(0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 500|
// * |points[i].length == 2|
// * |0 <= xᵢ, yᵢ <= 4 * 10⁴|
// * All the given points are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(939, MinimumAreaRectangle, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {1, 3},
      {3, 1},
      {3, 3},
      {2, 2}
  };
  int expect = 4;
  int actual = solution->minAreaRect(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(939, MinimumAreaRectangle, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {1, 3},
      {3, 1},
      {3, 3},
      {4, 1},
      {4, 3}
  };
  int expect = 2;
  int actual = solution->minAreaRect(points);
  LCD_EXPECT_EQ(expect, actual);
}
