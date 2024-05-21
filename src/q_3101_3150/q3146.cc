// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Permutation Difference between Two Strings
//
// https://leetcode.com/problems/permutation-difference-between-two-strings/
//
// Question ID: 3146
// Difficult  : Easy
// Solve Date : 2024/05/21 20:44

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3146. Permutation Difference between Two Strings|:
//
// You are given two strings |s| and |t| such that every character occurs at
// most once in |s| and |t| is a permutation of |s|. The permutation difference
// between |s| and |t| is defined as the sum of the absolute difference between
// the index of the occurrence of each character in |s| and the index of the
// occurrence of the same character in |t|. Return the permutation difference
// between |s| and |t|.
//
//

LEETCODE_BEGIN_RESOLVING(3146, PermutationDifferenceBetweenTwoStrings,
                         Solution);

class Solution {
public:
  int findPermutationDifference(string s, string t) {
    vector<int> pos(26, 0);
    for (int i = 0; i < s.size(); ++i) {
      pos[s[i] - 'a'] = i;
    }
    int res = 0;
    for (int i = 0; i < t.size(); ++i) {
      res += abs(pos[t[i] - 'a'] - i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 26|
// * Each character occurs at most once in |s|.
// * |t| is a permutation of |s|.
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc", t = "bac"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3146, PermutationDifferenceBetweenTwoStrings,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abc";
  string t        = "bac";
  int    expect   = 2;
  int    actual   = solution->findPermutationDifference(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcde", t = "edbac"
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(3146, PermutationDifferenceBetweenTwoStrings,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcde";
  string t        = "edbac";
  int    expect   = 12;
  int    actual   = solution->findPermutationDifference(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
