// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Cheapest Flights Within K Stops
//
// https://leetcode.com/problems/cheapest-flights-within-k-stops/
//
// Question ID: 787
// Difficult  : Medium
// Solve Date : 2023/01/26 13:37

#include <iosfwd>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |787. Cheapest Flights Within K Stops|:
//
// There are |n| cities connected by some number of flights. You are given an
// array |flights| where |flights[i] = [fromᵢ, toᵢ, priceᵢ]| indicates that
// there is a flight from city |fromᵢ| to city |toᵢ| with cost |priceᵢ|. You are
// also given three integers |src|, |dst|, and |k|, return the cheapest price
// from |src| to |dst| with at most |k| stops. If there is no such route, return
// |-1|.
//

LEETCODE_BEGIN_RESOLVING(787, CheapestFlightsWithinKStops, Solution);

class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    unordered_map<int, vector<pair<int, int>>> graph;
    for (auto &e : flights) {
      graph[e[0]].emplace_back(e[1], e[2]);
    }
    vector<int>           prices(n, -1);
    queue<pair<int, int>> q;
    q.emplace(src, 0);
    ++k;
    while (!q.empty() && k) {
      auto tmp = std::move(q);
      while (!tmp.empty()) {
        auto [cur, p] = tmp.front();
        tmp.pop();
        for (auto e : graph[cur]) {
          auto price = p + e.second;
          if (prices[e.first] == -1 || price < prices[e.first]) {
            prices[e.first] = price;
            q.emplace(e.first, price);
          }
        }
      }
      --k;
    }
    return prices[dst];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |0 <= flights.length <= (n * (n - 1) / 2)|
// * |flights[i].length == 3|
// * |0 <= fromᵢ, toᵢ < n|
// * |fromᵢ != toᵢ|
// * |1 <= priceᵢ <= 10⁴|
// * There will not be any multiple flights between two cities.
// * |0 <= src, dst, k < n|
// * |src != dst|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]],
//  src = 0, dst = 3, k = 1
// Output: 700
//
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 3 is marked in red and
// has cost 100 + 600 = 700. Note that the path through cities [0,1,2,3] is
// cheaper but is invalid because it uses 2 stops.

LEETCODE_SOLUTION_UNITTEST(787, CheapestFlightsWithinKStops, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> flights  = {
      {0, 1, 100},
      {1, 2, 100},
      {2, 0, 100},
      {1, 3, 600},
      {2, 3, 200}
  };
  int src    = 0;
  int dst    = 3;
  int k      = 1;
  int expect = 700;
  int actual = solution->findCheapestPrice(n, flights, src, dst, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k
//  = 1
// Output: 200
//
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 2 is marked in red and
// has cost 100 + 100 = 200.

LEETCODE_SOLUTION_UNITTEST(787, CheapestFlightsWithinKStops, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> flights  = {
      {0, 1, 100},
      {1, 2, 100},
      {0, 2, 500}
  };
  int src    = 0;
  int dst    = 2;
  int k      = 1;
  int expect = 200;
  int actual = solution->findCheapestPrice(n, flights, src, dst, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k
//  = 0
// Output: 500
//
// The graph is shown above.
// The optimal path with no stops from city 0 to 2 is marked in red and has cost
// 500.

LEETCODE_SOLUTION_UNITTEST(787, CheapestFlightsWithinKStops, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> flights  = {
      {0, 1, 100},
      {1, 2, 100},
      {0, 2, 500}
  };
  int src    = 0;
  int dst    = 2;
  int k      = 0;
  int expect = 500;
  int actual = solution->findCheapestPrice(n, flights, src, dst, k);
  LCD_EXPECT_EQ(expect, actual);
}
