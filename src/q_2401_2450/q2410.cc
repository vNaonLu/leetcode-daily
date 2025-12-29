// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Matching of Players With Trainers
//
// https://leetcode.com/problems/maximum-matching-of-players-with-trainers/
//
// Question ID: 2410
// Difficult  : Medium
// Solve Date : 2025/07/13 13:14

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2410. Maximum Matching of Players With Trainers|:
//
// You are given a 0-indexed integer array |players|, where |players[i]|
// represents the ability of the |iᵗʰ| player. You are also given a 0-indexed
// integer array |trainers|, where |trainers[j]| represents the training
// capacity of the |jᵗʰ| trainer. The |iᵗʰ| player can match with the |jᵗʰ|
// trainer if the player's ability is less than or equal to the trainer's
// training capacity. Additionally, the |iᵗʰ| player can be matched with at most
// one trainer, and the |jᵗʰ| trainer can be matched with at most one player.
// Return the maximum number of matchings between |players| and |trainers| that
// satisfy these conditions.
//
//

LEETCODE_BEGIN_RESOLVING(2410, MaximumMatchingOfPlayersWithTrainers, Solution);

class Solution {
public:
  int matchPlayersAndTrainers(vector<int> &players, vector<int> &trainers) {
    sort(players.begin(), players.end());
    sort(trainers.begin(), trainers.end());
    auto tb  = trainers.begin();
    int  res = 0;
    for (auto x : players) {
      auto it = lower_bound(tb, trainers.end(), x);
      if (it == trainers.end()) {
        break;
      }

      tb = it + 1;
      ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= players.length, trainers.length <= 10⁵|
// * |1 <= players[i], trainers[j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: players = [4,7,9], trainers = [8,2,5,8]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2410, MaximumMatchingOfPlayersWithTrainers,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> players  = {4, 7, 9};
  vector<int> trainers = {8, 2, 5, 8};
  int         expect   = 2;
  int         actual   = solution->matchPlayersAndTrainers(players, trainers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: players = [1,1,1], trainers = [10]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2410, MaximumMatchingOfPlayersWithTrainers,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> players  = {1, 1, 1};
  vector<int> trainers = {10};
  int         expect   = 1;
  int         actual   = solution->matchPlayersAndTrainers(players, trainers);
  LCD_EXPECT_EQ(expect, actual);
}
