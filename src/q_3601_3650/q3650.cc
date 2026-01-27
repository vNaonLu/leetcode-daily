// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Cost Path with Edge Reversals
//
// https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/
//
// Question ID: 3650
// Difficult  : Medium
// Solve Date : 2026/01/27 19:14

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3650. Minimum Cost Path with Edge Reversals|:
//
// You are given a directed, weighted graph with |n| nodes labeled from 0 to |n
// - 1|, and an array |edges| where |edges[i] = [uᵢ, vᵢ, wᵢ]| represents a
// directed edge from node |uᵢ| to node |vᵢ| with cost |wᵢ|. Each node |uᵢ| has
// a switch that can be used at most once: when you arrive at |uᵢ| and have not
// yet used its switch, you may activate it on one of its incoming edges |vᵢ →
// uᵢ| reverse that edge to |uᵢ → vᵢ| and immediately traverse it. The reversal
// is only valid for that single move, and using a reversed edge costs |2 * wᵢ|.
// Return the minimum total cost to travel from node 0 to node |n - 1|. If it is
// not possible, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3650, MinimumCostPathWithEdgeReversals, Solution);

class Solution {
public:
  int minCost(int n, vector<vector<int>> &edges) {
    graph_.resize(n);
    for (auto &e : edges) {
      int u = e[0];
      int v = e[1];
      int w = e[2];
      graph_[u].emplace_back(v, w);
      graph_[v].emplace_back(u, 2 * w);
    }
    return dijkstra(n);
  }

private:
  int dijkstra(int n) {
    vector<bool>                   vis(n, false);
    vector<int>                    dist(n, 1e9);
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;
    while (!pq.empty()) {
      auto [_, u] = pq.top();
      pq.pop();

      if (vis[u]) {
        continue;
      }
      vis[u] = true;

      for (auto &[v, w] : graph_[u]) {
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          pq.emplace(-dist[v], v);
        }
      }
    }
    return dist.back() == 1e9 ? -1 : dist.back();
  }

  vector<vector<pair<int, int>>> graph_;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 5 * 10⁴|
// * |1 <= edges.length <= 10⁵|
// * |edges[i] = [uᵢ, vᵢ, wᵢ]|
// * |0 <= uᵢ, vᵢ <= n - 1|
// * |1 <= wᵢ <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3650, MinimumCostPathWithEdgeReversals, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 1, 3},
      {3, 1, 1},
      {2, 3, 4},
      {0, 2, 2}
  };
  int expect = 5;
  int actual = solution->minCost(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3650, MinimumCostPathWithEdgeReversals, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 2, 1},
      {2, 1, 1},
      {1, 3, 1},
      {2, 3, 3}
  };
  int expect = 3;
  int actual = solution->minCost(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
