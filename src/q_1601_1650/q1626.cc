// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Team With No Conflicts
//
// https://leetcode.com/problems/best-team-with-no-conflicts/
//
// Question ID: 1626
// Difficult  : Medium
// Solve Date : 2023/01/31 20:56

#include <algorithm>
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1626. Best Team With No Conflicts|:
//
// You are the manager of a basketball team. For the upcoming tournament, you
// want to choose the team with the highest overall score. The score of the team
// is the sum of scores of all the players in the team. However, the basketball
// team is not allowed to have conflicts. A conflict exists if a younger player
// has a strictly higher score than an older player. A conflict does not occur
// between players of the same age. Given two lists, |scores| and |ages|, where
// each |scores[i]| and |ages[i]| represents the score and age of the |iᵗʰ|
// player, respectively, return the highest overall score of all possible
// basketball teams.
//

LEETCODE_BEGIN_RESOLVING(1626, BestTeamWithNoConflicts, Solution);

class Solution {
public:
  int bestTeamScore(vector<int> &scores, vector<int> &ages) {
    vector<pair<int, int>> items;
    for (int i = 0; i < scores.size(); ++i) {
      items.emplace_back(scores[i], ages[i]);
    }
    sort(items.begin(), items.end());

    map<int, int> res;
    res[0] = 0;
    for (auto [score, age] : items) {
      auto iter0  = res.upper_bound(age);
      int  score2 = score + (--iter0)->second;
      auto iter   = res.insert(iter0, {age, score2});
      if (iter->second < score2) {
        iter->second = score2;
      }
      ++iter;
      while (iter != res.end() && iter->second <= score2) {
        auto it2 = iter++;
        res.erase(it2);
      }
    }
    return res.rbegin()->second;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= scores.length, ages.length <= 1000|
// * |scores.length == ages.length|
// * |1 <= scores[i] <= 10⁶|
// * |1 <= ages[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
// Output: 34
//
// You can choose all the players.

LEETCODE_SOLUTION_UNITTEST(1626, BestTeamWithNoConflicts, example_1) {
  auto        solution = MakeSolution();
  vector<int> scores   = {1, 3, 5, 10, 15};
  vector<int> ages     = {1, 2, 3, 4, 5};
  int         expect   = 34;
  int         actual   = solution->bestTeamScore(scores, ages);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: scores = [4,5,6,5], ages = [2,1,2,1]
// Output: 16
//
// It is best to choose the last 3 players. Notice that you are allowed to
// choose multiple people of the same age.

LEETCODE_SOLUTION_UNITTEST(1626, BestTeamWithNoConflicts, example_2) {
  auto        solution = MakeSolution();
  vector<int> scores   = {4, 5, 6, 5};
  vector<int> ages     = {2, 1, 2, 1};
  int         expect   = 16;
  int         actual   = solution->bestTeamScore(scores, ages);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: scores = [1,2,3,5], ages = [8,9,10,1]
// Output: 6
//
// It is best to choose the first 3 players.

LEETCODE_SOLUTION_UNITTEST(1626, BestTeamWithNoConflicts, example_3) {
  auto        solution = MakeSolution();
  vector<int> scores   = {1, 2, 3, 5};
  vector<int> ages     = {8, 9, 10, 1};
  int         expect   = 6;
  int         actual   = solution->bestTeamScore(scores, ages);
  LCD_EXPECT_EQ(expect, actual);
}
