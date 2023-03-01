// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reachable Nodes In Subdivided Graph
//
// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/
//
// Question ID: 882
// Difficult  : Hard
// Solve Date : 2021/09/12 08:00

#include <iosfwd>
#include <limits>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |882. Reachable Nodes In Subdivided Graph|:
//
// You are given an undirected graph (the "original graph") with |n| nodes
// labeled from |0| to |n - 1|. You decide to subdivide each edge in the graph
// into a chain of nodes, with the number of new nodes varying between each
// edge. The graph is given as a 2D array of |edges| where |edges[i] = [uᵢ, vᵢ,
// cntᵢ]| indicates that there is an edge between nodes |uᵢ| and |vᵢ| in the
// original graph, and |cntᵢ| is the total number of new nodes that you will
// subdivide the edge into. Note that |cntᵢ == 0| means you will not subdivide
// the edge. To subdivide the edge |[uᵢ, vᵢ]|, replace it with |(cntᵢ + 1)| new
// edges and |cntᵢ| new nodes. The new nodes are |x₁|, |x₂|, ..., |x^{cnt}ᵢ|,
// and the new edges are |[uᵢ, x₁]|, |[x₁, x₂]|, |[x₂, x₃]|, ..., |[x^{cnt}ᵢ₋₁,
// x^{cnt}ᵢ]|, |[x^{cnt}ᵢ, vᵢ]|. In this new graph, you want to know how many
// nodes are reachable from the node |0|, where a node is reachable if the
// distance is |maxMoves| or less. Given the original graph and |maxMoves|,
// return the number of nodes that are reachable from node |0| in the new graph.
//  
//

LEETCODE_BEGIN_RESOLVING(882, ReachableNodesInSubdividedGraph, Solution);

class Solution {
public:
  int reachableNodes(vector<vector<int>> &edges, int maxMoves, int n) {
    vector<int> dist(n, numeric_limits<int>::max());
    unordered_map<int, unordered_map<int, int>> g;
    for (auto &e : edges)
      g[e[0]][e[1]] = g[e[1]][e[0]] = e[2] + 1;
    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
      return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
        cmp);
    pq.push({0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
      auto u = pq.top().first;
      pq.pop();
      if (dist[u] >= maxMoves)
        break;
      for (auto n_w : g[u]) {
        int v = n_w.first, w = n_w.second;
        if (dist[u] + w < dist[v]) {
          dist[v] = w + dist[u];
          pq.push({v, dist[v]});
        }
      }
    }
    int res = 0;
    for (int i = 0; i < n; i++)
      if (dist[i] <= maxMoves)
        res++;
    for (auto &e : edges) {
      int a = dist[e[0]] >= maxMoves ? 0 : min(maxMoves - dist[e[0]], e[2]);
      int b = dist[e[1]] >= maxMoves ? 0 : min(maxMoves - dist[e[1]], e[2]);
      res += min(a + b, e[2]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= edges.length <= min(n * (n - 1) / 2, 10⁴)|
// * |edges[i].length == 3|
// * |0 <= uᵢ < vᵢ < n|
// * There are no multiple edges in the graph.
// * |0 <= cntᵢ <= 10⁴|
// * |0 <= maxMoves <= 10⁹|
// * |1 <= n <= 3000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
//
// The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.

LEETCODE_SOLUTION_UNITTEST(882, ReachableNodesInSubdividedGraph, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {0, 1, 10},
      {0, 2,  1},
      {1, 2,  2}
  };
  int maxMoves = 6;
  int n        = 3;
  int expect   = 13;
  int actual   = solution->reachableNodes(edges, maxMoves, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], maxMoves = 10, n = 4
// Output: 23
//

LEETCODE_SOLUTION_UNITTEST(882, ReachableNodesInSubdividedGraph, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {0, 1, 4},
      {1, 2, 6},
      {0, 2, 8},
      {1, 3, 1}
  };
  int maxMoves = 10;
  int n        = 4;
  int expect   = 23;
  int actual   = solution->reachableNodes(edges, maxMoves, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: edges = [[1,2,4],[1,4,5],[1,3,1],[2,3,4],[3,4,5]], maxMoves = 17, n =
//  5
// Output: 1
//
// Node 0 is disconnected from the rest of the graph, so only node 0 is
// reachable.

LEETCODE_SOLUTION_UNITTEST(882, ReachableNodesInSubdividedGraph, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {1, 2, 4},
      {1, 4, 5},
      {1, 3, 1},
      {2, 3, 4},
      {3, 4, 5}
  };
  int maxMoves = 17;
  int n        = 5;
  int expect   = 1;
  int actual   = solution->reachableNodes(edges, maxMoves, n);
  LCD_EXPECT_EQ(expect, actual);
}
