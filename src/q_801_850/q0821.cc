// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Distance to a Character
//
// https://leetcode.com/problems/shortest-distance-to-a-character/
//
// Question ID: 821
// Difficult  : Easy
// Solve Date : 2022/10/08 14:21

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |821. Shortest Distance to a Character|:
//
// Given a string |s| and a character |c| that occurs in |s|, return an array of
// integers |answer| where |answer.length == s.length| and |answer[i]| is the
// distance from index |i| to the closest occurrence of character |c| in |s|.
// The distance between two indices |i| and |j| is |abs(i - j)|, where |abs| is
// the absolute value function.
//

LEETCODE_BEGIN_RESOLVING(821, ShortestDistanceToACharacter, Solution);

class Solution {
public:
  vector<int> shortestToChar(string s, char c) {
    auto res  = vector<int>(s.size(), s.size());
    auto prev = (int)-s.size();
    auto lo   = (int)0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == c) {
        while (lo != i) {
          res[lo] = min(lo - prev, i - lo);
          ++lo;
        }
        res[i] = 0;
        prev   = i;
      }
    }
    while (lo < res.size()) {
      res[lo] = lo - prev;
      ++lo;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s[i]| and |c| are lowercase English letters.
// * It is guaranteed that |c| occurs at least once in |s|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "loveleetcode", c = "e"
// Output: [3,2,1,0,1,0,0,1,2,2,1,0]
//
// The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
// The closest occurrence of 'e' for index 0 is at index 3, so the distance is
// abs(0 - 3) = 3. The closest occurrence of 'e' for index 1 is at index 3, so
// the distance is abs(1 - 3) = 2. For index 4, there is a tie between the 'e'
// at index 3 and the 'e' at index 5, but the distance is still the same: abs(4
// - 3) == abs(4 - 5) = 1. The closest occurrence of 'e' for index 8 is at index
// 6, so the distance is abs(8 - 6) = 2.

LEETCODE_SOLUTION_UNITTEST(821, ShortestDistanceToACharacter, example_1) {
  auto        solution = MakeSolution();
  string      s        = "loveleetcode";
  char        c        = 'e';
  vector<int> expect   = {3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0};
  vector<int> actual   = solution->shortestToChar(s, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaab", c = "b"
// Output: [3,2,1,0]
//

LEETCODE_SOLUTION_UNITTEST(821, ShortestDistanceToACharacter, example_2) {
  auto        solution = MakeSolution();
  string      s        = "aaab";
  char        c        = 'b';
  vector<int> expect   = {3, 2, 1, 0};
  vector<int> actual   = solution->shortestToChar(s, c);
  LCD_EXPECT_EQ(expect, actual);
}
