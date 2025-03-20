// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Cost Walk in Weighted Graph
//
// https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/
//
// Question ID: 3108
// Difficult  : Hard
// Solve Date : 2025/03/20 22:13

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3108. Minimum Cost Walk in Weighted Graph|:
//
// There is an undirected weighted graph with |n| vertices labeled from |0| to
// |n - 1|. You are given the integer |n| and an array |edges|, where |edges[i]
// = [uᵢ, vᵢ, wᵢ]| indicates that there is an edge between vertices |uᵢ| and
// |vᵢ| with a weight of |wᵢ|. A walk on a graph is a sequence of vertices and
// edges. The walk starts and ends with a vertex, and each edge connects the
// vertex that comes before it and the vertex that comes after it. It's
// important to note that a walk may visit the same edge or vertex more than
// once. The cost of a walk starting at node |u| and ending at node |v| is
// defined as the bitwise |AND| of the weights of the edges traversed during the
// walk. In other words, if the sequence of edge weights encountered during the
// walk is |w₀, w₁, w₂, ..., wₖ|, then the cost is calculated as |w₀ & w₁ & w₂ &
// ... & wₖ|, where |&| denotes the bitwise |AND| operator. You are also given a
// 2D array |query|, where |query[i] = [sᵢ, tᵢ]|. For each query, you need to
// find the minimum cost of the walk starting at vertex |sᵢ| and ending at
// vertex |tᵢ|. If there exists no such walk, the answer is |-1|. Return the
// array |answer|, where |answer[i]| denotes the minimum cost of a walk for
// query |i|.
//
//

LEETCODE_BEGIN_RESOLVING(3108, MinimumCostWalkInWeightedGraph, Solution);

class Solution {
public:
  vector<int> minimumCost(int n, vector<vector<int>> &edges,
                          vector<vector<int>> &query) {
    vector<int> parent(n), min_path_cost(n, -1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find_root = [&](int node) {
      if (parent[node] != node) {
        parent[node] = find_root(parent[node]);
      }
      return parent[node];
    };

    for (auto &edge : edges) {
      int source = edge[0], target = edge[1], weight = edge[2];
      int source_root = find_root(source);
      int target_root = find_root(target);

      min_path_cost[target_root] &= weight;

      if (source_root != target_root) {
        min_path_cost[target_root] &= min_path_cost[source_root];
        parent[source_root] = target_root;
      }
    }

    vector<int> result;
    for (auto &q : query) {
      int start = q[0], end = q[1];
      if (start == end) {
        result.push_back(0);
      } else if (find_root(start) != find_root(end)) {
        result.push_back(-1);
      } else {
        result.push_back(min_path_cost[find_root(start)]);
      }
    }
    return result;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |0 <= edges.length <= 10⁵|
// * |edges[i].length == 3|
// * |0 <= uᵢ, vᵢ <= n - 1|
// * |uᵢ != vᵢ|
// * |0 <= wᵢ <= 10⁵|
// * |1 <= query.length <= 10⁵|
// * |query[i].length == 2|
// * |0 <= sᵢ, tᵢ <= n - 1|
// * |sᵢ != tᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
// Output: [1,-1]
//

LEETCODE_SOLUTION_UNITTEST(3108, MinimumCostWalkInWeightedGraph, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1, 7},
      {1, 3, 7},
      {1, 2, 1}
  };
  vector<vector<int>> query = {
      {0, 3},
      {3, 4}
  };
  vector<int> expect = {1, -1};
  vector<int> actual = solution->minimumCost(n, edges, query);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(3108, MinimumCostWalkInWeightedGraph, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 2,  7},
      {0, 1, 15},
      {1, 2,  6},
      {1, 2,  1}
  };
  vector<vector<int>> query = {
      {1, 2}
  };
  vector<int> expect = {0};
  vector<int> actual = solution->minimumCost(n, edges, query);
  LCD_EXPECT_EQ(expect, actual);
}
