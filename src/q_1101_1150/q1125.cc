// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Sufficient Team
//
// https://leetcode.com/problems/smallest-sufficient-team/
//
// Question ID: 1125
// Difficult  : Hard
// Solve Date : 2023/07/16 13:35

#include <bitset>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1125. Smallest Sufficient Team|:
//
// In a project, you have a list of required skills |req_skills|, and a list of
// people. The |iᵗʰ| person |people[i]| contains a list of skills that the
// person has. Consider a sufficient team: a set of people such that for every
// required skill in |req_skills|, there is at least one person in the team who
// has that skill. We can represent these teams by the index of each person.
//
//  • For example, |team = [0, 1, 3]| represents the people with skills
//  |people[0]|, |people[1]|, and |people[3]|.
// Return any sufficient team of the smallest possible size, represented by the
// index of each person. You may return the answer in any order. It is
// guaranteed an answer exists.
//
//

LEETCODE_BEGIN_RESOLVING(1125, SmallestSufficientTeam, Solution);

class Solution {
public:
  vector<int> smallestSufficientTeam(vector<string>         &req_skills,
                                     vector<vector<string>> &people) {
    unordered_map<string, int> mp;
    vector<int>                mask(people.size(), 0);
    vector<int64_t> dp(1 << req_skills.size(), numeric_limits<int64_t>::max());
    for (int i = 0; i < req_skills.size(); ++i) {
      mp[req_skills[i]] = i;
    }

    for (int i = 0; i < people.size(); ++i) {
      for (auto &s : people[i]) {
        mask[i] |= (1 << mp[s]);
      }
    }

    auto choose = helper((1 << req_skills.size()) - 1, mask, dp, people.size());
    bitset<60>  b_choose(choose);
    vector<int> res;
    for (int i = 0; i < people.size(); ++i) {
      if (b_choose[i]) {
        res.emplace_back(i);
      }
    }
    return res;
  }

private:
  int64_t helper(int skill_had, vector<int> &mask, vector<int64_t> &dp, int n) {
    if (skill_had == 0) {
      return 0;
    }

    if (dp[skill_had] != numeric_limits<int64_t>::max()) {
      return dp[skill_had];
    }

    for (int i = 0; i < n; ++i) {
      int s = skill_had & ~mask[i];
      if (s != skill_had) {
        int64_t    choose = helper(s, mask, dp, n) | (1ll << i);
        bitset<60> b_choose(choose);

        if (b_choose.count() < bitset<60>(dp[skill_had]).count()) {
          dp[skill_had] = choose;
        }
      }
    }
    return dp[skill_had];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= req_skills.length <= 16|
// * |1 <= req_skills[i].length <= 16|
// * |req_skills[i]| consists of lowercase English letters.
// * All the strings of |req_skills| are unique.
// * |1 <= people.length <= 60|
// * |0 <= people[i].length <= 16|
// * |1 <= people[i][j].length <= 16|
// * |people[i][j]| consists of lowercase English letters.
// * All the strings of |people[i]| are unique.
// * Every skill in |people[i]| is a skill in |req_skills|.
// * It is guaranteed a sufficient team exists.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: req_skills = ["java","nodejs","reactjs"], people =
//  [["java"],["nodejs"],["nodejs","reactjs"]]
// Output: [0,2]
//

LEETCODE_SOLUTION_UNITTEST(1125, SmallestSufficientTeam, example_1) {
  auto                   solution   = MakeSolution();
  vector<string>         req_skills = {"java", "nodejs", "reactjs"};
  vector<vector<string>> people     = {
      {"java"},
      {"nodejs"},
      {"nodejs", "reactjs"}
  };
  vector<int> expect = {0, 2};
  vector<int> actual = solution->smallestSufficientTeam(req_skills, people);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
//  people =
//  [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(1125, SmallestSufficientTeam, example_2) {
  auto                   solution   = MakeSolution();
  vector<string>         req_skills = {"algorithms", "math",   "java",
                                       "reactjs",    "csharp", "aws"};
  vector<vector<string>> people     = {
      {"algorithms", "math", "java"},
      {"algorithms", "math", "reactjs"},
      {"java", "csharp", "aws"},
      {"reactjs", "csharp"},
      {"csharp", "math"},
      {"aws", "java"}
  };
  vector<int> expect = {1, 2};
  vector<int> actual = solution->smallestSufficientTeam(req_skills, people);
  EXPECT_ANYORDER_EQ(expect, actual);
}
