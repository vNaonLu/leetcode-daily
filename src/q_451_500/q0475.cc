// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Heaters
//
// https://leetcode.com/problems/heaters/
//
// Question ID: 475
// Difficult  : Medium
// Solve Date : 2024/04/12 20:13

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |475. Heaters|:
//
// Winter is coming! During the contest, your first job is to design a standard
// heater with a fixed warm radius to warm all the houses. Every house can be
// warmed, as long as the house is within the heater's warm radius range. Given
// the positions of |houses| and |heaters| on a horizontal line, return the
// minimum radius standard of heaters so that those heaters could cover all
// houses. Notice that all the |heaters| follow your radius standard, and the
// warm radius will the same.
//
//

LEETCODE_BEGIN_RESOLVING(475, Heaters, Solution);

class Solution {
public:
  int findRadius(vector<int> &houses, vector<int> &heaters) {
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    vector<int> res(houses.size(), numeric_limits<int>::max());
    for (int i = 0, h = 0; i < houses.size() && h < heaters.size();) {
      if (houses[i] <= heaters[h]) {
        res[i] = heaters[h] - houses[i];
        ++i;
      } else {
        ++h;
      }
    }
    for (int i = houses.size() - 1, h = heaters.size() - 1; i >= 0 && h >= 0;) {
      if (houses[i] >= heaters[h]) {
        res[i] = min(res[i], houses[i] - heaters[h]);
        --i;
      } else {
        --h;
      }
    }
    return *max_element(res.begin(), res.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= houses.length, heaters.length <= 3 * 10⁴|
// * |1 <= houses[i], heaters[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: houses = [1,2,3], heaters = [2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(475, Heaters, example_1) {
  auto        solution = MakeSolution();
  vector<int> houses   = {1, 2, 3};
  vector<int> heaters  = {2};
  int         expect   = 1;
  int         actual   = solution->findRadius(houses, heaters);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: houses = [1,2,3,4], heaters = [1,4]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(475, Heaters, example_2) {
  auto        solution = MakeSolution();
  vector<int> houses   = {1, 2, 3, 4};
  vector<int> heaters  = {1, 4};
  int         expect   = 1;
  int         actual   = solution->findRadius(houses, heaters);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: houses = [1,5], heaters = [2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(475, Heaters, example_3) {
  auto        solution = MakeSolution();
  vector<int> houses   = {1, 5};
  vector<int> heaters  = {2};
  int         expect   = 3;
  int         actual   = solution->findRadius(houses, heaters);
  LCD_EXPECT_EQ(expect, actual);
}
