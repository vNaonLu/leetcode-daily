// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Unreachable Pairs of Nodes in an Undirected Graph
//
// https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
//
// Question ID: 2316
// Difficult  : Medium
// Solve Date : 2023/03/25 18:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2316. Count Unreachable Pairs of Nodes in an Undirected
// Graph|:
//
// You are given an integer |n|. There is an undirected graph with |n| nodes,
// numbered from |0| to |n - 1|. You are given a 2D integer array |edges| where
// |edges[i] = [aᵢ, bᵢ]| denotes that there exists an undirected edge connecting
// nodes |aᵢ| and |bᵢ|. Return the number of pairs of different nodes that are
// unreachable from each other.
//
//

LEETCODE_BEGIN_RESOLVING(2316, CountUnreachablePairsOfNodesInAnUndirectedGraph,
                         Solution);

class Solution {
private:
  void dfs(vector<vector<int>> &g, int node, vector<int> &vis, int &cnt) {
    ++cnt;
    vis[node] = 1;
    for (auto x : g[node]) {
      if (!vis[x]) {
        dfs(g, x, vis, cnt);
      }
    }
  }

public:
  long long countPairs(int n, vector<vector<int>> &edges) {
    vector<vector<int>> graph(n);
    for (auto &v : edges) {
      graph[v[0]].emplace_back(v[1]);
      graph[v[1]].emplace_back(v[0]);
    }
    vector<int> visit(n, 0);
    int64_t     res = 0;
    int64_t     sum = 0;
    int         cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (!visit[i]) {
        dfs(graph, i, visit, cnt);
        res += sum * cnt;
        sum += cnt;
        cnt = 0;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |0 <= edges.length <= 2 * 10⁵|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * There are no repeated edges.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edges = [[0,1],[0,2],[1,2]]
// Output: 0
//
// There are no pairs of nodes that are unreachable from each other. Therefore,
// we return 0.

LEETCODE_SOLUTION_UNITTEST(2316,
                           CountUnreachablePairsOfNodesInAnUndirectedGraph,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 2}
  };
  long long expect = 0;
  long long actual = solution->countPairs(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
// Output: 14
//
// There are 14 pairs of nodes that are unreachable from each other:
// [[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]].
// Therefore, we return 14.

LEETCODE_SOLUTION_UNITTEST(2316,
                           CountUnreachablePairsOfNodesInAnUndirectedGraph,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 2},
      {0, 5},
      {2, 4},
      {1, 6},
      {5, 4}
  };
  long long expect = 14;
  long long actual = solution->countPairs(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
