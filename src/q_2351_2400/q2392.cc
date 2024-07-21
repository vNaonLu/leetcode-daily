// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Build a Matrix With Conditions
//
// https://leetcode.com/problems/build-a-matrix-with-conditions/
//
// Question ID: 2392
// Difficult  : Hard
// Solve Date : 2024/07/21 12:44

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2392. Build a Matrix With Conditions|:
//
// You are given a positive integer |k|. You are also given:
//
//  • a 2D integer array |rowConditions| of size |n| where |rowConditions[i] =
//  [aboveᵢ, belowᵢ]|, and
//
//  • a 2D integer array |colConditions| of size |m| where |colConditions[i] =
//  [leftᵢ, rightᵢ]|.
// The two arrays contain integers from |1| to |k|.
// You have to build a |k x k| matrix that contains each of the numbers from |1|
// to |k| exactly once. The remaining cells should have the value |0|. The
// matrix should also satisfy the following conditions:
//
//  • The number |aboveᵢ| should appear in a row that is strictly above the row
//  at which the number |belowᵢ| appears for all |i| from |0| to |n - 1|.
//
//  • The number |leftᵢ| should appear in a column that is strictly left of the
//  column at which the number |rightᵢ| appears for all |i| from |0| to |m - 1|.
// Return any matrix that satisfies the conditions. If no answer exists, return
// an empty matrix.
//
//

LEETCODE_BEGIN_RESOLVING(2392, BuildAMatrixWithConditions, Solution);

class Solution {
public:
  vector<vector<int>> buildMatrix(int k, vector<vector<int>> &rowConditions,
                                  vector<vector<int>> &colConditions) {
    auto r = topoSort(k, rowConditions);
    auto c = topoSort(k, colConditions);
    if (r.empty() || c.empty()) {
      return {};
    }

    vector<vector<int>> res(k, vector<int>(k));
    vector<int>         pos_i(k + 1, -1);
    vector<int>         pos_j(k + 1, -1);
    for (int i = 0; i < k; ++i) {
      pos_i[r[i]] = i;
      pos_j[c[i]] = i;
    }

    for (int i = 1; i <= k; ++i) {
      res[pos_i[i]][pos_j[i]] = i;
    }

    return res;
  }

private:
  vector<int> topoSort(int k, vector<vector<int>> const &cnd) {
    vector<vector<int>> adj(k + 1);
    vector<int>         deg(k + 1);
    for (auto &edge : cnd) {
      int v = edge[0];
      int w = edge[1];
      adj[v].push_back(w);
      ++deg[w];
    }
    queue<int> q;
    for (int i = 1; i <= k; ++i) {
      if (!deg[i]) {
        q.push(i);
      }
    }

    int         count = 0;
    vector<int> res;
    res.reserve(k);
    while (!q.empty()) {
      int j = q.front();
      q.pop();
      res.push_back(j);
      ++count;
      for (int k : adj[j]) {
        --deg[k];
        if (!deg[k]) {
          q.push(k);
        }
      }
    }
    return count != k ? vector<int>{} : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= k <= 400|
// * |1 <= rowConditions.length, colConditions.length <= 10⁴|
// * |rowConditions[i].length == colConditions[i].length == 2|
// * |1 <= aboveᵢ, belowᵢ, leftᵢ, rightᵢ <= k|
// * |aboveᵢ != belowᵢ|
// * |leftᵢ != rightᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
// Output: [[3,0,0],[0,0,1],[0,2,0]]
//

LEETCODE_SOLUTION_UNITTEST(2392, BuildAMatrixWithConditions, example_1) {
  auto                solution      = MakeSolution();
  int                 k             = 3;
  vector<vector<int>> rowConditions = {
      {1, 2},
      {3, 2}
  };
  vector<vector<int>> colConditions = {
      {2, 1},
      {3, 2}
  };
  vector<vector<int>> expect = {
      {0, 0, 1},
      {3, 0, 0},
      {0, 2, 0}
  };
  vector<vector<int>> actual =
      solution->buildMatrix(k, rowConditions, colConditions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions =
//  [[2,1]]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(2392, BuildAMatrixWithConditions, example_2) {
  auto                solution      = MakeSolution();
  int                 k             = 3;
  vector<vector<int>> rowConditions = {
      {1, 2},
      {2, 3},
      {3, 1},
      {2, 3}
  };
  vector<vector<int>> colConditions = {
      {2, 1}
  };
  vector<vector<int>> expect = {};
  vector<vector<int>> actual =
      solution->buildMatrix(k, rowConditions, colConditions);
  LCD_EXPECT_EQ(expect, actual);
}
