// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
//
// https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
//
// Question ID: 1489
// Difficult  : Hard
// Solve Date : 2023/08/19 11:40

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1489. Find Critical and Pseudo-Critical Edges in Minimum
// Spanning Tree|:
//
// Given a weighted undirected connected graph with |n| vertices numbered from
// |0| to |n - 1|, and an array |edges| where |edges[i] = [aᵢ, bᵢ, weightᵢ]|
// represents a bidirectional and weighted edge between nodes |aᵢ| and |bᵢ|. A
// minimum spanning tree (MST) is a subset of the graph's edges that connects
// all vertices without cycles and with the minimum possible total edge weight.
// Find all the critical and pseudo-critical edges in the given graph's minimum
// spanning tree (MST). An MST edge whose deletion from the graph would cause
// the MST weight to increase is called a critical edge. On the other hand, a
// pseudo-critical edge is that which can appear in some MSTs but not all. Note
// that you can return the indices of the edges in any order.
//
//

LEETCODE_BEGIN_RESOLVING(
    1489, FindCriticalAndPseudoCriticalEdgesInMinimumSpanningTree, Solution);

class Solution {
public:
  class DSU {
    vector<int> parent, size;

  public:
    DSU(int n) {
      parent.resize(n);
      size.resize(n, 1);
      for (int i = 0; i < n; ++i) {
        parent[i] = i;
      }
    }

    int find(int x) {
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }

    bool unite(int x, int y) {
      int rootX = find(x);
      int rootY = find(y);
      if (rootX == rootY) {
        return false;
      }

      if (size[rootX] < size[rootY]) {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
      } else {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
      }

      return true;
    }

    int getSize(int x) { return size[find(x)]; }
  };

  vector<vector<int>>
  findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges) {
    int m = edges.size();
    for (int i = 0; i < m; ++i) {
      edges[i].push_back(i);
    }
    sort(
        edges.begin(), edges.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[2] < b[2]; });

    DSU dsu(n);
    int mst_weight = 0;
    for (int i = 0; i < m; ++i) {
      if (dsu.unite(edges[i][0], edges[i][1])) {
        mst_weight += edges[i][2];
      }
    }

    vector<int> critical, pseudo_critical;
    for (int i = 0; i < m; ++i) {
      DSU tmp(n);
      int weight_without = 0;
      for (int j = 0; j < m; ++j) {
        if (i != j && tmp.unite(edges[j][0], edges[j][1])) {
          weight_without += edges[j][2];
        }
      }

      if (tmp.getSize(0) != n || weight_without > mst_weight) {
        critical.push_back(edges[i][3]);
      } else {
        DSU new_dsu(n);
        new_dsu.unite(edges[i][0], edges[i][1]);
        int weight_with = edges[i][2];
        for (int j = 0; j < m; ++j) {
          if (i != j && new_dsu.unite(edges[j][0], edges[j][1]))
            weight_with += edges[j][2];
        }

        if (weight_with == mst_weight) {
          pseudo_critical.push_back(edges[i][3]);
        }
      }
    }

    return {critical, pseudo_critical};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 100|
// * |1 <= edges.length <= min(200, n * (n - 1) / 2)|
// * |edges[i].length == 3|
// * |0 <= aᵢ < bᵢ < n|
// * |1 <= weightᵢ <= 1000|
// * All pairs |(aᵢ, bᵢ)| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges =
//  [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
//
// The figure above describes the graph.
// The following figure shows all the possible MSTs:
// ![img](https://assets.leetcode.com/uploads/2020/06/04/msts.png)
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are
// critical edges, so we return them in the first list of the output. The edges
// 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered
// pseudo-critical edges. We add them to the second list of the output.

LEETCODE_SOLUTION_UNITTEST(
    1489, FindCriticalAndPseudoCriticalEdgesInMinimumSpanningTree, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1, 1},
      {1, 2, 1},
      {2, 3, 2},
      {0, 3, 2},
      {0, 4, 3},
      {3, 4, 3},
      {1, 4, 6}
  };
  vector<vector<int>> expect = {
      {0, 1},
      {2, 3, 4, 5}
  };
  vector<vector<int>> actual =
      solution->findCriticalAndPseudoCriticalEdges(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
// Output: [[],[0,1,2,3]]
//
// We can observe that since all 4 edges have equal weight, choosing any 3 edges
// from the given 4 will yield an MST. Therefore all 4 edges are
// pseudo-critical.

LEETCODE_SOLUTION_UNITTEST(
    1489, FindCriticalAndPseudoCriticalEdgesInMinimumSpanningTree, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 1, 1},
      {1, 2, 1},
      {2, 3, 1},
      {0, 3, 1}
  };
  vector<vector<int>> expect = {
      {},
      {0, 1, 2, 3}
  };
  vector<vector<int>> actual =
      solution->findCriticalAndPseudoCriticalEdges(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}
