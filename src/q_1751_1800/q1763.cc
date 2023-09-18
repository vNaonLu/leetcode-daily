// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Nice Substring
//
// https://leetcode.com/problems/longest-nice-substring/
//
// Question ID: 1763
// Difficult  : Easy
// Solve Date : 2023/09/12 19:07

#include <iosfwd>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1763. Longest Nice Substring|:
//
// A string |s| is nice if, for every letter of the alphabet that |s| contains,
// it appears both in uppercase and lowercase. For example, |"abABB"| is nice
// because |'A'| and |'a'| appear, and |'B'| and |'b'| appear. However, |"abA"|
// is not because |'b'| appears, but |'B'| does not. Given a string |s|, return
// the longest substring of |s| that is nice. If there are multiple, return the
// substring of the earliest occurrence. If there are none, return an empty
// string.
//
//

LEETCODE_BEGIN_RESOLVING(1763, LongestNiceSubstring, Solution);

class Solution {
public:
  string longestNiceSubstring(string s) {
    if (s.size() == 1) {
      return "";
    }

    unordered_set<char> uset;
    for (auto x : s) {
      uset.emplace(x);
    }
    for (int i = 0; i < s.size(); ++i) {
      if (uset.count(tolower(s[i])) && uset.count(toupper(s[i]))) {
        continue;
      }

      string prev = longestNiceSubstring(s.substr(0, i));
      string next = longestNiceSubstring(s.substr(i + 1));
      return prev.size() >= next.size() ? prev : next;
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of uppercase and lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "YazaAay"
// Output: "aAa"
//
// "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s,
// and both 'A' and 'a' appear. "aAa" is the longest nice substring.

LEETCODE_SOLUTION_UNITTEST(1763, LongestNiceSubstring, example_1) {
  auto   solution = MakeSolution();
  string s        = "YazaAay";
  string expect   = "aAa";
  string actual   = solution->longestNiceSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "Bb"
// Output: "Bb"
//
// "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a
// substring.

LEETCODE_SOLUTION_UNITTEST(1763, LongestNiceSubstring, example_2) {
  auto   solution = MakeSolution();
  string s        = "Bb";
  string expect   = "Bb";
  string actual   = solution->longestNiceSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "c"
// Output: ""
//
// There are no nice substrings.

LEETCODE_SOLUTION_UNITTEST(1763, LongestNiceSubstring, example_3) {
  auto   solution = MakeSolution();
  string s        = "c";
  string expect   = "";
  string actual   = solution->longestNiceSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}
