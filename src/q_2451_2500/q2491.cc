// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Divide Players Into Teams of Equal Skill
//
// https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/
//
// Question ID: 2491
// Difficult  : Medium
// Solve Date : 2024/10/04 22:19

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2491. Divide Players Into Teams of Equal Skill|:
//
// You are given a positive integer array |skill| of even length |n| where
// |skill[i]| denotes the skill of the |iᵗʰ| player. Divide the players into |n
// / 2| teams of size |2| such that the total skill of each team is equal. The
// chemistry of a team is equal to the product of the skills of the players on
// that team. Return the sum of the chemistry of all the teams, or return |-1|
// if there is no way to divide the players into teams such that the total skill
// of each team is equal.
//
//

LEETCODE_BEGIN_RESOLVING(2491, DividePlayersIntoTeamsOfEqualSkill, Solution);

class Solution {
public:
  long long dividePlayers(vector<int> &skill) {
    int64_t                 res = 0;
    unordered_map<int, int> mp;
    int64_t                 sum = 0;
    for (auto x : skill) {
      ++mp[x];
      sum += x;
    }

    sum /= skill.size() / 2;

    for (auto &[x, cnt] : mp) {
      if (cnt == 0) {
        continue;
      }
      if (auto it = mp.find(sum - x); it == mp.end()) {
        return -1;
      } else {
        while (cnt > 0 && it->second > 0) {
          --cnt;
          --it->second;
          res += x * it->first;
        }

        if (cnt != 0 || it->second != 0) {
          return -1;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= skill.length <= 10⁵|
// * |skill.length| is even.
// * |1 <= skill[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: skill = [3,2,5,1,3,4]
// Output: 22
//

LEETCODE_SOLUTION_UNITTEST(2491, DividePlayersIntoTeamsOfEqualSkill,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> skill    = {3, 2, 5, 1, 3, 4};
  long long   expect   = 22;
  long long   actual   = solution->dividePlayers(skill);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: skill = [3,4]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(2491, DividePlayersIntoTeamsOfEqualSkill,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> skill    = {3, 4};
  long long   expect   = 12;
  long long   actual   = solution->dividePlayers(skill);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: skill = [1,1,2,3]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2491, DividePlayersIntoTeamsOfEqualSkill,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> skill    = {1, 1, 2, 3};
  long long   expect   = -1;
  long long   actual   = solution->dividePlayers(skill);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [2,2,2,2]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2491, DividePlayersIntoTeamsOfEqualSkill,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> skill    = {2, 2, 2, 2};
  long long   expect   = 8;
  long long   actual   = solution->dividePlayers(skill);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [4,2,4,3]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2491, DividePlayersIntoTeamsOfEqualSkill,
                           extra_testcase_2) {
  auto        solution = MakeSolution();
  vector<int> skill    = {4, 2, 4, 3};
  long long   expect   = -1;
  long long   actual   = solution->dividePlayers(skill);
  LCD_EXPECT_EQ(expect, actual);
}
