// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Eventual Safe States
//
// https://leetcode.com/problems/find-eventual-safe-states/
//
// Question ID: 802
// Difficult  : Medium
// Solve Date : 2022/03/18 18:54

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |802. Find Eventual Safe States|:
//
// There is a directed graph of |n| nodes with each node labeled from |0| to |n
// - 1|. The graph is represented by a 0-indexed 2D integer array |graph| where
// |graph[i]| is an integer array of nodes adjacent to node |i|, meaning there
// is an edge from node |i| to each node in |graph[i]|. A node is a terminal
// node if there are no outgoing edges. A node is a safe node if every possible
// path starting from that node leads to a terminal node (or another safe node).
// Return an array containing all the safe nodes of the graph. The answer should
// be sorted in ascending order.  
//

LEETCODE_BEGIN_RESOLVING(802, FindEventualSafeStates, Solution);

class Solution {
public:
  vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
    vector<int>                res, safe(graph.size(), 0);
    vector<unordered_set<int>> g(graph.size()), rg(graph.size());
    queue<int>                 q;

    for (int i = 0; i < graph.size(); ++i) {
      if (graph[i].empty()) {
        q.emplace(i);
      } else {
        for (auto &x : graph[i]) {
          g[i].insert(x);
          rg[x].insert(i);
        }
      }
    }

    while (!q.empty()) {
      int x = q.front();
      q.pop();
      safe[x] = 1;
      for (auto &y : rg[x]) {
        g[y].erase(x);
        if (g[y].empty()) {
          q.emplace(y);
        }
      }
    }

    for (int i = 0; i < safe.size(); ++i) {
      if (safe[i] != 0) {
        res.emplace_back(i);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == graph.length|
// * |1 <= n <= 10⁴|
// * |0 <= graph[i].length <= n|
// * |0 <= graph[i][j] <= n - 1|
// * |graph[i]| is sorted in a strictly increasing order.
// * The graph may contain self-loops.
// * The number of edges in the graph will be in the range |[1, 4 * 10⁴]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Output: [2,4,5,6]
//
// The given graph is shown above.
// Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either
// of them. Every path starting at nodes 2, 4, 5, and 6 all lead to either node
// 5 or 6.

LEETCODE_SOLUTION_UNITTEST(802, FindEventualSafeStates, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 2},
      {2, 3},
      {5},
      {0},
      {5},
      {},
      {}
  };
  vector<int> expect = {2, 4, 5, 6};
  vector<int> actual = solution->eventualSafeNodes(graph);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
// Output: [4]
//
// Only node 4 is a terminal node, and every path starting at node 4 leads to
// node 4.

LEETCODE_SOLUTION_UNITTEST(802, FindEventualSafeStates, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 2, 3, 4},
      {1, 2},
      {3, 4},
      {0, 4},
      {}
  };
  vector<int> expect = {4};
  vector<int> actual = solution->eventualSafeNodes(graph);
  LCD_EXPECT_EQ(expect, actual);
}
