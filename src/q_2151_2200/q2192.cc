// Copyright 2024 Naon Lu
//
// This file describes the solution of
// All Ancestors of a Node in a Directed Acyclic Graph
//
// https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/
//
// Question ID: 2192
// Difficult  : Medium
// Solve Date : 2024/06/29 14:36

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2192. All Ancestors of a Node in a Directed Acyclic Graph|:
//
// You are given a positive integer |n| representing the number of nodes of a
// Directed Acyclic Graph (DAG). The nodes are numbered from |0| to |n - 1|
// (inclusive). You are also given a 2D integer array |edges|, where |edges[i] =
// [fromᵢ, toᵢ]| denotes that there is a unidirectional edge from |fromᵢ| to
// |toᵢ| in the graph. Return a list |answer|, where |answer[i]| is the list of
// ancestors of the |iᵗʰ| node, sorted in ascending order. A node |u| is an
// ancestor of another node |v| if |u| can reach |v| via a set of edges.
//
//

LEETCODE_BEGIN_RESOLVING(2192, AllAncestorsOfANodeInADirectedAcyclicGraph,
                         Solution);

class Solution {
public:
  vector<vector<int>> getAncestors(int n, vector<vector<int>> &edges) {
    vector<vector<int>> res(n);
    vector<vector<int>> children(n);
    for (auto &e : edges) {
      children[e[0]].emplace_back(e[1]);
    }
    for (int i = 0; i < n; ++i) {
      dfs(i, i, &res, children);
    }
    return res;
  }

private:
  void dfs(int x, int cur, vector<vector<int>> *res,
           vector<vector<int>> const &children) {
    for (auto ch : children[cur]) {
      if ((*res)[ch].empty() || (*res)[ch].back() != x) {
        (*res)[ch].push_back(x);
        dfs(x, ch, res, children);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |0 <= edges.length <= min(2000, n * (n - 1) / 2)|
// * |edges[i].length == 2|
// * |0 <= fromᵢ, toᵢ <= n - 1|
// * |fromᵢ != toᵢ|
// * There are no duplicate edges.
// * The graph is directed and acyclic.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 8, edgeList =
//  [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
// Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
//

LEETCODE_SOLUTION_UNITTEST(2192, AllAncestorsOfANodeInADirectedAcyclicGraph,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 8;
  vector<vector<int>> edges    = {
      {0, 3},
      {0, 4},
      {1, 3},
      {2, 4},
      {2, 7},
      {3, 5},
      {3, 6},
      {3, 7},
      {4, 6}
  };
  vector<vector<int>> expect = {
      {},
      {},
      {},
      {0, 1},
      {0, 2},
      {0, 1, 3},
      {0, 1, 2, 3, 4},
      {0, 1, 2, 3}
  };
  vector<vector<int>> actual = solution->getAncestors(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, edgeList =
//  [[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// Output: [[],[0],[0,1],[0,1,2],[0,1,2,3]]
//

LEETCODE_SOLUTION_UNITTEST(2192, AllAncestorsOfANodeInADirectedAcyclicGraph,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {0, 3},
      {0, 4},
      {1, 2},
      {1, 3},
      {1, 4},
      {2, 3},
      {2, 4},
      {3, 4}
  };
  vector<vector<int>> expect = {
      {},
      {0},
      {0, 1},
      {0, 1, 2},
      {0, 1, 2, 3}
  };
  vector<vector<int>> actual = solution->getAncestors(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}
