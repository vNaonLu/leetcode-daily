// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Players With Zero or One Losses
//
// https://leetcode.com/problems/find-players-with-zero-or-one-losses/
//
// Question ID: 2225
// Difficult  : Medium
// Solve Date : 2022/11/29 18:03

#include <algorithm>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2225. Find Players With Zero or One Losses|:
//
// You are given an integer array |matches| where |matches[i] = [winnerᵢ,
// loserᵢ]| indicates that the player |winnerᵢ| defeated player |loserᵢ| in a
// match. Return a list |answer| of size |2| where:
//
//  • |answer[0]| is a list of all players that have not lost any matches.
//
//  • |answer[1]| is a list of all players that have lost exactly one match.
// The values in the two lists should be returned in increasing order.
// Note:
//
//  • You should only consider the players that have played at least one match.
//
//  • The testcases will be generated such that no two matches will have the
//  same outcome.
//

LEETCODE_BEGIN_RESOLVING(2225, FindPlayersWithZeroOrOneLosses, Solution);

class Solution {
public:
  vector<vector<int>> findWinners(vector<vector<int>> &matches) {
    auto loss_map = unordered_map<int, int>();
    for (auto &v : matches) {
      if (!loss_map.count(v[0])) {
        loss_map[v[0]] = 0;
      }

      ++loss_map[v[1]];
    }

    auto res = vector<vector<int>>(2, vector<int>());

    for (auto [player, loss_cnt] : loss_map) {
      if (loss_cnt == 0) {
        res[0].emplace_back(player);
      } else if (loss_cnt == 1) {
        res[1].emplace_back(player);
      }
    }

    sort(res[0].begin(), res[0].end());
    sort(res[1].begin(), res[1].end());

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= matches.length <= 10⁵|
// * |matches[i].length == 2|
// * |1 <= winnerᵢ, loserᵢ <= 10⁵|
// * |winnerᵢ != loserᵢ|
// * All |matches[i]| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matches =
//  [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
// Output: [[1,2,10],[4,5,7,8]]
//
// Players 1, 2, and 10 have not lost any matches.
// Players 4, 5, 7, and 8 each have lost one match.
// Players 3, 6, and 9 each have lost two matches.
// Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].

LEETCODE_SOLUTION_UNITTEST(2225, FindPlayersWithZeroOrOneLosses, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matches  = {
      { 1, 3},
      { 2, 3},
      { 3, 6},
      { 5, 6},
      { 5, 7},
      { 4, 5},
      { 4, 8},
      { 4, 9},
      {10, 4},
      {10, 9}
  };
  vector<vector<int>> expect = {
      {1, 2, 10},
      {4, 5, 7, 8}
  };
  vector<vector<int>> actual = solution->findWinners(matches);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matches = [[2,3],[1,3],[5,4],[6,4]]
// Output: [[1,2,5,6],[]]
//
// Players 1, 2, 5, and 6 have not lost any matches.
// Players 3 and 4 each have lost two matches.
// Thus, answer[0] = [1,2,5,6] and answer[1] = [].

LEETCODE_SOLUTION_UNITTEST(2225, FindPlayersWithZeroOrOneLosses, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matches  = {
      {2, 3},
      {1, 3},
      {5, 4},
      {6, 4}
  };
  vector<vector<int>> expect = {
      {1, 2, 5, 6},
      {}
  };
  vector<vector<int>> actual = solution->findWinners(matches);
  LCD_EXPECT_EQ(expect, actual);
}
