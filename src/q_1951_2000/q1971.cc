// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find if Path Exists in Graph
//
// https://leetcode.com/problems/find-if-path-exists-in-graph/
//
// Question ID: 1971
// Difficult  : Easy
// Solve Date : 2022/12/09 11:43

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1971. Find if Path Exists in Graph|:
//
// There is a bi-directional graph with |n| vertices, where each vertex is
// labeled from |0| to |n - 1| (inclusive). The edges in the graph are
// represented as a 2D integer array |edges|, where each |edges[i] = [uᵢ, vᵢ]|
// denotes a bi-directional edge between vertex |uᵢ| and vertex |vᵢ|. Every
// vertex pair is connected by at most one edge, and no vertex has an edge to
// itself. You want to determine if there is a valid path that exists from
// vertex |source| to vertex |destination|. Given |edges| and the integers |n|,
// |source|, and |destination|, return |true| if there is a valid path from
// |source| to |destination|, or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1971, FindIfPathExistsInGraph, Solution);

class Solution {
public:
  bool validPath(int n, vector<vector<int>> &edges, int source,
                 int destination) {
    auto graph   = vector<unordered_set<int>>(n);
    auto path    = queue<int>();
    auto visited = unordered_set<int>();
    for (auto &e : edges) {
      graph[e[0]].emplace(e[1]);
      graph[e[1]].emplace(e[0]);
    }
    path.emplace(source);
    visited.emplace(source);
    while (!path.empty()) {
      auto x = path.front();
      path.pop();

      if (x == destination) {
        return true;
      }

      for (auto next : graph[x]) {
        if (visited.emplace(next).second) {
          path.emplace(next);
        }
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2 * 10⁵|
// * |0 <= edges.length <= 2 * 10⁵|
// * |edges[i].length == 2|
// * |0 <= uᵢ, vᵢ <= n - 1|
// * |uᵢ != vᵢ|
// * |0 <= source, destination <= n - 1|
// * There are no duplicate edges.
// * There are no self edges.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
// Output: true
//
// There are two paths from vertex 0 to vertex 2:
// - 0 → 1 → 2
// - 0 → 2

LEETCODE_SOLUTION_UNITTEST(1971, FindIfPathExistsInGraph, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {2, 0}
  };
  int  source      = 0;
  int  destination = 2;
  bool expect      = true;
  bool actual      = solution->validPath(n, edges, source, destination);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0,
//  destination = 5
// Output: false
//
// There is no path from vertex 0 to vertex 5.

LEETCODE_SOLUTION_UNITTEST(1971, FindIfPathExistsInGraph, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {3, 5},
      {5, 4},
      {4, 3}
  };
  int  source      = 0;
  int  destination = 5;
  bool expect      = false;
  bool actual      = solution->validPath(n, edges, source, destination);
  LCD_EXPECT_EQ(expect, actual);
}
