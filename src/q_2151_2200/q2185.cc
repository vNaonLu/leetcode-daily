// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Counting Words With a Given Prefix
//
// https://leetcode.com/problems/counting-words-with-a-given-prefix/
//
// Question ID: 2185
// Difficult  : Easy
// Solve Date : 2023/03/12 16:59

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2185. Counting Words With a Given Prefix|:
//
// You are given an array of strings |words| and a string |pref|.
// Return the number of strings in |words| that contain |pref| as a prefix.
// A prefix of a string |s| is any leading contiguous substring of |s|.
//

LEETCODE_BEGIN_RESOLVING(2185, CountingWordsWithAGivenPrefix, Solution);

class Solution {
public:
  int prefixCount(vector<string> &words, string pref) {
    int res = 0;
    for (string_view sv : words) {
      if (sv.size() >= pref.size() && sv.substr(0, pref.size()) == pref) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length, pref.length <= 100|
// * |words[i]| and |pref| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["pay","attention","practice","attend"], pref = "at"
// Output: 2
//
// The 2 strings that contain "at" as a prefix are: "attention" and "attend".

LEETCODE_SOLUTION_UNITTEST(2185, CountingWordsWithAGivenPrefix, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"pay", "attention", "practice", "attend"};
  string         pref     = "at";
  int            expect   = 2;
  int            actual   = solution->prefixCount(words, pref);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["leetcode","win","loops","success"], pref = "code"
// Output: 0
//
// There are no strings that contain "code" as a prefix.

LEETCODE_SOLUTION_UNITTEST(2185, CountingWordsWithAGivenPrefix, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"leetcode", "win", "loops", "success"};
  string         pref     = "code";
  int            expect   = 0;
  int            actual   = solution->prefixCount(words, pref);
  LCD_EXPECT_EQ(expect, actual);
}
