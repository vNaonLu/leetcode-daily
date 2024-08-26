// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find And Replace in String
//
// https://leetcode.com/problems/find-and-replace-in-string/
//
// Question ID: 833
// Difficult  : Medium
// Solve Date : 2024/08/22 20:10

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |833. Find And Replace in String|:
//
// You are given a 0-indexed string |s| that you must perform |k| replacement
// operations on. The replacement operations are given as three 0-indexed
// parallel arrays, |indices|, |sources|, and |targets|, all of length |k|. To
// complete the |iᵗʰ| replacement operation:
//
//  1. Check if the substring |sources[i]| occurs at index |indices[i]| in the
//  original string |s|.
//
//  2. If it does not occur, do nothing.
//
//  3. Otherwise if it does occur, replace that substring with |targets[i]|.
// For example, if |s = "abcd"|, |indices[i] = 0|, |sources[i] = "ab"|, and
// |targets[i] = "eee"|, then the result of this replacement will be |"eeecd"|.
// All replacement operations must occur simultaneously, meaning the replacement
// operations should not affect the indexing of each other. The testcases will
// be generated such that the replacements will not overlap.
//
//  • For example, a testcase with |s = "abc"|, |indices = [0, 1]|, and |sources
//  = ["ab","bc"]| will not be generated because the |"ab"| and |"bc"|
//  replacements overlap.
// Return the resulting string after performing all replacement operations on
// |s|. A substring is a contiguous sequence of characters in a string.
//
//

LEETCODE_BEGIN_RESOLVING(833, FindAndReplaceInString, Solution);

class Solution {
public:
  string findReplaceString(string s, vector<int> &indices,
                           vector<string> &sources, vector<string> &targets) {
    map<int, pair<int, string>, greater<int>> mp;
    for (int i = 0; i < indices.size(); ++i) {
      if (s.compare(indices[i], sources[i].size(), sources[i]) == 0) {
        mp.emplace(indices[i], make_pair(sources[i].size(), targets[i]));
      }
    }

    for (auto &[i, rp] : mp) {
      s.replace(i, rp.first, rp.second);
    }

    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |k == indices.length == sources.length == targets.length|
// * |1 <= k <= 100|
// * |0 <= indexes[i] < s.length|
// * |1 <= sources[i].length, targets[i].length <= 50|
// * |s| consists of only lowercase English letters.
// * |sources[i]| and |targets[i]| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets =
//  ["eee", "ffff"]
// Output: "eeebffff"
//

LEETCODE_SOLUTION_UNITTEST(833, FindAndReplaceInString, example_1) {
  auto           solution = MakeSolution();
  string         s        = "abcd";
  vector<int>    indices  = {0, 2};
  vector<string> sources  = {"a", "cd"};
  vector<string> targets  = {"eee", "ffff"};
  string         expect   = "eeebffff";
  string actual = solution->findReplaceString(s, indices, sources, targets);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets =
//  ["eee","ffff"]
// Output: "eeecd"
//

LEETCODE_SOLUTION_UNITTEST(833, FindAndReplaceInString, example_2) {
  auto           solution = MakeSolution();
  string         s        = "abcd";
  vector<int>    indices  = {0, 2};
  vector<string> sources  = {"ab", "ec"};
  vector<string> targets  = {"eee", "ffff"};
  string         expect   = "eeecd";
  string actual = solution->findReplaceString(s, indices, sources, targets);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "abcdef"
// [2,2]
// ["feg","cdef"]
// ["abc","feg"]
// Output: "abfeg"
//

LEETCODE_SOLUTION_UNITTEST(833, FindAndReplaceInString, extra_testcase_1) {
  auto           solution = MakeSolution();
  string         s        = "abcdef";
  vector<int>    indices  = {2, 2};
  vector<string> sources  = {"feg", "cdef"};
  vector<string> targets  = {"abc", "feg"};
  string         expect   = "abfeg";
  string actual = solution->findReplaceString(s, indices, sources, targets);
  LCD_EXPECT_EQ(expect, actual);
}
