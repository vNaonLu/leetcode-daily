// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Critical Connections in a Network
//
// https://leetcode.com/problems/critical-connections-in-a-network/
//
// Question ID: 1192
// Difficult  : Hard
// Solve Date : 2022/05/18 18:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1192. Critical Connections in a Network|:
//
// There are |n| servers numbered from |0| to |n - 1| connected by undirected
// server-to-server |connections| forming a network where |connections[i] = [aᵢ,
// bᵢ]| represents a connection between servers |aᵢ| and |bᵢ|. Any server can
// reach other servers directly or indirectly through the network. A critical
// connection is a connection that, if removed, will make some servers unable to
// reach some other server. Return all critical connections in the network in
// any order.
//

LEETCODE_BEGIN_RESOLVING(1192, CriticalConnectionsInANetwork, Solution);

class Solution {
private:
  vector<vector<int>> res;
  vector<vector<int>> graph;

  vector<int> first_time, min_time, visited;
  int         time = 1;

  void helper(int node, int parent = -1) {
    first_time[node] = min_time[node] = time++;
    visited[node]                     = true;

    for (auto next : graph[node]) {
      if (next == parent) {
        continue;
      }

      if (!visited[next]) {
        helper(next, node);
      }

      min_time[node] = min(min_time[node], min_time[next]);

      if (first_time[node] < min_time[next]) {
        res.emplace_back(vector<int>{node, next});
      }
    }
  }

public:
  vector<vector<int>> criticalConnections(int                  n,
                                          vector<vector<int>> &connections) {
    first_time.resize(n, 0);
    min_time.resize(n, 0);
    visited.resize(n, 0);
    graph.resize(n);

    for (auto &b : connections) {
      graph[b[0]].emplace_back(b[1]);
      graph[b[1]].emplace_back(b[0]);
    }

    helper(0);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |n - 1 <= connections.length <= 10⁵|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
// * There are no repeated connections.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
//
// [[3,1]] is also accepted.

LEETCODE_SOLUTION_UNITTEST(1192, CriticalConnectionsInANetwork, example_1) {
  auto                solution    = MakeSolution();
  int                 n           = 4;
  vector<vector<int>> connections = {
      {0, 1},
      {1, 2},
      {2, 0},
      {1, 3}
  };
  vector<vector<int>> expect = {
      {1, 3}
  };
  vector<vector<int>> actual = solution->criticalConnections(n, connections);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, connections = [[0,1]]
// Output: [[0,1]]
//

LEETCODE_SOLUTION_UNITTEST(1192, CriticalConnectionsInANetwork, example_2) {
  auto                solution    = MakeSolution();
  int                 n           = 2;
  vector<vector<int>> connections = {
      {0, 1}
  };
  vector<vector<int>> expect = {
      {0, 1}
  };
  vector<vector<int>> actual = solution->criticalConnections(n, connections);
  EXPECT_ANYORDER_EQ(expect, actual);
}
