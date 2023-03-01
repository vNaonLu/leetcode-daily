// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bus Routes
//
// https://leetcode.com/problems/bus-routes/
//
// Question ID: 815
// Difficult  : Hard
// Solve Date : 2022/09/18 14:27

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |815. Bus Routes|:
//
// You are given an array |routes| representing bus routes where |routes[i]| is
// a bus route that the |iᵗʰ| bus repeats forever.
//
//  • For example, if |routes[0] = [1, 5, 7]|, this means that the |0ᵗʰ| bus
//  travels in the sequence |1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ...| forever.
// You will start at the bus stop |source| (You are not on any bus initially),
// and you want to go to the bus stop |target|. You can travel between bus stops
// by buses only. Return the least number of buses you must take to travel from
// |source| to |target|. Return |-1| if it is not possible.
//

LEETCODE_BEGIN_RESOLVING(815, BusRoutes, Solution);

class Solution {
private:
  bool intersect(vector<int> &a, vector<int> &b) {
    int i = 0;
    int j = 0;
    while (i < a.size() && j < b.size()) {
      if (a[i] == b[j]) {
        return true;
      }
      if (a[i] < b[j]) {
        ++i;
      } else {
        ++j;
      }
    }
    return false;
  }

public:
  int numBusesToDestination(vector<vector<int>> &routes, int source,
                            int target) {
    if (source == target) {
      return 0;
    }
    auto n     = routes.size();
    auto graph = vector<vector<int>>();
    for (auto &p : routes) {
      sort(p.begin(), p.end());
      graph.emplace_back();
    }

    auto seen = unordered_set<int>();
    auto targ = unordered_set<int>();
    auto path = queue<pair<int, int>>();

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (intersect(routes[i], routes[j])) {
          graph[i].emplace_back(j);
          graph[j].emplace_back(i);
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      auto find = lower_bound(routes[i].begin(), routes[i].end(), source);
      if (find != routes[i].end() && *find == source) {
        seen.emplace(i);
        path.emplace(i, 0);
      }
      find = lower_bound(routes[i].begin(), routes[i].end(), target);
      if (find != routes[i].end() && *find == target) {
        targ.emplace(i);
      }
    }

    while (!path.empty()) {
      auto [node, depth] = path.front();
      path.pop();
      if (targ.count(node)) {
        return depth + 1;
      }
      for (auto n : graph[node]) {
        if (!seen.count(n)) {
          seen.emplace(n);
          path.emplace(n, depth + 1);
        }
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= routes.length <= 500|.
// * |1 <= routes[i].length <= 10⁵|
// * All the values of |routes[i]| are unique.
// * |sum(routes[i].length) <= 10⁵|
// * |0 <= routes[i][j] < 10⁶|
// * |0 <= source, target < 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
//
// The best strategy is take the first bus to the bus stop 7, then take the
// second bus to the bus stop 6.

LEETCODE_SOLUTION_UNITTEST(815, BusRoutes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> routes   = {
      {1, 2, 7},
      {3, 6, 7}
  };
  int source = 1;
  int target = 6;
  int expect = 2;
  int actual = solution->numBusesToDestination(routes, source, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target
//  = 12
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(815, BusRoutes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> routes   = {
      {7, 12},
      {4, 5, 15},
      {6},
      {15, 19},
      {9, 12, 13}
  };
  int source = 15;
  int target = 12;
  int expect = -1;
  int actual = solution->numBusesToDestination(routes, source, target);
  LCD_EXPECT_EQ(expect, actual);
}
