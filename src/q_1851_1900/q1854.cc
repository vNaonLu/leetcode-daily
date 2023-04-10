// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Population Year
//
// https://leetcode.com/problems/maximum-population-year/
//
// Question ID: 1854
// Difficult  : Easy
// Solve Date : 2023/04/10 08:52

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1854. Maximum Population Year|:
//
// You are given a 2D integer array |logs| where each |logs[i] = [birthᵢ,
// deathᵢ]| indicates the birth and death years of the |iᵗʰ| person. The
// population of some year |x| is the number of people alive during that year.
// The |iᵗʰ| person is counted in year |x|'s population if |x| is in the
// inclusive range |[birthᵢ, deathᵢ - 1]|. Note that the person is not counted
// in the year that they die. Return the earliest year with the maximum
// population.
//
//

LEETCODE_BEGIN_RESOLVING(1854, MaximumPopulationYear, Solution);

class Solution {
public:
  int maximumPopulation(vector<vector<int>> &logs) {
    map<int, int> pop;
    for (auto &v : logs) {
      for (int y = v[0]; y < v[1]; ++y) {
        ++pop[y];
      }
    }
    auto *res = &*pop.begin();
    for (auto &pr : pop) {
      if (pr.second > (*res).second && pr.first > (*res).first) {
        res = &pr;
      }
    }
    return (*res).first;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= logs.length <= 100|
// * |1950 <= birthᵢ < deathᵢ <= 2050|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: logs = [[1993,1999],[2000,2010]]
// Output: 1993
//
// The maximum population is 1, and 1993 is the earliest year with this
// population.

LEETCODE_SOLUTION_UNITTEST(1854, MaximumPopulationYear, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> logs     = {
      {1993, 1999},
      {2000, 2010}
  };
  int expect = 1993;
  int actual = solution->maximumPopulation(logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
// Output: 1960
//
// The maximum population is 2, and it had happened in years 1960 and 1970.
// The earlier year between them is 1960.

LEETCODE_SOLUTION_UNITTEST(1854, MaximumPopulationYear, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> logs     = {
      {1950, 1961},
      {1960, 1971},
      {1970, 1981}
  };
  int expect = 1960;
  int actual = solution->maximumPopulation(logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1982,1998],[2013,2042],[2010,2035],[2022,2050],[2047,2048]]
// Output: 2022
//

LEETCODE_SOLUTION_UNITTEST(1854, MaximumPopulationYear, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> logs     = {
      {1982, 1998},
      {2013, 2042},
      {2010, 2035},
      {2022, 2050},
      {2047, 2048}
  };
  int expect = 2022;
  int actual = solution->maximumPopulation(logs);
  LCD_EXPECT_EQ(expect, actual);
}
