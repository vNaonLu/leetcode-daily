// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximal Network Rank
//
// https://leetcode.com/problems/maximal-network-rank/
//
// Question ID: 1615
// Difficult  : Medium
// Solve Date : 2022/03/23 18:34

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1615. Maximal Network Rank|:
//
// There is an infrastructure of |n| cities with some number of |roads|
// connecting these cities. Each |roads[i] = [aᵢ, bᵢ]| indicates that there is a
// bidirectional road between cities |aᵢ| and |bᵢ|. The network rank of two
// different cities is defined as the total number of directly connected roads
// to either city. If a road is directly connected to both cities, it is only
// counted once. The maximal network rank of the infrastructure is the maximum
// network rank of all pairs of different cities. Given the integer |n| and the
// array |roads|, return the maximal network rank of the entire infrastructure.
//  
//

LEETCODE_BEGIN_RESOLVING(1615, MaximalNetworkRank, Solution);

class Solution {
public:
  int maximalNetworkRank(int n, vector<vector<int>> &roads) {
    vector<unordered_set<int>> graph(n);

    for (auto &v : roads) {
      graph[v[0]].emplace(v[1]);
      graph[v[1]].emplace(v[0]);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j)
          continue;

        res = max<int>(res, graph[i].size() + graph[j].size() -
                                (graph[i].count(j) ? 1 : 0));
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 100|
// * |0 <= roads.length <= n * (n - 1) / 2|
// * |roads[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n-1|
// * |aᵢ != bᵢ|
// * Each pair of cities has at most one road connecting them.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
// Output: 4
//
// The network rank of cities 0 and 1 is 4 as there are 4 roads that are
// connected to either 0 or 1. The road between 0 and 1 is only counted once.

LEETCODE_SOLUTION_UNITTEST(1615, MaximalNetworkRank, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> roads    = {
      {0, 1},
      {0, 3},
      {1, 2},
      {1, 3}
  };
  int expect = 4;
  int actual = solution->maximalNetworkRank(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
// Output: 5
//
// There are 5 roads that are connected to cities 1 or 2.

LEETCODE_SOLUTION_UNITTEST(1615, MaximalNetworkRank, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> roads    = {
      {0, 1},
      {0, 3},
      {1, 2},
      {1, 3},
      {2, 3},
      {2, 4}
  };
  int expect = 5;
  int actual = solution->maximalNetworkRank(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
// Output: 5
//
// The network rank of 2 and 5 is 5. Notice that all the cities do not have to
// be connected.

LEETCODE_SOLUTION_UNITTEST(1615, MaximalNetworkRank, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 8;
  vector<vector<int>> roads    = {
      {0, 1},
      {1, 2},
      {2, 3},
      {2, 4},
      {5, 6},
      {5, 7}
  };
  int expect = 5;
  int actual = solution->maximalNetworkRank(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}
