// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Minimum Amount of Time to Brew Potions
//
// https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/
//
// Question ID: 3494
// Difficult  : Medium
// Solve Date : 2025/10/09 11:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3494. Find the Minimum Amount of Time to Brew Potions|:
//
//

LEETCODE_BEGIN_RESOLVING(3494, FindTheMinimumAmountOfTimeToBrewPotions,
                         Solution);

class Solution {
public:
  long long minTime(vector<int> &skill, vector<int> &mana) {
    int             n = skill.size();
    int             m = mana.size();
    vector<int64_t> done(n + 1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        done[j + 1] = max(done[j + 1], done[j]) + mana[i] * skill[j];
      }
      for (int j = n - 1; j >= 0; --j) {
        done[j] = done[j + 1] - mana[i] * skill[j];
      }
    }
    return done.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == skill.length|
// * |m == mana.length|
// * |1 <= n, m <= 5000|
// * |1 <= mana[i], skill[i] <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: skill = [1,5,2,4], mana = [5,1,4,2]
// Output: 110
//

LEETCODE_SOLUTION_UNITTEST(3494, FindTheMinimumAmountOfTimeToBrewPotions,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> skill    = {1, 5, 2, 4};
  vector<int> mana     = {5, 1, 4, 2};
  long long   expect   = 110;
  long long   actual   = solution->minTime(skill, mana);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: skill = [1,1,1], mana = [1,1,1]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3494, FindTheMinimumAmountOfTimeToBrewPotions,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> skill    = {1, 1, 1};
  vector<int> mana     = {1, 1, 1};
  long long   expect   = 5;
  long long   actual   = solution->minTime(skill, mana);
  LCD_EXPECT_EQ(expect, actual);
}
