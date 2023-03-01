// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Restricted Paths From First to Last Node
//
// https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/
//
// Question ID: 1786
// Difficult  : Medium
// Solve Date : 2022/02/10 19:37

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

// Description of |1786. Number of Restricted Paths From First to Last Node|:
//
// There is an undirected weighted connected graph. You are given a positive
// integer |n| which denotes that the graph has |n| nodes labeled from |1| to
// |n|, and an array |edges| where each |edges[i] = [uᵢ, vᵢ, weightᵢ]| denotes
// that there is an edge between nodes |uᵢ| and |vᵢ| with weight equal to
// |weightᵢ|. A path from node |start| to node |end| is a sequence of nodes
// |[z₀, z₁,^{ }z₂, ..., zₖ]| such that |z^{0 }= start| and |zₖ = end| and there
// is an edge between |zᵢ| and |zᵢ₊₁| where |0 <= i <= k-1|. The distance of a
// path is the sum of the weights on the edges of the path. Let
// |distanceToLastNode(x)| denote the shortest distance of a path between node
// |n| and node |x|. A restricted path is a path that also satisfies that
// |distanceToLastNode(zᵢ) > distanceToLastNode(zᵢ₊₁)| where |0 <= i <= k-1|.
// Return the number of restricted paths from node |1| to node |n|. Since that
// number may be too large, return it modulo |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(1786, NumberOfRestrictedPathsFromFirstToLastNode,
                         Solution);

class Solution {
private:
  using ull                            = unsigned long long;
  using pii                            = pair<int, int>;
  using pui                            = pair<unsigned long long, int>;
  static constexpr ull            kMax = numeric_limits<ull>::max();
  static constexpr int            kMod = 1e+9 + 7;
  unordered_map<int, vector<pii>> graph;
  int                             n;

  int dfs(int from, vector<int> &pathes, const vector<ull> &dist) {
    if (pathes[from] == -1) {
      pathes[from] = 0;
      for (const auto &[u, _] : graph[from]) {
        if (dist[u] < dist[from]) {
          pathes[from] = (pathes[from] + dfs(u, pathes, dist)) % kMod;
        }
      }
    }
    return pathes[from];
  }

  vector<ull> djikstra(int beg) noexcept {
    priority_queue<pui, vector<pui>, greater<pui>> pq;
    vector<ull>                                    res(n + 1, kMax);
    pq.emplace(0, beg);
    res[beg] = 0;
    while (!pq.empty()) {
      auto [du, u] = pq.top();
      pq.pop();
      for (auto &[v, dv] : graph[u]) {
        auto dist = dv + res[u];
        if (dist < res[v]) {
          res[v] = dist;
          pq.emplace(dist, v);
        }
      }
    }
    return res;
  }

public:
  int countRestrictedPaths(int n, vector<vector<int>> &edges) {
    this->n = n;
    for (const auto &vs : edges) {
      graph[vs[0]].emplace_back(vs[1], vs[2]);
      graph[vs[1]].emplace_back(vs[0], vs[2]);
    }
    auto        dist = djikstra(n);
    vector<int> pathes(n + 1, -1);
    pathes[n] = 1;
    dfs(1, pathes, dist);
    return pathes[1];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2 * 10⁴|
// * |n - 1 <= edges.length <= 4 * 10⁴|
// * |edges[i].length == 3|
// * |1 <= uᵢ, vᵢ <= n|
// * |u^{i }!= vᵢ|
// * |1 <= weightᵢ <= 10⁵|
// * There is at most one edge between any two nodes.
// * There is at least one path between any two nodes.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges =
//  [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
//
// Each circle contains the node number in black and its |distanceToLastNode
// value in blue. |The three restricted paths are: 1) 1 --> 2 --> 5 2) 1 --> 2
// --> 3 --> 5 3) 1 --> 3 --> 5

LEETCODE_SOLUTION_UNITTEST(1786, NumberOfRestrictedPathsFromFirstToLastNode,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {1, 2,  3},
      {1, 3,  3},
      {2, 3,  1},
      {1, 4,  2},
      {5, 2,  2},
      {3, 5,  1},
      {5, 4, 10}
  };
  int expect = 3;
  int actual = solution->countRestrictedPaths(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, edges =
//  [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
// Output: 1
//
// Each circle contains the node number in black and its |distanceToLastNode
// value in blue. |The only restricted path is 1 --> 3 --> 7.

LEETCODE_SOLUTION_UNITTEST(1786, NumberOfRestrictedPathsFromFirstToLastNode,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {1, 3, 1},
      {4, 1, 2},
      {7, 3, 4},
      {2, 5, 3},
      {5, 6, 1},
      {6, 7, 2},
      {7, 5, 3},
      {2, 6, 4}
  };
  int expect = 1;
  int actual = solution->countRestrictedPaths(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
