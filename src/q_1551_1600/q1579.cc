// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Max Number of Edges to Keep Graph Fully Traversable
//
// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
//
// Question ID: 1579
// Difficult  : Hard
// Solve Date : 2023/04/30 15:05

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1579. Remove Max Number of Edges to Keep Graph Fully
// Traversable|:
//
// Alice and Bob have an undirected graph of |n| nodes and three types of edges:
//
//  • Type 1: Can be traversed by Alice only.
//
//  • Type 2: Can be traversed by Bob only.
//
//  • Type 3: Can be traversed by both Alice and Bob.
// Given an array |edges| where |edges[i] = [typeᵢ, uᵢ, vᵢ]| represents a
// bidirectional edge of type |typeᵢ| between nodes |uᵢ| and |vᵢ|, find the
// maximum number of edges you can remove so that after removing the edges, the
// graph can still be fully traversed by both Alice and Bob. The graph is fully
// traversed by Alice and Bob if starting from any node, they can reach all
// other nodes. Return the maximum number of edges you can remove, or return
// |-1| if Alice and Bob cannot fully traverse the graph.
//
//

LEETCODE_BEGIN_RESOLVING(1579,
                         RemoveMaxNumberOfEdgesToKeepGraphFullyTraversable,
                         Solution);

class Solution {
public:
  int maxNumEdgesToRemove(int n, vector<vector<int>> &edges) {
    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b) { return a[0] > b[0]; });
    Dsu alice(n + 1);
    Dsu bob(n + 1);
    int removed_edge = 0;
    int alice_edge   = 0;
    int bob_edge     = 0;
    for (auto &e : edges) {
      if (e[0] == 3) {
        if (alice.Union(e[1], e[2])) {
          bob.Union(e[1], e[2]);
          ++alice_edge;
          ++bob_edge;
        } else {
          ++removed_edge;
        }
      } else if (e[0] == 2) {
        if (bob.Union(e[1], e[2])) {
          ++bob_edge;
        } else {
          ++removed_edge;
        }
      } else {
        if (alice.Union(e[1], e[2])) {
          ++alice_edge;
        } else {
          ++removed_edge;
        }
      }
    }
    return (bob_edge == n - 1 && alice_edge == n - 1) ? removed_edge : -1;
  }

private:
  class Dsu {
  public:
    explicit Dsu(int n) : parent(n), rank(n) {
      for (int i = 0; i < n; ++i) {
        parent[i] = i;
      }
    }

    int Find(int x) { return parent[x] = parent[x] == x ? x : Find(parent[x]); }

    bool Union(int x, int y) {
      int xset = Find(x);
      int yset = Find(y);
      if (xset != yset) {
        if (rank[xset] < rank[yset]) {
          parent[xset] = yset;
        } else {
          parent[yset] = xset;
        }
        rank[xset] += rank[xset] == rank[yset];
        return true;
      }
      return false;
    }

  private:
    vector<int> parent;
    vector<int> rank;
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |1 <= edges.length <= min(10⁵, 3 * n * (n - 1) / 2)|
// * |edges[i].length == 3|
// * |1 <= typeᵢ <= 3|
// * |1 <= uᵢ < vᵢ <= n|
// * All tuples |(typeᵢ, uᵢ, vᵢ)| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
// Output: 2
//
// If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully
// traversable by Alice and Bob. Removing any additional edge will not make it
// so. So the maximum number of edges we can remove is 2.

LEETCODE_SOLUTION_UNITTEST(1579,
                           RemoveMaxNumberOfEdgesToKeepGraphFullyTraversable,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {3, 1, 2},
      {3, 2, 3},
      {1, 1, 3},
      {1, 2, 4},
      {1, 1, 2},
      {2, 3, 4}
  };
  int expect = 2;
  int actual = solution->maxNumEdgesToRemove(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
// Output: 0
//
// Notice that removing any edge will not make the graph fully traversable by
// Alice and Bob.

LEETCODE_SOLUTION_UNITTEST(1579,
                           RemoveMaxNumberOfEdgesToKeepGraphFullyTraversable,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {3, 1, 2},
      {3, 2, 3},
      {1, 1, 4},
      {2, 1, 4}
  };
  int expect = 0;
  int actual = solution->maxNumEdgesToRemove(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
// Output: -1
//
// In the current graph, Alice cannot reach node 4 from the other nodes.
// Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph
// fully traversable.

LEETCODE_SOLUTION_UNITTEST(1579,
                           RemoveMaxNumberOfEdgesToKeepGraphFullyTraversable,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {3, 2, 3},
      {1, 1, 2},
      {2, 3, 4}
  };
  int expect = -1;
  int actual = solution->maxNumEdgesToRemove(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 2
// [[1,1,2],[2,1,2],[3,1,2]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1579,
                           RemoveMaxNumberOfEdgesToKeepGraphFullyTraversable,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> edges    = {
      {1, 1, 2},
      {2, 1, 2},
      {3, 1, 2}
  };
  int expect = 2;
  int actual = solution->maxNumEdgesToRemove(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
