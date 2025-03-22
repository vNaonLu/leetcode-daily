// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Complete Components
//
// https://leetcode.com/problems/count-the-number-of-complete-components/
//
// Question ID: 2685
// Difficult  : Medium
// Solve Date : 2025/03/22 12:31

#include <iosfwd>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2685. Count the Number of Complete Components|:
//
// You are given an integer |n|. There is an undirected graph with |n| vertices,
// numbered from |0| to |n - 1|. You are given a 2D integer array |edges| where
// |edges[i] = [aᵢ, bᵢ]| denotes that there exists an undirected edge connecting
// vertices |aᵢ| and |bᵢ|. Return the number of complete connected components of
// the graph. A connected component is a subgraph of a graph in which there
// exists a path between any two vertices, and no vertex of the subgraph shares
// an edge with a vertex outside of the subgraph. A connected component is said
// to be complete if there exists an edge between every pair of its vertices.
//
//

LEETCODE_BEGIN_RESOLVING(2685, CountTheNumberOfCompleteComponents, Solution);

class Solution {
public:
  int countCompleteComponents(int n, vector<vector<int>> &edges) {
    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) {
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    };

    auto unionSets = [&](int x, int y) {
      int rootX = find(x);
      int rootY = find(y);
      if (rootX == rootY)
        return;
      if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else {
        parent[rootY] = rootX;
        rank[rootX]++;
      }
    };

    for (auto &edge : edges) {
      unionSets(edge[0], edge[1]);
    }

    unordered_map<int, unordered_set<int>> componentVertices;
    unordered_map<int, int>                componentEdges;

    for (int i = 0; i < n; ++i) {
      int root = find(i);
      componentVertices[root].insert(i);
    }

    for (auto &edge : edges) {
      int root = find(edge[0]);
      componentEdges[root]++;
    }

    int completeCount = 0;
    for (auto &[root, vertices] : componentVertices) {
      int numVertices   = vertices.size();
      int expectedEdges = numVertices * (numVertices - 1) / 2;
      if (componentEdges[root] == expectedEdges) {
        completeCount++;
      }
    }

    return completeCount;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 50|
// * |0 <= edges.length <= n * (n - 1) / 2|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
// * There are no repeated edges.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2685, CountTheNumberOfCompleteComponents,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 2},
      {3, 4}
  };
  int expect = 3;
  int actual = solution->countCompleteComponents(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2685, CountTheNumberOfCompleteComponents,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 2},
      {3, 4},
      {3, 5}
  };
  int expect = 1;
  int actual = solution->countCompleteComponents(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
