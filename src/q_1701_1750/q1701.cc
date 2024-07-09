// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Average Waiting Time
//
// https://leetcode.com/problems/average-waiting-time/
//
// Question ID: 1701
// Difficult  : Medium
// Solve Date : 2024/07/09 19:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1701. Average Waiting Time|:
//
// There is a restaurant with a single chef. You are given an array |customers|,
// where |customers[i] = [arrivalᵢ, timeᵢ]:|
//
//  • |arrivalᵢ| is the arrival time of the |iᵗʰ| customer. The arrival times
//  are sorted in non-decreasing order.
//
//  • |timeᵢ| is the time needed to prepare the order of the |iᵗʰ| customer.
// When a customer arrives, he gives the chef his order, and the chef starts
// preparing it once he is idle. The customer waits till the chef finishes
// preparing his order. The chef does not prepare food for more than one
// customer at a time. The chef prepares food for customers in the order they
// were given in the input. Return the average waiting time of all customers.
// Solutions within |10⁻⁵| from the actual answer are considered accepted.
//
//

LEETCODE_BEGIN_RESOLVING(1701, AverageWaitingTime, Solution);

class Solution {
public:
  double averageWaitingTime(vector<vector<int>> &customers) {
    return helper(0, 0, customers) / customers.size();
  }

private:
  double helper(int i, double prepare, vector<vector<int>> const &v) {
    if (i >= v.size()) {
      return 0;
    }
    auto &t = v[i];
    prepare = max(prepare, 1.0 * t[0]) + t[1];
    return prepare - t[0] + helper(i + 1, prepare, v);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= customers.length <= 10⁵|
// * |1 <= arrivalᵢ, timeᵢ <= 10⁴|
// * |arrival_{i }<= arrivalᵢ₊₁|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: customers = [[1,2],[2,5],[4,3]]
// Output: 5.00000
// Explanation:
// 1) The first customer arrives at time 1, the chef takes his order and starts
// preparing it immediately at time 1, and finishes at time 3, so the waiting
// time of the first customer is 3 - 1 = 2. 2) The second customer arrives at
// time 2, the chef takes his order and starts preparing it at time 3, and
// finishes at time 8, so the waiting time of the second customer is 8 - 2 = 6.
// 3) The third customer arrives at time 4, the chef takes his order and starts
// preparing it at time 8, and finishes at time 11, so the waiting time of the
// third customer is 11 - 4 = 7. So the average waiting time = (2 + 6 + 7) / 3
// = 5.
//

LEETCODE_SOLUTION_UNITTEST(1701, AverageWaitingTime, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> customers = {
      {1, 2},
      {2, 5},
      {4, 3}
  };
  double expect = 5.00000;
  double actual = solution->averageWaitingTime(customers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: customers = [[5,2],[5,4],[10,3],[20,1]]
// Output: 3.25000
// Explanation:
// 1) The first customer arrives at time 5, the chef takes his order and starts
// preparing it immediately at time 5, and finishes at time 7, so the waiting
// time of the first customer is 7 - 5 = 2. 2) The second customer arrives at
// time 5, the chef takes his order and starts preparing it at time 7, and
// finishes at time 11, so the waiting time of the second customer is 11 - 5
// = 6. 3) The third customer arrives at time 10, the chef takes his order and
// starts preparing it at time 11, and finishes at time 14, so the waiting time
// of the third customer is 14 - 10 = 4. 4) The fourth customer arrives at time
// 20, the chef takes his order and starts preparing it immediately at time 20,
// and finishes at time 21, so the waiting time of the fourth customer is 21 -
// 20 = 1. So the average waiting time = (2 + 6 + 4 + 1) / 4 = 3.25.
//

LEETCODE_SOLUTION_UNITTEST(1701, AverageWaitingTime, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> customers = {
      { 5, 2},
      { 5, 4},
      {10, 3},
      {20, 1}
  };
  double expect = 3.25000;
  double actual = solution->averageWaitingTime(customers);
  LCD_EXPECT_EQ(expect, actual);
}
