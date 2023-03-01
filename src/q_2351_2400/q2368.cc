// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reachable Nodes With Restrictions
//
// https://leetcode.com/problems/reachable-nodes-with-restrictions/
//
// Question ID: 2368
// Difficult  : Medium
// Solve Date : 2022/10/21 21:32

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2368. Reachable Nodes With Restrictions|:
//
// There is an undirected tree with |n| nodes labeled from |0| to |n - 1| and |n
// - 1| edges. You are given a 2D integer array |edges| of length |n - 1| where
// |edges[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes |aᵢ| and
// |bᵢ| in the tree. You are also given an integer array |restricted| which
// represents restricted nodes. Return the maximum number of nodes you can reach
// from node |0| without visiting a restricted node. Note that node |0| will not
// be a restricted node.
//

LEETCODE_BEGIN_RESOLVING(2368, ReachableNodesWithRestrictions, Solution);

class Solution {
public:
  int reachableNodes(int n, vector<vector<int>> &edges,
                     vector<int> &restricted) {
    auto pth = vector<vector<int>>(n);
    auto vst = vector<bool>(n, false);
    auto rst = unordered_set<int>(restricted.begin(), restricted.end());
    auto cur = queue<int>();

    for (auto &e : edges) {
      pth[e[0]].emplace_back(e[1]);
      pth[e[1]].emplace_back(e[0]);
    }

    if (!rst.count(0)) {
      vst[0] = true;
      cur.emplace(0);
    }

    auto res = (int)0;

    while (!cur.empty()) {
      auto c = cur.front();
      cur.pop();

      ++res;
      for (auto x : pth[c]) {
        if (!vst[x] && !rst.count(x)) {
          vst[x] = true;
          cur.emplace(x);
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |edges| represents a valid tree.
// * |1 <= restricted.length < n|
// * |1 <= restricted[i] < n|
// * All the values of |restricted| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted =
//  [4,5]
// Output: 4
//
// The diagram above shows the tree.
// We have that [0,1,2,3] are the only nodes that can be reached from node 0
// without visiting a restricted node.

LEETCODE_SOLUTION_UNITTEST(2368, ReachableNodesWithRestrictions, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {3, 1},
      {4, 0},
      {0, 5},
      {5, 6}
  };
  vector<int> restricted = {4, 5};
  int         expect     = 4;
  int         actual     = solution->reachableNodes(n, edges, restricted);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, edges = [[0,1],[0,2],[0,5],[0,4],[3,2],[6,5]], restricted =
//  [4,2,1]
// Output: 3
//
// The diagram above shows the tree.
// We have that [0,5,6] are the only nodes that can be reached from node 0
// without visiting a restricted node.

LEETCODE_SOLUTION_UNITTEST(2368, ReachableNodesWithRestrictions, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {0, 5},
      {0, 4},
      {3, 2},
      {6, 5}
  };
  vector<int> restricted = {4, 2, 1};
  int         expect     = 3;
  int         actual     = solution->reachableNodes(n, edges, restricted);
  LCD_EXPECT_EQ(expect, actual);
}
