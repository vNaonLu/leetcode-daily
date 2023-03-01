// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Operations to Make Network Connected
//
// https://leetcode.com/problems/number-of-operations-to-make-network-connected/
//
// Question ID: 1319
// Difficult  : Medium
// Solve Date : 2022/03/17 18:22

#include <iosfwd>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1319. Number of Operations to Make Network Connected|:
//
// There are |n| computers numbered from |0| to |n - 1| connected by ethernet
// cables |connections| forming a network where |connections[i] = [aᵢ, bᵢ]|
// represents a connection between computers |aᵢ| and |bᵢ|. Any computer can
// reach any other computer directly or indirectly through the network. You are
// given an initial computer network |connections|. You can extract certain
// cables between two directly connected computers, and place them between any
// pair of disconnected computers to make them directly connected. Return the
// minimum number of times you need to do this in order to make all the
// computers connected. If it is not possible, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(1319, NumberOfOperationsToMakeNetworkConnected,
                         Solution);

class Solution {
public:
  int makeConnected(int n, vector<vector<int>> &connections) {
    if (n - 1 > connections.size())
      return -1;

    unordered_map<int, unordered_set<int>> graph;
    unordered_set<int>                     visited;
    int                                    res = 0;

    for (const auto &v : connections) {
      auto x = v[0], y = v[1];
      graph[x].insert(y);
      graph[y].insert(x);
    }

    for (int i = 0; i < n; ++i) {
      if (visited.emplace(i).second) {
        queue<int> q;
        q.emplace(i);

        ++res;
        while (!q.empty()) {
          auto x = q.front();
          q.pop();
          for (const auto &y : graph[x]) {
            if (visited.emplace(y).second) {
              q.emplace(y);
            }
          }
        }
      }
    }
    return --res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |1 <= connections.length <= min(n * (n - 1) / 2, 10⁵)|
// * |connections[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * There are no repeated connections.
// * No two computers are connected by more than one cable.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, connections = [[0,1],[0,2],[1,2]]
// Output: 1
//
// Remove cable between computer 1 and 2 and place between computers 1 and 3.

LEETCODE_SOLUTION_UNITTEST(1319, NumberOfOperationsToMakeNetworkConnected,
                           example_1) {
  auto                solution    = MakeSolution();
  int                 n           = 4;
  vector<vector<int>> connections = {
      {0, 1},
      {0, 2},
      {1, 2}
  };
  int expect = 1;
  int actual = solution->makeConnected(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1319, NumberOfOperationsToMakeNetworkConnected,
                           example_2) {
  auto                solution    = MakeSolution();
  int                 n           = 6;
  vector<vector<int>> connections = {
      {0, 1},
      {0, 2},
      {0, 3},
      {1, 2},
      {1, 3}
  };
  int expect = 2;
  int actual = solution->makeConnected(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
// Output: -1
//
// There are not enough cables.

LEETCODE_SOLUTION_UNITTEST(1319, NumberOfOperationsToMakeNetworkConnected,
                           example_3) {
  auto                solution    = MakeSolution();
  int                 n           = 6;
  vector<vector<int>> connections = {
      {0, 1},
      {0, 2},
      {0, 3},
      {1, 2}
  };
  int expect = -1;
  int actual = solution->makeConnected(n, connections);
  LCD_EXPECT_EQ(expect, actual);
}
