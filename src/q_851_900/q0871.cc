// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Refueling Stops
//
// https://leetcode.com/problems/minimum-number-of-refueling-stops/
//
// Question ID: 871
// Difficult  : Hard
// Solve Date : 2022/08/20 14:10

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |871. Minimum Number of Refueling Stops|:
//
// A car travels from a starting position to a destination which is |target|
// miles east of the starting position. There are gas stations along the way.
// The gas stations are represented as an array |stations| where |stations[i] =
// [positionᵢ, fuelᵢ]| indicates that the |iᵗʰ| gas station is |positionᵢ| miles
// east of the starting position and has |fuelᵢ| liters of gas. The car starts
// with an infinite tank of gas, which initially has |startFuel| liters of fuel
// in it. It uses one liter of gas per one mile that it drives. When the car
// reaches a gas station, it may stop and refuel, transferring all the gas from
// the station into the car. Return the minimum number of refueling stops the
// car must make in order to reach its destination. If it cannot reach the
// destination, return |-1|. Note that if the car reaches a gas station with |0|
// fuel left, the car can still refuel there. If the car reaches the destination
// with |0| fuel left, it is still considered to have arrived.
//

LEETCODE_BEGIN_RESOLVING(871, MinimumNumberOfRefuelingStops, Solution);

class Solution {
public:
  int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
    auto pq   = priority_queue<int>();
    auto res  = 0;
    auto prev = 0;
    auto tank = startFuel;

    for (auto &v : stations) {
      auto loc = v[0];
      auto cap = v[1];

      tank -= loc - prev;
      while (!pq.empty() && tank < 0) {
        tank += pq.top();
        pq.pop();
        ++res;
      }

      if (tank < 0) {
        return -1;
      }

      pq.emplace(cap);
      prev = loc;
    }

    tank -= target - prev;
    while (!pq.empty() && tank < 0) {
      tank += pq.top();
      pq.pop();
      ++res;
    }

    if (tank < 0) {
      return -1;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= target, startFuel <= 10⁹|
// * |0 <= stations.length <= 500|
// * |1 <= positionᵢ < positionᵢ₊₁ < target|
// * |1 <= fuelᵢ < 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = 1, startFuel = 1, stations = []
// Output: 0
//
// We can reach the target without refueling.

LEETCODE_SOLUTION_UNITTEST(871, MinimumNumberOfRefuelingStops, example_1) {
  auto                solution  = MakeSolution();
  int                 target    = 1;
  int                 startFuel = 1;
  vector<vector<int>> stations  = {};
  int                 expect    = 0;
  int actual = solution->minRefuelStops(target, startFuel, stations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = 100, startFuel = 1, stations = [[10,100]]
// Output: -1
//
// We can not reach the target (or even the first gas station).

LEETCODE_SOLUTION_UNITTEST(871, MinimumNumberOfRefuelingStops, example_2) {
  auto                solution  = MakeSolution();
  int                 target    = 100;
  int                 startFuel = 1;
  vector<vector<int>> stations  = {
      {10, 100}
  };
  int expect = -1;
  int actual = solution->minRefuelStops(target, startFuel, stations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = 100, startFuel = 10, stations =
//  [[10,60],[20,30],[30,30],[60,40]]
// Output: 2
//
// We start with 10 liters of fuel.
// We drive to position 10, expending 10 liters of fuel. We refuel from 0 liters
// to 60 liters of gas. Then, we drive from position 10 to position 60
// (expending 50 liters of fuel), and refuel from 10 liters to 50 liters of gas.
// We then drive to and reach the target. We made 2 refueling stops along the
// way, so we return 2.

LEETCODE_SOLUTION_UNITTEST(871, MinimumNumberOfRefuelingStops, example_3) {
  auto                solution  = MakeSolution();
  int                 target    = 100;
  int                 startFuel = 10;
  vector<vector<int>> stations  = {
      {10, 60},
      {20, 30},
      {30, 30},
      {60, 40}
  };
  int expect = 2;
  int actual = solution->minRefuelStops(target, startFuel, stations);
  LCD_EXPECT_EQ(expect, actual);
}
