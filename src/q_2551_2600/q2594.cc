// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Time to Repair Cars
//
// https://leetcode.com/problems/minimum-time-to-repair-cars/
//
// Question ID: 2594
// Difficult  : Medium
// Solve Date : 2025/03/16 13:29

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2594. Minimum Time to Repair Cars|:
//
// You are given an integer array |ranks| representing the ranks of some
// mechanics. ranksᵢ is the rank of the iᵗʰ mechanic. A mechanic with a rank |r|
// can repair n cars in |r * n²| minutes. You are also given an integer |cars|
// representing the total number of cars waiting in the garage to be repaired.
// Return the minimum time taken to repair all the cars.
// Note: All the mechanics can repair the cars simultaneously.
//
//

LEETCODE_BEGIN_RESOLVING(2594, MinimumTimeToRepairCars, Solution);

class Solution {
public:
  long long repairCars(vector<int> &ranks, int cars) {
    int64_t lo = 1;
    int64_t hi = 1e14;
    while (lo < hi) {
      auto mi = lo + (hi - lo) / 2;
      if (time(ranks, cars, mi)) {
        hi = mi;
      } else {
        lo = mi + 1;
      }
    }
    return lo;
  }

private:
  bool time(vector<int> const &ranks, int cars, int64_t mn) {
    int64_t res = 0;
    for (auto r : ranks) {
      int64_t c2 = mn / r;
      int64_t c  = floor(sqrt(c2));
      res += c;
    }
    return res >= cars;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= ranks.length <= 10⁵|
// * |1 <= ranks[i] <= 100|
// * |1 <= cars <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ranks = [4,2,3,1], cars = 10
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(2594, MinimumTimeToRepairCars, example_1) {
  auto        solution = MakeSolution();
  vector<int> ranks    = {4, 2, 3, 1};
  int         cars     = 10;
  long long   expect   = 16;
  long long   actual   = solution->repairCars(ranks, cars);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ranks = [5,1,8], cars = 6
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(2594, MinimumTimeToRepairCars, example_2) {
  auto        solution = MakeSolution();
  vector<int> ranks    = {5, 1, 8};
  int         cars     = 6;
  long long   expect   = 16;
  long long   actual   = solution->repairCars(ranks, cars);
  LCD_EXPECT_EQ(expect, actual);
}
