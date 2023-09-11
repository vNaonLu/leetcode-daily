// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Extra Characters in a String
//
// https://leetcode.com/problems/extra-characters-in-a-string/
//
// Question ID: 2707
// Difficult  : Medium
// Solve Date : 2023/09/02 10:17

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2707. Extra Characters in a String|:
//
// You are given a 0-indexed string |s| and a dictionary of words |dictionary|.
// You have to break |s| into one or more non-overlapping substrings such that
// each substring is present in |dictionary|. There may be some extra characters
// in |s| which are not present in any of the substrings. Return the minimum
// number of extra characters left over if you break up |s| optimally.
//
//

LEETCODE_BEGIN_RESOLVING(2707, ExtraCharactersInAString, Solution);

class Solution {
public:
  int minExtraChar(string s, vector<string> &dictionary) {
    map<string, int> mp;
    vector<int>      dp(s.size(), -1);
    for (auto &c : dictionary) {
      ++mp[c];
    }
    return helper(0, s, &dp, mp);
  }

private:
  int helper(int i, const string &s, vector<int> *dp, map<string, int> &mp) {
    if (i >= s.size()) {
      return 0;
    }
    if ((*dp)[i] != -1) {
      return (*dp)[i];
    }
    int    res = 1 + helper(i + 1, s, dp, mp);
    string k   = "";
    for (int j = i; j < s.size(); ++j) {
      k += s[j];
      if (mp[k]) {
        res = min(res, helper(j + 1, s, dp, mp));
      }
    }
    return (*dp)[i] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 50|
// * |1 <= dictionary.length <= 50|
// * |1 <= dictionary[i].length <= 50|
// * |dictionary[i]| and |s| consists of only lowercase English letters
// * |dictionary| contains distinct words
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
// Output: 1
//
// We can break s in two substrings: "leet" from index 0 to 3 and "code" from
// index 5 to 8. There is only 1 unused character (at index 4), so we return 1.

LEETCODE_SOLUTION_UNITTEST(2707, ExtraCharactersInAString, example_1) {
  auto           solution   = MakeSolution();
  string         s          = "leetscode";
  vector<string> dictionary = {"leet", "code", "leetcode"};
  int            expect     = 1;
  int            actual     = solution->minExtraChar(s, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "sayhelloworld", dictionary = ["hello","world"]
// Output: 3
//
// We can break s in two substrings: "hello" from index 3 to 7 and "world" from
// index 8 to 12. The characters at indices 0, 1, 2 are not used in any
// substring and thus are considered as extra characters. Hence, we return 3.

LEETCODE_SOLUTION_UNITTEST(2707, ExtraCharactersInAString, example_2) {
  auto           solution   = MakeSolution();
  string         s          = "sayhelloworld";
  vector<string> dictionary = {"hello", "world"};
  int            expect     = 3;
  int            actual     = solution->minExtraChar(s, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}
