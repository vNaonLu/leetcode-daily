// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Fuel Cost to Report to the Capital
//
// https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/
//
// Question ID: 2477
// Difficult  : Medium
// Solve Date : 2023/02/12 14:52

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2477. Minimum Fuel Cost to Report to the Capital|:
//
// There is a tree (i.e., a connected, undirected graph with no cycles)
// structure country network consisting of |n| cities numbered from |0| to |n -
// 1| and exactly |n - 1| roads. The capital city is city |0|. You are given a
// 2D integer array |roads| where |roads[i] = [aᵢ, bᵢ]| denotes that there
// exists a bidirectional road connecting cities |aᵢ| and |bᵢ|. There is a
// meeting for the representatives of each city. The meeting is in the capital
// city. There is a car in each city. You are given an integer |seats| that
// indicates the number of seats in each car. A representative can use the car
// in their city to travel or change the car and ride with another
// representative. The cost of traveling between two cities is one liter of
// fuel. Return the minimum number of liters of fuel to reach the capital city.
//

LEETCODE_BEGIN_RESOLVING(2477, MinimumFuelCostToReportToTheCapital, Solution);

class Solution {
private:
  int dfs(int i, int prev, vector<vector<int>> &graph, int64_t &res, int &s,
          int people = 1) {
    for (auto x : graph[i]) {
      if (x == prev) {
        continue;
      }
      people += dfs(x, i, graph, res, s);
    }
    if (i != 0) {
      res += (people + s - 1) / s;
    }
    return people;
  }

public:
  long long minimumFuelCost(vector<vector<int>> &roads, int seats) {
    int64_t             res = 0;
    vector<vector<int>> graph(roads.size() + 1);
    for (auto &v : roads) {
      graph[v[0]].emplace_back(v[1]);
      graph[v[1]].emplace_back(v[0]);
    }
    dfs(0, 0, graph, res, seats);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |roads.length == n - 1|
// * |roads[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |roads| represents a valid tree.
// * |1 <= seats <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: roads = [[0,1],[0,2],[0,3]], seats = 5
// Output: 3
//
// - Representative₁ goes directly to the capital with 1 liter of fuel.
// - Representative₂ goes directly to the capital with 1 liter of fuel.
// - Representative₃ goes directly to the capital with 1 liter of fuel.
// It costs 3 liters of fuel at minimum.
// It can be proven that 3 is the minimum number of liters of fuel needed.

LEETCODE_SOLUTION_UNITTEST(2477, MinimumFuelCostToReportToTheCapital,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> roads    = {
      {0, 1},
      {0, 2},
      {0, 3}
  };
  int  seats  = 5;
  long expect = 3;
  long actual = solution->minimumFuelCost(roads, seats);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: roads = [[3,1],[3,2],[1,0],[0,4],[0,5],[4,6]], seats = 2
// Output: 7
//
// - Representative₂ goes directly to city 3 with 1 liter of fuel.
// - Representative₂ and representative₃ go together to city 1 with 1 liter of
// fuel.
// - Representative₂ and representative₃ go together to the capital with 1 liter
// of fuel.
// - Representative₁ goes directly to the capital with 1 liter of fuel.
// - Representative₅ goes directly to the capital with 1 liter of fuel.
// - Representative₆ goes directly to city 4 with 1 liter of fuel.
// - Representative₄ and representative₆ go together to the capital with 1 liter
// of fuel. It costs 7 liters of fuel at minimum. It can be proven that 7 is the
// minimum number of liters of fuel needed.

LEETCODE_SOLUTION_UNITTEST(2477, MinimumFuelCostToReportToTheCapital,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> roads    = {
      {3, 1},
      {3, 2},
      {1, 0},
      {0, 4},
      {0, 5},
      {4, 6}
  };
  int  seats  = 2;
  long expect = 7;
  long actual = solution->minimumFuelCost(roads, seats);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: roads = [], seats = 1
// Output: 0
//
// No representatives need to travel to the capital city.

LEETCODE_SOLUTION_UNITTEST(2477, MinimumFuelCostToReportToTheCapital,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> roads    = {};
  int                 seats    = 1;
  long                expect   = 0;
  long                actual   = solution->minimumFuelCost(roads, seats);
  LCD_EXPECT_EQ(expect, actual);
}
