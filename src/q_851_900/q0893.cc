// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Groups of Special-Equivalent Strings
//
// https://leetcode.com/problems/groups-of-special-equivalent-strings/
//
// Question ID: 893
// Difficult  : Medium
// Solve Date : 2024/09/20 22:50

#include <algorithm>
#include <iosfwd>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |893. Groups of Special-Equivalent Strings|:
//
// You are given an array of strings of the same length |words|.
// In one move, you can swap any two even indexed characters or any two odd
// indexed characters of a string |words[i]|. Two strings |words[i]| and
// |words[j]| are special-equivalent if after any number of moves, |words[i] ==
// words[j]|.
//
//  • For example, |words[i] = "zzxy"| and |words[j] = "xyzz"| are
//  special-equivalent because we may make the moves |"zzxy" -> "xzzy" ->
//  "xyzz"|.
// A group of special-equivalent strings from |words| is a non-empty subset of
// words such that:
//
//  • Every pair of strings in the group are special equivalent, and
//
//  • The group is the largest size possible (i.e., there is not a string
//  |words[i]| not in the group such that |words[i]| is special-equivalent to
//  every string in the group).
// Return the number of groups of special-equivalent strings from |words|.
//
//

LEETCODE_BEGIN_RESOLVING(893, GroupsOfSpecialEquivalentStrings, Solution);

class Solution {
public:
  int numSpecialEquivGroups(vector<string> &words) {
    set<string> res;
    for (auto &x : words) {
      string q;
      string w;
      q.reserve(x.size());
      w.reserve(x.size());
      for (int i = 0; i < x.size(); ++i) {
        if (i & 1) {
          q += x[i];
        } else {
          w += x[i];
        }
      }
      sort(q.begin(), q.end());
      sort(w.begin(), w.end());
      res.emplace(std::move(q) + std::move(w));
    }
    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 20|
// * |words[i]| consist of lowercase English letters.
// * All the strings are of the same length.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abcd","cdab","cbad","xyzz","zzxy","zzyx"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(893, GroupsOfSpecialEquivalentStrings, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abcd", "cdab", "cbad", "xyzz", "zzxy", "zzyx"};
  int            expect   = 3;
  int            actual   = solution->numSpecialEquivGroups(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["abc","acb","bac","bca","cab","cba"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(893, GroupsOfSpecialEquivalentStrings, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "acb", "bac", "bca", "cab", "cba"};
  int            expect   = 3;
  int            actual   = solution->numSpecialEquivGroups(words);
  LCD_EXPECT_EQ(expect, actual);
}
