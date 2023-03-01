// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Car Pooling
//
// https://leetcode.com/problems/car-pooling/
//
// Question ID: 1094
// Difficult  : Medium
// Solve Date : 2022/01/06 18:11

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1094. Car Pooling|:
//
// There is a car with |capacity| empty seats. The vehicle only drives east
// (i.e., it cannot turn around and drive west). You are given the integer
// |capacity| and an array |trips| where |trips[i] = [numPassengersᵢ, fromᵢ,
// toᵢ]| indicates that the |iᵗʰ| trip has |numPassengersᵢ| passengers and the
// locations to pick them up and drop them off are |fromᵢ| and |toᵢ|
// respectively. The locations are given as the number of kilometers due east
// from the car's initial location. Return |true| if it is possible to pick up
// and drop off all passengers for all the given trips, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(1094, CarPooling, Solution);

class Solution {
private:
  using trip_t = pair<int, int>;

public:
  bool carPooling(vector<vector<int>> &trips, int capacity) {
    sort(trips.begin(), trips.end(), [](auto lhs, auto rhs) {
      return lhs[1] < rhs[1] || (lhs[1] == rhs[1] && lhs[2] < rhs[2]);
    });
    int                                                     cur = 0;
    priority_queue<trip_t, vector<trip_t>, greater<trip_t>> pq;
    for (int i = 0; i < trips.size(); ++i) {
      while (!pq.empty() && pq.top().first <= trips[i][1]) {
        cur -= pq.top().second;
        pq.pop();
      }
      pq.emplace(trips[i][2], trips[i][0]);
      cur += trips[i][0];
      if (cur > capacity)
        return false;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= trips.length <= 1000|
// * |trips[i].length == 3|
// * |1 <= numPassengersᵢ <= 100|
// * |0 <= fromᵢ < toᵢ <= 1000|
// * |1 <= capacity <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: trips = [[2,1,5],[3,3,7]], capacity = 4
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1094, CarPooling, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> trips    = {
      {2, 1, 5},
      {3, 3, 7}
  };
  int  capacity = 4;
  bool expect   = false;
  bool actual   = solution->carPooling(trips, capacity);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: trips = [[2,1,5],[3,3,7]], capacity = 5
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1094, CarPooling, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> trips    = {
      {2, 1, 5},
      {3, 3, 7}
  };
  int  capacity = 5;
  bool expect   = true;
  bool actual   = solution->carPooling(trips, capacity);
  LCD_EXPECT_EQ(expect, actual);
}
