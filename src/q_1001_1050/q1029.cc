// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two City Scheduling
//
// https://leetcode.com/problems/two-city-scheduling/
//
// Question ID: 1029
// Difficult  : Medium
// Solve Date : 2022/02/21 23:52

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1029. Two City Scheduling|:
//
// A company is planning to interview |2n| people. Given the array |costs| where
// |costs[i] = [aCostᵢ, bCostᵢ]|, the cost of flying the |iᵗʰ| person to city
// |a| is |aCostᵢ|, and the cost of flying the |iᵗʰ| person to city |b| is
// |bCostᵢ|. Return the minimum cost to fly every person to a city such that
// exactly |n| people arrive in each city.  
//

LEETCODE_BEGIN_RESOLVING(1029, TwoCityScheduling, Solution);

class Solution {
public:
  int twoCitySchedCost(vector<vector<int>> &costs) {
    int         n = costs.size() / 2, res = 0;
    vector<int> refund;
    for (const auto &v : costs) {
      res += v[0];
      refund.emplace_back(v[0] - v[1]);
    }
    sort(refund.rbegin(), refund.rend());
    for (int i = 0; i < n; ++i) {
      res -= refund[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 * n == costs.length|
// * |2 <= costs.length <= 100|
// * |costs.length| is even.
// * |1 <= aCostᵢ, bCostᵢ <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: costs = [[10,20],[30,200],[400,50],[30,20]]
// Output: 110
//
// The first person goes to city A for a cost of 10.
// The second person goes to city A for a cost of 30.
// The third person goes to city B for a cost of 50.
// The fourth person goes to city B for a cost of 20.
// The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people
// interviewing in each city.

LEETCODE_SOLUTION_UNITTEST(1029, TwoCityScheduling, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> costs    = {
      { 10,  20},
      { 30, 200},
      {400,  50},
      { 30,  20}
  };
  int expect = 110;
  int actual = solution->twoCitySchedCost(costs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
// Output: 1859
//

LEETCODE_SOLUTION_UNITTEST(1029, TwoCityScheduling, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> costs    = {
      {259, 770},
      {448,  54},
      {926, 667},
      {184, 139},
      {840, 118},
      {577, 469}
  };
  int expect = 1859;
  int actual = solution->twoCitySchedCost(costs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: costs =
//  [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
// Output: 3086
//

LEETCODE_SOLUTION_UNITTEST(1029, TwoCityScheduling, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> costs    = {
      {515, 563},
      {451, 713},
      {537, 709},
      {343, 819},
      {855, 779},
      {457,  60},
      {650, 359},
      {631,  42}
  };
  int expect = 3086;
  int actual = solution->twoCitySchedCost(costs);
  LCD_EXPECT_EQ(expect, actual);
}
