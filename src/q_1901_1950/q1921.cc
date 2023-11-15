// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Eliminate Maximum Number of Monsters
//
// https://leetcode.com/problems/eliminate-maximum-number-of-monsters/
//
// Question ID: 1921
// Difficult  : Medium
// Solve Date : 2023/11/07 19:11

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1921. Eliminate Maximum Number of Monsters|:
//
// You are playing a video game where you are defending your city from a group
// of |n| monsters. You are given a 0-indexed integer array |dist| of size |n|,
// where |dist[i]| is the initial distance in kilometers of the |iᵗʰ| monster
// from the city. The monsters walk toward the city at a constant speed. The
// speed of each monster is given to you in an integer array |speed| of size
// |n|, where |speed[i]| is the speed of the |iᵗʰ| monster in kilometers per
// minute. You have a weapon that, once fully charged, can eliminate a single
// monster. However, the weapon takes one minute to charge. The weapon is fully
// charged at the very start. You lose when any monster reaches your city. If a
// monster reaches the city at the exact moment the weapon is fully charged, it
// counts as a loss, and the game ends before you can use your weapon. Return
// the maximum number of monsters that you can eliminate before you lose, or |n|
// if you can eliminate all the monsters before they reach the city.
//
//

LEETCODE_BEGIN_RESOLVING(1921, EliminateMaximumNumberOfMonsters, Solution);

class Solution {
public:
  int eliminateMaximum(vector<int> &dist, vector<int> &speed) {
    vector<double> time;
    for (int i = 0; i < dist.size(); ++i) {
      time.emplace_back(static_cast<double>(dist[i]) / speed[i]);
    }

    sort(time.begin(), time.end());
    for (int i = 0; i < dist.size(); ++i) {
      if (time[i] <= i) {
        return i;
      }
    }
    return dist.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == dist.length == speed.length|
// * |1 <= n <= 10⁵|
// * |1 <= dist[i], speed[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dist = [1,3,4], speed = [1,1,1]
// Output: 3
//
// In the beginning, the distances of the monsters are [1,3,4]. You eliminate
// the first monster. After a minute, the distances of the monsters are [X,2,3].
// You eliminate the second monster. After a minute, the distances of the
// monsters are [X,X,2]. You eliminate the thrid monster. All 3 monsters can be
// eliminated.

LEETCODE_SOLUTION_UNITTEST(1921, EliminateMaximumNumberOfMonsters, example_1) {
  auto        solution = MakeSolution();
  vector<int> dist     = {1, 3, 4};
  vector<int> speed    = {1, 1, 1};
  int         expect   = 3;
  int         actual   = solution->eliminateMaximum(dist, speed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dist = [1,1,2,3], speed = [1,1,1,1]
// Output: 1
//
// In the beginning, the distances of the monsters are [1,1,2,3]. You eliminate
// the first monster. After a minute, the distances of the monsters are
// [X,0,1,2], so you lose. You can only eliminate 1 monster.

LEETCODE_SOLUTION_UNITTEST(1921, EliminateMaximumNumberOfMonsters, example_2) {
  auto        solution = MakeSolution();
  vector<int> dist     = {1, 1, 2, 3};
  vector<int> speed    = {1, 1, 1, 1};
  int         expect   = 1;
  int         actual   = solution->eliminateMaximum(dist, speed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: dist = [3,2,4], speed = [5,3,2]
// Output: 1
//
// In the beginning, the distances of the monsters are [3,2,4]. You eliminate
// the first monster. After a minute, the distances of the monsters are [X,0,2],
// so you lose. You can only eliminate 1 monster.

LEETCODE_SOLUTION_UNITTEST(1921, EliminateMaximumNumberOfMonsters, example_3) {
  auto        solution = MakeSolution();
  vector<int> dist     = {3, 2, 4};
  vector<int> speed    = {5, 3, 2};
  int         expect   = 1;
  int         actual   = solution->eliminateMaximum(dist, speed);
  LCD_EXPECT_EQ(expect, actual);
}
