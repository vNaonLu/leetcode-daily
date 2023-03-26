// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Cycle in a Graph
//
// https://leetcode.com/problems/longest-cycle-in-a-graph/
//
// Question ID: 2360
// Difficult  : Hard
// Solve Date : 2023/03/26 11:42

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2360. Longest Cycle in a Graph|:
//
// You are given a directed graph of |n| nodes numbered from |0| to |n - 1|,
// where each node has at most one outgoing edge. The graph is represented with
// a given 0-indexed array |edges| of size |n|, indicating that there is a
// directed edge from node |i| to node |edges[i]|. If there is no outgoing edge
// from node |i|, then |edges[i] == -1|. Return the length of the longest cycle
// in the graph. If no cycle exists, return |-1|. A cycle is a path that starts
// and ends at the same node.
//
//

LEETCODE_BEGIN_RESOLVING(2360, LongestCycleInAGraph, Solution);

class Solution {
public:
  // dfs function for finding the length of cycle

  void dfs(vector<int> &edges, int u, vector<bool> &vis, int &count) {
    vis[u] = true;
    ++count;
    if (edges[u] != -1 && vis[edges[u]] == false) {
      dfs(edges, edges[u], vis, count);
    }
  }

  int longestCycle(vector<int> &edges) {
    int         n = edges.size();
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; i++) {
      int v = edges[i];
      if (v != -1) {
        indegree[v]++;
      }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (edges[u] != -1) {
        --indegree[edges[u]];
        if (indegree[edges[u]] == 0) {
          q.push(edges[u]);
        }
      }
    }

    vector<bool> vis(n, false);
    int          res = numeric_limits<int>::min();
    ;
    for (int i = 0; i < n; i++) {
      int count = 0;

      if (indegree[i] > 0 && vis[i] == false) {
        dfs(edges, i, vis, count);
      }

      res = max(res, count);
    }

    // if there is no cycle in graph, return -1

    if (res == 0)
      return -1;

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == edges.length|
// * |2 <= n <= 10⁵|
// * |-1 <= edges[i] < n|
// * |edges[i] != i|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [3,3,4,2,3]
// Output: 3
//
// The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
// The length of this cycle is 3, so 3 is returned.

LEETCODE_SOLUTION_UNITTEST(2360, LongestCycleInAGraph, example_1) {
  auto        solution = MakeSolution();
  vector<int> edges    = {3, 3, 4, 2, 3};
  int         expect   = 3;
  int         actual   = solution->longestCycle(edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [2,-1,3,1]
// Output: -1
//
// There are no cycles in this graph.

LEETCODE_SOLUTION_UNITTEST(2360, LongestCycleInAGraph, example_2) {
  auto        solution = MakeSolution();
  vector<int> edges    = {2, -1, 3, 1};
  int         expect   = -1;
  int         actual   = solution->longestCycle(edges);
  LCD_EXPECT_EQ(expect, actual);
}
