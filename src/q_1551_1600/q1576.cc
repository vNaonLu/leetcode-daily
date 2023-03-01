// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Replace All ?'s to Avoid Consecutive Repeating Characters
//
// https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/
//
// Question ID: 1576
// Difficult  : Easy
// Solve Date : 2022/07/03 14:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1576. Replace All ?'s to Avoid Consecutive Repeating
// Characters|:
//
// Given a string |s| containing only lowercase English letters and the |'?'|
// character, convert all the |'?'| characters into lowercase letters such that
// the final string does not contain any consecutive repeating characters. You
// cannot modify the non |'?'| characters. It is guaranteed that there are no
// consecutive repeating characters in the given string except for |'?'|. Return
// the final string after all the conversions (possibly zero) have been made. If
// there is more than one solution, return any of them. It can be shown that an
// answer is always possible with the given constraints.
//

LEETCODE_BEGIN_RESOLVING(1576, ReplaceAllSToAvoidConsecutiveRepeatingCharacters,
                         Solution);

class Solution {
public:
  string modifyString(string s) {
    string res = s;
    for (int i = 0; i < res.size(); ++i) {
      if (res[i] == '?') {
        char prev = i == 0 ? '?' : res[i - 1];
        char next = i == res.size() - 1 ? '?' : res[i + 1];

        for (auto repl = 'a'; repl <= 'z'; ++repl) {
          if (repl != prev && repl != next) {
            res[i] = repl;
            break;
          }
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consist of lowercase English letters and |'?'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "?zs"
// Output: "azs"
//
// There are 25 solutions for this problem. From "azs" to "yzs", all are valid.
// Only "z" is an invalid modification as the string will consist of consecutive
// repeating characters in "zzs".

LEETCODE_SOLUTION_UNITTEST(1576,
                           ReplaceAllSToAvoidConsecutiveRepeatingCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "?zs";
  string expect   = "azs";
  string actual   = solution->modifyString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ubv?w"
// Output: "ubvaw"
//
// There are 24 solutions for this problem. Only "v" and "w" are invalid
// modifications as the strings will consist of consecutive repeating characters
// in "ubvvw" and "ubvww".

LEETCODE_SOLUTION_UNITTEST(1576,
                           ReplaceAllSToAvoidConsecutiveRepeatingCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "ubv?w";
  string expect   = "ubvaw";
  string actual   = solution->modifyString(s);
  LCD_EXPECT_EQ(expect, actual);
}
