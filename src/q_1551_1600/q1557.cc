// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Vertices to Reach All Nodes
//
// https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
//
// Question ID: 1557
// Difficult  : Medium
// Solve Date : 2021/10/07 10:32

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1557. Minimum Number of Vertices to Reach All Nodes|:
//
// Given a directed acyclic graph, with  |n| vertices numbered from  |0| to 
// |n-1|, and an array  |edges| where  |edges[i] = [fromᵢ, toᵢ]| represents a
// directed edge from node  |fromᵢ| to node  |toᵢ|.
//
// Find the smallest set of vertices from which all nodes in the graph are
// reachable. It's guaranteed that a unique solution exists.
//
// Notice that you can return the vertices in any order.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1557, MinimumNumberOfVerticesToReachAllNodes,
                         Solution);

class Solution {
public:
  vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges) {
    unordered_set<int> reachable;
    for (const auto &e : edges)
      reachable.insert(e[1]);
    vector<int> res;
    for (int i = 0; i < n; ++i)
      if (!reachable.count(i))
        res.push_back(i);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10^5|
// * |1 <= edges.length <= min(10^5, n * (n - 1) / 2)|
// * |edges[i].length == 2|
// * |0 <= from^{i,} toᵢ < n|
// * All pairs |(fromᵢ, toᵢ)| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
// Output: [0,3]
// Explanation: It's not possible to reach all the nodes from a single vertex.
// From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output
// [0,3].
//

LEETCODE_SOLUTION_UNITTEST(1557, MinimumNumberOfVerticesToReachAllNodes,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {2, 5},
      {3, 4},
      {4, 2}
  };
  vector<int> expect = {0, 3};
  vector<int> actual = solution->findSmallestSetOfVertices(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
// Output: [0,2,3]
//
// Notice that vertices 0, 3 and 2 are not reachable from any other node, so we
// must include them. Also any of these vertices can reach nodes 1 and 4.

LEETCODE_SOLUTION_UNITTEST(1557, MinimumNumberOfVerticesToReachAllNodes,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1},
      {2, 1},
      {3, 1},
      {1, 4},
      {2, 4}
  };
  vector<int> expect = {0, 2, 3};
  vector<int> actual = solution->findSmallestSetOfVertices(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}
