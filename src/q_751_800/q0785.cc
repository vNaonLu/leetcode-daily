// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Is Graph Bipartite?
//
// https://leetcode.com/problems/is-graph-bipartite/
//
// Question ID: 785
// Difficult  : Medium
// Solve Date : 2022/03/23 18:56

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |785. Is Graph Bipartite?|:
//
// There is an undirected graph with |n| nodes, where each node is numbered
// between |0| and |n - 1|. You are given a 2D array |graph|, where |graph[u]|
// is an array of nodes that node |u| is adjacent to. More formally, for each
// |v| in |graph[u]|, there is an undirected edge between node |u| and node |v|.
// The graph has the following properties:
//
//  • There are no self-edges ( |graph[u]| does not contain |u|).
//
//  • There are no parallel edges ( |graph[u]| does not contain duplicate
//  values).
//
//  • If |v| is in |graph[u]|, then |u| is in |graph[v]| (the graph is
//  undirected).
//
//  • The graph may not be connected, meaning there may be two nodes |u| and |v|
//  such that there is no path between them.
// A graph is bipartite if the nodes can be partitioned into two independent
// sets |A| and |B| such that every edge in the graph connects a node in set |A|
// and a node in set |B|. Return |true| if and only if it is bipartite.  
//

LEETCODE_BEGIN_RESOLVING(785, IsGraphBipartite, Solution);

class Solution {
public:
  bool isBipartite(vector<vector<int>> &graph) {
    int n = graph.size();

    vector<int> grouped(n, false), visited(n, false);

    for (int i = 0; i < n; ++i) {
      if (visited[i])
        continue;

      queue<int> q;
      q.emplace(i);

      while (!q.empty()) {
        auto x = q.front();
        q.pop();

        for (auto &y : graph[x]) {
          if (visited[y]) {
            if (grouped[x] == grouped[y]) {
              return false;
            }
          } else {
            visited[y] = true;
            grouped[y] = !grouped[x];
            q.emplace(y);
          }
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |graph.length == n|
// * |1 <= n <= 100|
// * |0 <= graph[u].length < n|
// * |0 <= graph[u][i] <= n - 1|
// * |graph[u]| does not contain  |u|.
// * All the values of |graph[u]| are unique.
// * If |graph[u]| contains |v|, then |graph[v]| contains |u|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
// Output: false
//
// There is no way to partition the nodes into two independent sets such that
// every edge connects a node in one and a node in the other.

LEETCODE_SOLUTION_UNITTEST(785, IsGraphBipartite, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 2, 3},
      {0, 2},
      {0, 1, 3},
      {0, 2}
  };
  bool expect = false;
  bool actual = solution->isBipartite(graph);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: graph = [[1,3],[0,2],[1,3],[0,2]]
// Output: true
//
// We can partition the nodes into two sets: {0, 2} and {1, 3}.

LEETCODE_SOLUTION_UNITTEST(785, IsGraphBipartite, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 3},
      {0, 2},
      {1, 3},
      {0, 2}
  };
  bool expect = true;
  bool actual = solution->isBipartite(graph);
  LCD_EXPECT_EQ(expect, actual);
}
