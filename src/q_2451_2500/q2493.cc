// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Divide Nodes Into the Maximum Number of Groups
//
// https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/
//
// Question ID: 2493
// Difficult  : Hard
// Solve Date : 2025/01/30 11:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2493. Divide Nodes Into the Maximum Number of Groups|:
//
// You are given a positive integer |n| representing the number of nodes in an
// undirected graph. The nodes are labeled from |1| to |n|. You are also given a
// 2D integer array |edges|, where |edges[i] = [a_{i, }bᵢ]| indicates that there
// is a bidirectional edge between nodes |aᵢ| and |bᵢ|. Notice that the given
// graph may be disconnected. Divide the nodes of the graph into |m| groups
// (1-indexed) such that:
//
//  • Each node in the graph belongs to exactly one group.
//
//  • For every pair of nodes in the graph that are connected by an edge |[a_{i,
//  }bᵢ]|, if |aᵢ| belongs to the group with index |x|, and |bᵢ| belongs to the
//  group with index |y|, then ||y - x| = 1|.
// Return the maximum number of groups (i.e., maximum |m|) into which you can
// divide the nodes. Return |-1| if it is impossible to group the nodes with the
// given conditions.
//
//

LEETCODE_BEGIN_RESOLVING(2493, DivideNodesIntoTheMaximumNumberOfGroups,
                         Solution);

class Solution {
public:
  int magnificentSets(int n, vector<vector<int>> &edges) {
    vector<vector<int>> adj(n);
    for (const auto &e : edges) {
      adj[e[0] - 1].push_back(e[1] - 1);
      adj[e[1] - 1].push_back(e[0] - 1);
    }
    vector<int>         color(n, -1);
    vector<vector<int>> components;
    for (int i = {0}; i < n; ++i) {
      if (color[i] == -1) {
        components.emplace_back();
        if (!dfs(i, 0, adj, color, components.back()))
          return -1;
      }
    }
    int maxGroups = {0};
    for (const auto &comp : components) {
      maxGroups += bfsMaxDepth(comp, adj);
    }
    return maxGroups;
  }

private:
  bool dfs(int node, int col, const vector<vector<int>> &adj,
           vector<int> &color, vector<int> &comp) {
    color[node] = col;
    comp.push_back(node);
    for (int neighbor : adj[node]) {
      if (color[neighbor] == col)
        return false;
      if (color[neighbor] == -1 && !dfs(neighbor, 1 - col, adj, color, comp))
        return false;
    }
    return true;
  }
  int bfsMaxDepth(const vector<int> &comp, const vector<vector<int>> &adj) {
    int maxDepth = {0};
    for (int start : comp) {
      vector<int> depth(adj.size(), -1);
      vector<int> queue = {start};
      depth[start]      = {0};
      for (size_t i = {0}; i < queue.size(); ++i) {
        int node = queue[i];
        for (int neighbor : adj[node]) {
          if (depth[neighbor] == -1) {
            depth[neighbor] = depth[node] + 1;
            queue.push_back(neighbor);
          }
        }
      }
      maxDepth = max(maxDepth, *max_element(depth.begin(), depth.end()));
    }
    return maxDepth + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
// * |1 <= edges.length <= 10⁴|
// * |edges[i].length == 2|
// * |1 <= aᵢ, bᵢ <= n|
// * |aᵢ != bᵢ|
// * There is at most one edge between any pair of vertices.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2493, DivideNodesIntoTheMaximumNumberOfGroups,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {1, 2},
      {1, 4},
      {1, 5},
      {2, 6},
      {2, 3},
      {4, 6}
  };
  int expect = 4;
  int actual = solution->magnificentSets(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, edges = [[1,2],[2,3],[3,1]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2493, DivideNodesIntoTheMaximumNumberOfGroups,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {1, 2},
      {2, 3},
      {3, 1}
  };
  int expect = -1;
  int actual = solution->magnificentSets(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
