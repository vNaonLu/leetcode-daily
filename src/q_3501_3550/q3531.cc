// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Covered Buildings
//
// https://leetcode.com/problems/count-covered-buildings/
//
// Question ID: 3531
// Difficult  : Medium
// Solve Date : 2025/12/11 22:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3531. Count Covered Buildings|:
//
// You are given a positive integer |n|, representing an |n x n| city. You are
// also given a 2D grid |buildings|, where |buildings[i] = [x, y]| denotes a
// unique building located at coordinates |[x, y]|. A building is covered if
// there is at least one building in all four directions: left, right, above,
// and below. Return the number of covered buildings.
//
//

LEETCODE_BEGIN_RESOLVING(3531, CountCoveredBuildings, Solution);

class Solution {
public:
  int countCoveredBuildings(int n, vector<vector<int>> &buildings) {
    vector<int> minx(n + 1, n + 1);
    vector<int> maxx(n + 1, 0);
    vector<int> miny(n + 1, n + 1);
    vector<int> maxy(n + 1, 0);
    for (auto b : buildings) {
      int x   = b[0];
      int y   = b[1];
      minx[y] = min(minx[y], x);
      maxx[y] = max(maxx[y], x);
      miny[x] = min(miny[x], y);
      maxy[x] = max(maxy[x], y);
    }
    int res = 0;
    for (auto b : buildings) {
      int x = b[0];
      int y = b[1];
      if (minx[y] < x && x < maxx[y] && miny[x] < y && y < maxy[x]) {
        res += 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= buildings.length <= 10⁵ |
// * |buildings[i] = [x, y]|
// * |1 <= x, y <= n|
// * All coordinates of |buildings| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3531, CountCoveredBuildings, example_1) {
  auto                solution  = MakeSolution();
  int                 n         = 3;
  vector<vector<int>> buildings = {
      {1, 2},
      {2, 2},
      {3, 2},
      {2, 1},
      {2, 3}
  };
  int expect = 1;
  int actual = solution->countCoveredBuildings(n, buildings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3531, CountCoveredBuildings, example_2) {
  auto                solution  = MakeSolution();
  int                 n         = 3;
  vector<vector<int>> buildings = {
      {1, 1},
      {1, 2},
      {2, 1},
      {2, 2}
  };
  int expect = 0;
  int actual = solution->countCoveredBuildings(n, buildings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3531, CountCoveredBuildings, example_3) {
  auto                solution  = MakeSolution();
  int                 n         = 5;
  vector<vector<int>> buildings = {
      {1, 3},
      {3, 2},
      {3, 3},
      {3, 5},
      {5, 3}
  };
  int expect = 1;
  int actual = solution->countCoveredBuildings(n, buildings);
  LCD_EXPECT_EQ(expect, actual);
}
