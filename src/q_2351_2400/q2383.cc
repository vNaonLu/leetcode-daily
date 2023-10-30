// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Hours of Training to Win a Competition
//
// https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/
//
// Question ID: 2383
// Difficult  : Easy
// Solve Date : 2023/10/25 20:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2383. Minimum Hours of Training to Win a Competition|:
//
// You are entering a competition, and are given two positive integers
// |initialEnergy| and |initialExperience| denoting your initial energy and
// initial experience respectively. You are also given two 0-indexed integer
// arrays |energy| and |experience|, both of length |n|. You will face |n|
// opponents in order. The energy and experience of the |iᵗʰ| opponent is
// denoted by |energy[i]| and |experience[i]| respectively. When you face an
// opponent, you need to have both strictly greater experience and energy to
// defeat them and move to the next opponent if available. Defeating the |iᵗʰ|
// opponent increases your experience by |experience[i]|, but decreases your
// energy by |energy[i]|. Before starting the competition, you can train for
// some number of hours. After each hour of training, you can either choose to
// increase your initial experience by one, or increase your initial energy by
// one. Return the minimum number of training hours required to defeat all |n|
// opponents.
//
//

LEETCODE_BEGIN_RESOLVING(2383, MinimumHoursOfTrainingToWinACompetition,
                         Solution);

class Solution {
public:
  int minNumberOfHours(int initialEnergy, int initialExperience,
                       vector<int> &energy, vector<int> &experience) {
    int n   = energy.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (initialEnergy <= energy[i]) {
        auto dif = energy[i] - initialEnergy;
        initialEnergy += dif + 1;
        res += dif + 1;
      }
      if (initialExperience <= experience[i]) {
        auto dif = experience[i] - initialExperience;
        initialExperience += dif + 1;
        res += dif + 1;
      }

      initialEnergy -= energy[i];
      initialExperience += experience[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == energy.length == experience.length|
// * |1 <= n <= 100|
// * |1 <= initialEnergy, initialExperience, energy[i], experience[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: initialEnergy = 5, initialExperience = 3, energy = [1,4,3,2],
//  experience = [2,6,3,1]
// Output: 8
//
// You can increase your energy to 11 after 6 hours of training, and your
// experience to 5 after 2 hours of training. You face the opponents in the
// following order:
// - You have more energy and experience than the 0ᵗʰ opponent so you win.
//  Your energy becomes 11 - 1 = 10, and your experience becomes 5 + 2 = 7.
// - You have more energy and experience than the 1ˢᵗ opponent so you win.
//  Your energy becomes 10 - 4 = 6, and your experience becomes 7 + 6 = 13.
// - You have more energy and experience than the 2ⁿᵈ opponent so you win.
//  Your energy becomes 6 - 3 = 3, and your experience becomes 13 + 3 = 16.
// - You have more energy and experience than the 3ʳᵈ opponent so you win.
//  Your energy becomes 3 - 2 = 1, and your experience becomes 16 + 1 = 17.
// You did a total of 6 + 2 = 8 hours of training before the competition, so we
// return 8. It can be proven that no smaller answer exists.

LEETCODE_SOLUTION_UNITTEST(2383, MinimumHoursOfTrainingToWinACompetition,
                           example_1) {
  auto        solution          = MakeSolution();
  int         initialEnergy     = 5;
  int         initialExperience = 3;
  vector<int> energy            = {1, 4, 3, 2};
  vector<int> experience        = {2, 6, 3, 1};
  int         expect            = 8;
  int actual = solution->minNumberOfHours(initialEnergy, initialExperience,
                                          energy, experience);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: initialEnergy = 2, initialExperience = 4, energy = [1], experience =
//  [3]
// Output: 0
//
// You do not need any additional energy or experience to win the competition,
// so we return 0.

LEETCODE_SOLUTION_UNITTEST(2383, MinimumHoursOfTrainingToWinACompetition,
                           example_2) {
  auto        solution          = MakeSolution();
  int         initialEnergy     = 2;
  int         initialExperience = 4;
  vector<int> energy            = {1};
  vector<int> experience        = {3};
  int         expect            = 0;
  int actual = solution->minNumberOfHours(initialEnergy, initialExperience,
                                          energy, experience);
  LCD_EXPECT_EQ(expect, actual);
}
