// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Taking Maximum Energy From the Mystic Dungeon
//
// https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/
//
// Question ID: 3147
// Difficult  : Medium
// Solve Date : 2025/10/10 12:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3147. Taking Maximum Energy From the Mystic Dungeon|:
//
// In a mystic dungeon, |n| magicians are standing in a line. Each magician has
// an attribute that gives you energy. Some magicians can give you negative
// energy, which means taking energy from you. You have been cursed in such a
// way that after absorbing energy from magician |i|, you will be instantly
// transported to magician |(i + k)|. This process will be repeated until you
// reach the magician where |(i + k)| does not exist. In other words, you will
// choose a starting point and then teleport with |k| jumps until you reach the
// end of the magicians' sequence, absorbing all the energy during the journey.
// You are given an array |energy| and an integer |k|. Return the maximum
// possible energy you can gain. Note that when you are reach a magician, you
// must take energy from them, whether it is negative or positive energy.
//
//

LEETCODE_BEGIN_RESOLVING(3147, TakingMaximumEnergyFromTheMysticDungeon,
                         Solution);

class Solution {
public:
  int maximumEnergy(vector<int> &energy, int k) {
    int         n = energy.size();
    vector<int> dp(n);
    int         res = numeric_limits<int>::min();
    for (int i = n - 1; i >= 0; --i) {
      dp[i] = energy[i] + ((i + k < n) ? dp[i + k] : 0);
      res   = max(res, dp[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= energy.length <= 10⁵|
// * |-1000 <= energy[i] <= 1000|
// * |1 <= k <= energy.length - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: energy = [5,2,-10,-5,1], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3147, TakingMaximumEnergyFromTheMysticDungeon,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> energy   = {5, 2, -10, -5, 1};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->maximumEnergy(energy, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: energy = [-2,-3,-1], k = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3147, TakingMaximumEnergyFromTheMysticDungeon,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> energy   = {-2, -3, -1};
  int         k        = 2;
  int         expect   = -1;
  int         actual   = solution->maximumEnergy(energy, k);
  LCD_EXPECT_EQ(expect, actual);
}
