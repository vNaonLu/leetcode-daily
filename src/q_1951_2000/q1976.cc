// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of Ways to Arrive at Destination
//
// https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/
//
// Question ID: 1976
// Difficult  : Medium
// Solve Date : 2025/03/23 14:50

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1976. Number of Ways to Arrive at Destination|:
//
// You are in a city that consists of |n| intersections numbered from |0| to |n
// - 1| with bi-directional roads between some intersections. The inputs are
// generated such that you can reach any intersection from any other
// intersection and that there is at most one road between any two
// intersections. You are given an integer |n| and a 2D integer array |roads|
// where |roads[i] = [uᵢ, vᵢ, timeᵢ]| means that there is a road between
// intersections |uᵢ| and |vᵢ| that takes |timeᵢ| minutes to travel. You want to
// know in how many ways you can travel from intersection |0| to intersection |n
// - 1| in the shortest amount of time. Return the number of ways you can arrive
// at your destination in the shortest amount of time. Since the answer may be
// large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1976, NumberOfWaysToArriveAtDestination, Solution);

class Solution {
public:
  int countPaths(int n, vector<vector<int>> &roads) {
    vector<vector<pair<int, int>>> graph(n);
    for (const auto &road : roads) {
      int u = road[0], v = road[1], time = road[2];
      graph[u].emplace_back(v, time);
      graph[v].emplace_back(u, time);
    }

    vector<int64_t> dist(n, numeric_limits<int64_t>::max());
    vector<int>     ways(n, 0);

    dist[0] = 0;
    ways[0] = 1;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<>>
        pq;
    pq.emplace(0, 0);

    const int MOD = 1e9 + 7;

    while (!pq.empty()) {
      auto [d, node] = pq.top();
      pq.pop();

      if (d > dist[node])
        continue;

      for (const auto &[neighbor, time] : graph[node]) {
        if (dist[node] + time < dist[neighbor]) {
          dist[neighbor] = dist[node] + time;
          ways[neighbor] = ways[node];
          pq.emplace(dist[neighbor], neighbor);
        } else if (dist[node] + time == dist[neighbor]) {
          ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
        }
      }
    }

    return ways[n - 1];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 200|
// * |n - 1 <= roads.length <= n * (n - 1) / 2|
// * |roads[i].length == 3|
// * |0 <= uᵢ, vᵢ <= n - 1|
// * |1 <= timeᵢ <= 10⁹|
// * |u_{i }!= vᵢ|
// * There is at most one road connecting any two intersections.
// * You can reach any intersection from any other intersection.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7, roads =
//  [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1976, NumberOfWaysToArriveAtDestination, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> roads    = {
      {0, 6, 7},
      {0, 1, 2},
      {1, 2, 3},
      {1, 3, 3},
      {6, 3, 3},
      {3, 5, 1},
      {6, 5, 1},
      {2, 5, 1},
      {0, 4, 5},
      {4, 6, 2}
  };
  int expect = 4;
  int actual = solution->countPaths(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, roads = [[1,0,10]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1976, NumberOfWaysToArriveAtDestination, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> roads    = {
      {1, 0, 10}
  };
  int expect = 1;
  int actual = solution->countPaths(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}
