// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximize Spanning Tree Stability with Upgrades
//
// https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/
//
// Question ID: 3600
// Difficult  : Hard
// Solve Date : 2026/03/12 19:09

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3600. Maximize Spanning Tree Stability with Upgrades|:
//
// You are given an integer |n|, representing |n| nodes numbered from 0 to |n -
// 1| and a list of |edges|, where |edges[i] = [uᵢ, vᵢ, sᵢ, mustᵢ]|:
//
//  • |uᵢ| and |vᵢ| indicates an undirected edge between nodes |uᵢ| and |vᵢ|.
//
//  • |sᵢ| is the strength of the edge.
//
//  • |mustᵢ| is an integer (0 or 1). If |mustᵢ == 1|, the edge must be included
//  in the spanning tree. These edges cannot be upgraded.
// You are also given an integer |k|, the maximum number of upgrades you can
// perform. Each upgrade doubles the strength of an edge, and each eligible edge
// (with |mustᵢ == 0|) can be upgraded at most once. The stability of a spanning
// tree is defined as the minimum strength score among all edges included in it.
// Return the maximum possible stability of any valid spanning tree. If it is
// impossible to connect all nodes, return |-1|. Note: A spanning tree of a
// graph with |n| nodes is a subset of the edges that connects all nodes
// together (i.e. the graph is connected) without forming any cycles, and uses
// exactly |n - 1| edges.
//
//

LEETCODE_BEGIN_RESOLVING(3600, MaximizeSpanningTreeStabilityWithUpgrades,
                         Solution);

class Solution {
public:
  bool canAchieve(int n, vector<vector<int>> &edges, int k, int x) {
    DSU dsu(n);

    for (auto &e : edges) {
      int u = e[0], v = e[1], s = e[2], must = e[3];

      if (must == 1) {
        if (s < x)
          return false;
        if (!dsu.unite(u, v))
          return false;
      }
    }

    for (auto &e : edges) {
      int u = e[0], v = e[1], s = e[2], must = e[3];

      if (must == 0 && s >= x) {
        dsu.unite(u, v);
      }
    }

    int usedUpgrades = 0;

    for (auto &e : edges) {
      int u = e[0], v = e[1], s = e[2], must = e[3];

      if (must == 0 && s < x && 2 * s >= x) {
        if (dsu.unite(u, v)) {
          usedUpgrades++;
          if (usedUpgrades > k)
            return false;
        }
      }
    }

    return dsu.components == 1;
  }

  int maxStability(int n, vector<vector<int>> &edges, int k) {
    {
      DSU dsu(n);
      for (auto &e : edges) {
        if (e[3] == 1) {
          if (!dsu.unite(e[0], e[1]))
            return -1;
        }
      }
    }

    int low = 1, high = 200000, ans = -1;

    while (low <= high) {
      int mid = low + (high - low) / 2;

      if (canAchieve(n, edges, k, mid)) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return ans;
  }

private:
  class DSU {
  public:
    vector<int> parent, rankv;
    int         components;

    DSU(int n) {
      parent.resize(n);
      rankv.assign(n, 0);
      iota(parent.begin(), parent.end(), 0);
      components = n;
    }

    int find(int x) {
      if (parent[x] != x)
        parent[x] = find(parent[x]);
      return parent[x];
    }

    bool unite(int a, int b) {
      a = find(a);
      b = find(b);

      if (a == b)
        return false;

      if (rankv[a] < rankv[b])
        swap(a, b);
      parent[b] = a;
      if (rankv[a] == rankv[b])
        rankv[a]++;

      components--;
      return true;
    }
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= edges.length <= 10⁵|
// * |edges[i] = [uᵢ, vᵢ, sᵢ, mustᵢ]|
// * |0 <= uᵢ, vᵢ < n|
// * |uᵢ != vᵢ|
// * |1 <= sᵢ <= 10⁵|
// * |mustᵢ| is either |0| or |1|.
// * |0 <= k <= n|
// * There are no duplicate edges.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edges = [[0,1,2,1],[1,2,3,0]], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3600, MaximizeSpanningTreeStabilityWithUpgrades,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1, 2, 1},
      {1, 2, 3, 0}
  };
  int k      = 1;
  int expect = 2;
  int actual = solution->maxStability(n, edges, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, edges = [[0,1,4,0],[1,2,3,0],[0,2,1,0]], k = 2
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3600, MaximizeSpanningTreeStabilityWithUpgrades,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1, 4, 0},
      {1, 2, 3, 0},
      {0, 2, 1, 0}
  };
  int k      = 2;
  int expect = 6;
  int actual = solution->maxStability(n, edges, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, edges = [[0,1,1,1],[1,2,1,1],[2,0,1,1]], k = 0
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3600, MaximizeSpanningTreeStabilityWithUpgrades,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1, 1, 1},
      {1, 2, 1, 1},
      {2, 0, 1, 1}
  };
  int k      = 0;
  int expect = -1;
  int actual = solution->maxStability(n, edges, k);
  LCD_EXPECT_EQ(expect, actual);
}
