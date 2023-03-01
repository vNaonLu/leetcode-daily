// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reorder Routes to Make All Paths Lead to the City Zero
//
// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
//
// Question ID: 1466
// Difficult  : Medium
// Solve Date : 2022/03/19 15:09

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1466. Reorder Routes to Make All Paths Lead to the City
// Zero|:
//
// There are |n| cities numbered from |0| to |n - 1| and |n - 1| roads such that
// there is only one way to travel between two different cities (this network
// form a tree). Last year, The ministry of transport decided to orient the
// roads in one direction because they are too narrow. Roads are represented by
// |connections| where |connections[i] = [aᵢ, bᵢ]| represents a road from city
// |aᵢ| to city |bᵢ|. This year, there will be a big event in the capital (city
// |0|), and many people want to travel to this city. Your task consists of
// reorienting some roads such that each city can visit the city |0|. Return the
// minimum number of edges changed. It's guaranteed that each city can reach
// city |0| after reorder.  
//

LEETCODE_BEGIN_RESOLVING(1466, ReorderRoutesToMakeAllPathsLeadToTheCityZero,
                         Solution);

class Solution {
private:
  set<pair<int, int>> path;
  vector<vector<int>> adj;
  int                 res;

  inline void dfs(vector<int> &visited, int curr) {
    visited[curr] = 1;

    for (auto &x : adj[curr]) {
      if (!visited[x]) {
        dfs(visited, x);
        if (path.count(make_pair(curr, x))) {
          ++res;
        }
      }
    }
  }

public:
  int minReorder(int n, vector<vector<int>> &connections) {
    adj.resize(n);
    res = 0;

    for (auto &v : connections) {
      adj[v[0]].emplace_back(v[1]);
      adj[v[1]].emplace_back(v[0]);
      path.emplace(v[0], v[1]);
    }

    vector<int> visited(n, 0);
    dfs(visited, 0);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 5 * 10⁴|
// * |connections.length == n - 1|
// * |connections[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
// Output: 3
//
// Change the direction of edges show in red such that each node can reach the
// node 0 (capital).

LEETCODE_SOLUTION_UNITTEST(1466, ReorderRoutesToMakeAllPathsLeadToTheCityZero,
                           example_1) {
  auto                solution    = MakeSolution();
  int                 n           = 6;
  vector<vector<int>> connections = {
      {0, 1},
      {1, 3},
      {2, 3},
      {4, 0},
      {4, 5}
  };
  int expect = 3;
  int actual = solution->minReorder(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
// Output: 2
//
// Change the direction of edges show in red such that each node can reach the
// node 0 (capital).

LEETCODE_SOLUTION_UNITTEST(1466, ReorderRoutesToMakeAllPathsLeadToTheCityZero,
                           example_2) {
  auto                solution    = MakeSolution();
  int                 n           = 5;
  vector<vector<int>> connections = {
      {1, 0},
      {1, 2},
      {3, 2},
      {3, 4}
  };
  int expect = 2;
  int actual = solution->minReorder(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, connections = [[1,0],[2,0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1466, ReorderRoutesToMakeAllPathsLeadToTheCityZero,
                           example_3) {
  auto                solution    = MakeSolution();
  int                 n           = 3;
  vector<vector<int>> connections = {
      {1, 0},
      {2, 0}
  };
  int expect = 0;
  int actual = solution->minReorder(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}
