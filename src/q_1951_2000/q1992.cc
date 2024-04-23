// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find All Groups of Farmland
//
// https://leetcode.com/problems/find-all-groups-of-farmland/
//
// Question ID: 1992
// Difficult  : Medium
// Solve Date : 2024/04/20 11:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1992. Find All Groups of Farmland|:
//
// You are given a 0-indexed |m x n| binary matrix |land| where a |0| represents
// a hectare of forested land and a |1| represents a hectare of farmland. To
// keep the land organized, there are designated rectangular areas of hectares
// that consist entirely of farmland. These rectangular areas are called groups.
// No two groups are adjacent, meaning farmland in one group is not
// four-directionally adjacent to another farmland in a different group. |land|
// can be represented by a coordinate system where the top left corner of |land|
// is |(0, 0)| and the bottom right corner of |land| is |(m-1, n-1)|. Find the
// coordinates of the top left and bottom right corner of each group of
// farmland. A group of farmland with a top left corner at |(r₁, c₁)| and a
// bottom right corner at |(r₂, c₂)| is represented by the 4-length array |[r₁,
// c₁, r₂, c₂].| Return a 2D array containing the 4-length arrays described
// above for each group of farmland in |land|. If there are no groups of
// farmland, return an empty array. You may return the answer in any order.
//
//

LEETCODE_BEGIN_RESOLVING(1992, FindAllGroupsOfFarmland, Solution);

class Solution {
public:
  vector<vector<int>> findFarmland(vector<vector<int>> &land) {
    vector<vector<int>> res;
    int                 m = land.size();
    int                 n = land[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (land[i][j] == 1) {
          vector<int> rect{i, j, i, j};
          helper(&land, m, n, &rect, i, j);
          res.emplace_back(std::move(rect));
        }
      }
    }
    return res;
  }

private:
  void helper(vector<vector<int>> *v, int m, int n, vector<int> *rect, int i,
              int j) {
    if (i >= m || j >= n || (*v)[i][j] != 1) {
      return;
    }

    (*rect)[2] = max((*rect)[2], i);
    (*rect)[3] = max((*rect)[3], j);
    (*v)[i][j] = 0;
    helper(v, m, n, rect, i + 1, j);
    helper(v, m, n, rect, i, j + 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == land.length|
// * |n == land[i].length|
// * |1 <= m, n <= 300|
// * |land| consists of only |0|'s and |1|'s.
// * Groups of farmland are rectangular in shape.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: land = [[1,0,0],[0,1,1],[0,1,1]]
// Output: [[0,0,0,0],[1,1,2,2]]
//

LEETCODE_SOLUTION_UNITTEST(1992, FindAllGroupsOfFarmland, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> land     = {
      {1, 0, 0},
      {0, 1, 1},
      {0, 1, 1}
  };
  vector<vector<int>> expect = {
      {0, 0, 0, 0},
      {1, 1, 2, 2}
  };
  vector<vector<int>> actual = solution->findFarmland(land);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: land = [[1,1],[1,1]]
// Output: [[0,0,1,1]]
//

LEETCODE_SOLUTION_UNITTEST(1992, FindAllGroupsOfFarmland, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> land     = {
      {1, 1},
      {1, 1}
  };
  vector<vector<int>> expect = {
      {0, 0, 1, 1}
  };
  vector<vector<int>> actual = solution->findFarmland(land);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: land = [[0]]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(1992, FindAllGroupsOfFarmland, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> land     = {{0}};
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->findFarmland(land);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[0,1],[1,0]]
// Output: [[0,1,0,1],[1,0,1,0]]
//

LEETCODE_SOLUTION_UNITTEST(1992, FindAllGroupsOfFarmland, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> land     = {
      {0, 1},
      {1, 0}
  };
  vector<vector<int>> expect = {
      {0, 1, 0, 1},
      {1, 0, 1, 0}
  };
  vector<vector<int>> actual = solution->findFarmland(land);
  EXPECT_ANYORDER_EQ(expect, actual);
}
