// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Gas Station
//
// https://leetcode.com/problems/gas-station/
//
// Question ID: 134
// Difficult  : Medium
// Solve Date : 2022/01/21 22:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |134. Gas Station|:
//
// There are |n| gas stations along a circular route, where the amount of gas at
// the |iᵗʰ| station is |gas[i]|. You have a car with an unlimited gas tank and
// it costs |cost[i]| of gas to travel from the |iᵗʰ| station to its next |(i +
// 1)ᵗʰ| station. You begin the journey with an empty tank at one of the gas
// stations. Given two integer arrays |gas| and |cost|, return the starting gas
// station's index if you can travel around the circuit once in the clockwise
// direction, otherwise return |-1|. If there exists a solution, it is
// guaranteed to be unique  
//

LEETCODE_BEGIN_RESOLVING(134, GasStation, Solution);

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int total = 0, cur = 0, res = 0;
    for (int i = 0; i < gas.size(); ++i) {
      total += gas[i] - cost[i];
      cur += gas[i] - cost[i];
      if (cur < 0) {
        cur = 0;
        res = i + 1;
      }
    }
    return total < 0 ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == gas.length == cost.length|
// * |1 <= n <= 10⁵|
// * |0 <= gas[i], cost[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
// Output: 3
//
// Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 +
// 4 = 4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to station 0.
// Your tank = 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 - 3 + 2 = 6
// Travel to station 2. Your tank = 6 - 4 + 3 = 5
// Travel to station 3. The cost is 5. Your gas is just enough to travel back to
// station 3. Therefore, return 3 as the starting index.

LEETCODE_SOLUTION_UNITTEST(134, GasStation, example_1) {
  auto        solution = MakeSolution();
  vector<int> gas      = {1, 2, 3, 4, 5};
  vector<int> cost     = {3, 4, 5, 1, 2};
  int         expect   = 3;
  int         actual   = solution->canCompleteCircuit(gas, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: gas = [2,3,4], cost = [3,4,3]
// Output: -1
//
// You can't start at station 0 or 1, as there is not enough gas to travel to
// the next station. Let's start at station 2 and fill up with 4 unit of gas.
// Your tank = 0 + 4 = 4 Travel to station 0. Your tank = 4 - 3 + 2 = 3 Travel
// to station 1. Your tank = 3 - 3 + 3 = 3 You cannot travel back to station 2,
// as it requires 4 unit of gas but you only have 3. Therefore, you can't travel
// around the circuit once no matter where you start.

LEETCODE_SOLUTION_UNITTEST(134, GasStation, example_2) {
  auto        solution = MakeSolution();
  vector<int> gas      = {2, 3, 4};
  vector<int> cost     = {3, 4, 3};
  int         expect   = -1;
  int         actual   = solution->canCompleteCircuit(gas, cost);
  LCD_EXPECT_EQ(expect, actual);
}
