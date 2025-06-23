// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximize the Number of Target Nodes After Connecting Trees I
//
// https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/
//
// Question ID: 3372
// Difficult  : Medium
// Solve Date : 2025/05/28 19:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3372. Maximize the Number of Target Nodes After Connecting
// Trees I|:
//
// There exist two undirected trees with |n| and |m| nodes, with distinct labels
// in ranges |[0, n - 1]| and |[0, m - 1]|, respectively. You are given two 2D
// integer arrays |edges1| and |edges2| of lengths |n - 1| and |m - 1|,
// respectively, where |edges1[i] = [aᵢ, bᵢ]| indicates that there is an edge
// between nodes |aᵢ| and |bᵢ| in the first tree and |edges2[i] = [uᵢ, vᵢ]|
// indicates that there is an edge between nodes |uᵢ| and |vᵢ| in the second
// tree. You are also given an integer |k|. Node |u| is target to node |v| if
// the number of edges on the path from |u| to |v| is less than or equal to |k|.
// Note that a node is always target to itself. Return an array of |n| integers
// |answer|, where |answer[i]| is the maximum possible number of nodes target to
// node |i| of the first tree if you have to connect one node from the first
// tree to another node in the second tree. Note that queries are independent
// from each other. That is, for every query you will remove the added edge
// before proceeding to the next query.
//
//

LEETCODE_BEGIN_RESOLVING(3372,
                         MaximizeTheNumberOfTargetNodesAfterConnectingTreesI,
                         Solution);

class Solution {
public:
  vector<int> maxTargetNodes(vector<vector<int>> &edges1,
                             vector<vector<int>> &edges2, int k) {
    auto        adj1 = build(edges1);
    auto        adj2 = build(edges2);
    int         n    = adj1.size();
    int         m    = adj2.size();
    int         mx   = 0;
    vector<int> res(n);
    for (int i = 0; i < m; ++i) {
      mx = max(mx, dfs(adj2, i, -1, k - 1));
    }
    for (int i = 0; i < n; ++i) {
      res[i] = dfs(adj1, i, -1, k) + mx;
    }
    return res;
  }

private:
  vector<vector<int>> build(auto const &v) {
    vector<vector<int>> res(v.size() + 1);
    for (auto &e : v) {
      res[e[0]].emplace_back(e[1]);
      res[e[1]].emplace_back(e[0]);
    }
    return res;
  }

  int dfs(auto const &v, int u, int p, int k) {
    if (k < 0) {
      return 0;
    }

    int res = 1;
    for (int x : v[u]) {
      if (x != p) {
        res += dfs(v, x, u, k - 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n, m <= 1000|
// * |edges1.length == n - 1|
// * |edges2.length == m - 1|
// * |edges1[i].length == edges2[i].length == 2|
// * |edges1[i] = [aᵢ, bᵢ]|
// * |0 <= aᵢ, bᵢ < n|
// * |edges2[i] = [uᵢ, vᵢ]|
// * |0 <= uᵢ, vᵢ < m|
// * The input is generated such that |edges1| and |edges2| represent valid
// trees.
// * |0 <= k <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 =
//  [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
// Output: [9,7,9,8,8]
//

LEETCODE_SOLUTION_UNITTEST(3372,
                           MaximizeTheNumberOfTargetNodesAfterConnectingTreesI,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges1   = {
      {0, 1},
      {0, 2},
      {2, 3},
      {2, 4}
  };
  vector<vector<int>> edges2 = {
      {0, 1},
      {0, 2},
      {0, 3},
      {2, 7},
      {1, 4},
      {4, 5},
      {4, 6}
  };
  int         k      = 2;
  vector<int> expect = {9, 7, 9, 8, 8};
  vector<int> actual = solution->maxTargetNodes(edges1, edges2, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k =
//  1
// Output: [6,3,3,3,3]
//

LEETCODE_SOLUTION_UNITTEST(3372,
                           MaximizeTheNumberOfTargetNodesAfterConnectingTreesI,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges1   = {
      {0, 1},
      {0, 2},
      {0, 3},
      {0, 4}
  };
  vector<vector<int>> edges2 = {
      {0, 1},
      {1, 2},
      {2, 3}
  };
  int         k      = 1;
  vector<int> expect = {6, 3, 3, 3, 3};
  vector<int> actual = solution->maxTargetNodes(edges1, edges2, k);
  LCD_EXPECT_EQ(expect, actual);
}
