// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count of Matches in Tournament
//
// https://leetcode.com/problems/count-of-matches-in-tournament/
//
// Question ID: 1688
// Difficult  : Easy
// Solve Date : 2022/06/03 13:41

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1688. Count of Matches in Tournament|:
//
// You are given an integer |n|, the number of teams in a tournament that has
// strange rules:
//
//  • If the current number of teams is even, each team gets paired with another
//  team. A total of |n / 2| matches are played, and |n / 2| teams advance to
//  the next round.
//
//  • If the current number of teams is odd, one team randomly advances in the
//  tournament, and the rest gets paired. A total of |(n - 1) / 2| matches are
//  played, and |(n - 1) / 2 + 1| teams advance to the next round.
// Return the number of matches played in the tournament until a winner is
// decided.
//

LEETCODE_BEGIN_RESOLVING(1688, CountOfMatchesInTournament, Solution);

class Solution {
public:
  int numberOfMatches(int n) {
    int res = 0;

    while (n != 1) {
      auto x = n >> 1;
      res += x;
      n -= x;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7
// Output: 6
//
// Details of the tournament:
// - 1st Round: Teams = 7, Matches = 3, and 4 teams advance.
// - 2nd Round: Teams = 4, Matches = 2, and 2 teams advance.
// - 3rd Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
// Total number of matches = 3 + 2 + 1 = 6.

LEETCODE_SOLUTION_UNITTEST(1688, CountOfMatchesInTournament, example_1) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 6;
  int  actual   = solution->numberOfMatches(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 14
// Output: 13
//
// Details of the tournament:
// - 1st Round: Teams = 14, Matches = 7, and 7 teams advance.
// - 2nd Round: Teams = 7, Matches = 3, and 4 teams advance.
// - 3rd Round: Teams = 4, Matches = 2, and 2 teams advance.
// - 4th Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
// Total number of matches = 7 + 3 + 2 + 1 = 13.

LEETCODE_SOLUTION_UNITTEST(1688, CountOfMatchesInTournament, example_2) {
  auto solution = MakeSolution();
  int  n        = 14;
  int  expect   = 13;
  int  actual   = solution->numberOfMatches(n);
  LCD_EXPECT_EQ(expect, actual);
}
