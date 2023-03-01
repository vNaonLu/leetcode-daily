// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Path Visiting All Nodes
//
// https://leetcode.com/problems/shortest-path-visiting-all-nodes/
//
// Question ID: 847
// Difficult  : Hard
// Solve Date : 2022/02/26 14:01

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |847. Shortest Path Visiting All Nodes|:
//
// You have an undirected, connected graph of |n| nodes labeled from |0| to |n -
// 1|. You are given an array |graph| where |graph[i]| is a list of all the
// nodes connected with node |i| by an edge. Return the length of the shortest
// path that visits every node. You may start and stop at any node, you may
// revisit nodes multiple times, and you may reuse edges.  
//

LEETCODE_BEGIN_RESOLVING(847, ShortestPathVisitingAllNodes, Solution);

class Solution {
private:
  vector<vector<int>> graph;
  vector<vector<int>> cache = vector<vector<int>>(13, vector<int>(1 << 13, 0));

  int shortest(int from, int mask) {
    if (cache[from][mask] != 0) {
      return cache[from][mask];
    }

    if ((mask & (mask - 1)) == 0) {
      return 0;
    }

    cache[from][mask] = numeric_limits<int>::max() - 1;

    for (auto &node : graph[from]) {
      if ((mask & (1 << node)) == 0)
        continue;
      int already_visited =
          cache[node][mask] != 0 ? cache[node][mask] : shortest(node, mask);

      int not_visited = cache[node][mask ^ (1 << from)] != 0
                            ? cache[node][mask ^ (1 << from)]
                            : shortest(node, mask ^ (1 << from));

      cache[from][mask] =
          min(cache[from][mask], 1 + min(already_visited, not_visited));
    }

    return cache[from][mask];
  }

public:
  int shortestPathLength(vector<vector<int>> &graph) {
    int res = numeric_limits<int>::max(), n = graph.size(),
        end_mask = (1 << n) - 1;

    this->graph = move(graph);

    for (int i = 0; i < n; ++i) {
      res = min(res, shortest(i, end_mask));
    }

    graph = move(this->graph);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == graph.length|
// * |1 <= n <= 12|
// * |0 <= graph[i].length < n|
// * |graph[i]| does not contain |i|.
// * If |graph[a]| contains |b|, then |graph[b]| contains |a|.
// * The input graph is always connected.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
//
// One possible path is [1,0,2,0,3]

LEETCODE_SOLUTION_UNITTEST(847, ShortestPathVisitingAllNodes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 2, 3},
      {0},
      {0},
      {0}
  };
  int expect = 4;
  int actual = solution->shortestPathLength(graph);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
// Output: 4
//
// One possible path is [0,1,4,2,3]

LEETCODE_SOLUTION_UNITTEST(847, ShortestPathVisitingAllNodes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1},
      {0, 2, 4},
      {1, 3, 4},
      {2},
      {1, 2}
  };
  int expect = 4;
  int actual = solution->shortestPathLength(graph);
  LCD_EXPECT_EQ(expect, actual);
}
