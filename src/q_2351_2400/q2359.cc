// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Closest Node to Given Two Nodes
//
// https://leetcode.com/problems/find-closest-node-to-given-two-nodes/
//
// Question ID: 2359
// Difficult  : Medium
// Solve Date : 2023/01/25 15:48

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2359. Find Closest Node to Given Two Nodes|:
//
// You are given a directed graph of |n| nodes numbered from |0| to |n - 1|,
// where each node has at most one outgoing edge. The graph is represented with
// a given 0-indexed array |edges| of size |n|, indicating that there is a
// directed edge from node |i| to node |edges[i]|. If there is no outgoing edge
// from |i|, then |edges[i] == -1|. You are also given two integers |node1| and
// |node2|. Return the index of the node that can be reached from both |node1|
// and |node2|, such that the maximum between the distance from |node1| to that
// node, and from |node2| to that node is minimized. If there are multiple
// answers, return the node with the smallest index, and if no possible answer
// exists, return |-1|. Note that |edges| may contain cycles.
//

LEETCODE_BEGIN_RESOLVING(2359, FindClosestNodeToGivenTwoNodes, Solution);

class Solution {
private:
  void dfs(vector<int> &e, int node, vector<int> &d, int dis = 0) {
    d[node] = dis;
    if (e[node] != -1 && d[e[node]] == numeric_limits<int>::max()) {
      dfs(e, e[node], d, dis + 1);
    }
  }

public:
  int closestMeetingNode(vector<int> &edges, int node1, int node2) {
    int         n = edges.size();
    vector<int> dis1(n, numeric_limits<int>::max());
    vector<int> dis2(n, numeric_limits<int>::max());
    dfs(edges, node1, dis1);
    dfs(edges, node2, dis2);
    int ans = numeric_limits<int>::max();
    int res = -1;
    for (int i = 0; i < n; ++i) {
      if (max(dis1[i], dis2[i]) < ans) {
        ans = max(dis1[i], dis2[i]);
        res = i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == edges.length|
// * |2 <= n <= 10⁵|
// * |-1 <= edges[i] < n|
// * |edges[i] != i|
// * |0 <= node1, node2 < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
// Output: 2
//
// The distance from node 0 to node 2 is 1, and the distance from node 1 to node
// 2 is 1. The maximum of those two distances is 1. It can be proven that we
// cannot get a node with a smaller maximum distance than 1, so we return
// node 2.

LEETCODE_SOLUTION_UNITTEST(2359, FindClosestNodeToGivenTwoNodes, example_1) {
  auto        solution = MakeSolution();
  vector<int> edges    = {2, 2, 3, -1};
  int         node1    = 0;
  int         node2    = 1;
  int         expect   = 2;
  int         actual   = solution->closestMeetingNode(edges, node1, node2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [1,2,-1], node1 = 0, node2 = 2
// Output: 2
//
// The distance from node 0 to node 2 is 2, and the distance from node 2 to
// itself is 0. The maximum of those two distances is 2. It can be proven that
// we cannot get a node with a smaller maximum distance than 2, so we return
// node 2.

LEETCODE_SOLUTION_UNITTEST(2359, FindClosestNodeToGivenTwoNodes, example_2) {
  auto        solution = MakeSolution();
  vector<int> edges    = {1, 2, -1};
  int         node1    = 0;
  int         node2    = 2;
  int         expect   = 2;
  int         actual   = solution->closestMeetingNode(edges, node1, node2);
  LCD_EXPECT_EQ(expect, actual);
}
