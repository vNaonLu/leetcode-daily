// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Network Delay Time
//
// https://leetcode.com/problems/network-delay-time/
//
// Question ID: 743
// Difficult  : Medium
// Solve Date : 2022/05/14 12:34

#include <iosfwd>
#include <limits>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |743. Network Delay Time|:
//
// You are given a network of |n| nodes, labeled from |1| to |n|. You are also
// given |times|, a list of travel times as directed edges |times[i] = (uᵢ, vᵢ,
// wᵢ)|, where |uᵢ| is the source node, |vᵢ| is the target node, and |wᵢ| is the
// time it takes for a signal to travel from source to target. We will send a
// signal from a given node |k|. Return the minimum time it takes for all the
// |n| nodes to receive the signal. If it is impossible for all the |n| nodes to
// receive the signal, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(743, NetworkDelayTime, Solution);

class Solution {
private:
  void dijkstra(vector<vector<pair<int, int>>> &network, int start,
                vector<int> &receive) {
    vector<int> visited(network.size(), 0);
    receive[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
      auto [time, node] = pq.top();
      pq.pop();

      if (time > receive[node]) {
        continue;
      }

      for (auto &n : network[node]) {
        auto &[next, take] = n;

        if (take + time < receive[next]) {
          receive[next] = take + time;
          pq.emplace(take + time, next);
        }
      }
    }
  }

public:
  inline constexpr static int unreachable = numeric_limits<int>::max();
  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    vector<vector<pair<int, int>>> network(n + 1);
    vector<int>                    received(n + 1, unreachable);
    for (auto &v : times) {
      network[v[0]].emplace_back(v[1], v[2]);
    }
    dijkstra(network, k, received);

    int res = 0;
    for (int i = 1; i <= n; ++i) {
      res = max(received[i], res);
    }

    return res == unreachable ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= n <= 100|
// * |1 <= times.length <= 6000|
// * |times[i].length == 3|
// * |1 <= uᵢ, vᵢ <= n|
// * |uᵢ != vᵢ|
// * |0 <= wᵢ <= 100|
// * All the pairs |(uᵢ, vᵢ)| are unique. (i.e., no multiple edges.)
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(743, NetworkDelayTime, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> times    = {
      {2, 1, 1},
      {2, 3, 1},
      {3, 4, 1}
  };
  int n      = 4;
  int k      = 2;
  int expect = 2;
  int actual = solution->networkDelayTime(times, n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: times = [[1,2,1]], n = 2, k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(743, NetworkDelayTime, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> times    = {
      {1, 2, 1}
  };
  int n      = 2;
  int k      = 1;
  int expect = 1;
  int actual = solution->networkDelayTime(times, n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: times = [[1,2,1]], n = 2, k = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(743, NetworkDelayTime, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> times    = {
      {1, 2, 1}
  };
  int n      = 2;
  int k      = 2;
  int expect = -1;
  int actual = solution->networkDelayTime(times, n, k);
  LCD_EXPECT_EQ(expect, actual);
}
