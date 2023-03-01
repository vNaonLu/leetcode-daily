// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Prefixes of a Given String
//
// https://leetcode.com/problems/count-prefixes-of-a-given-string/
//
// Question ID: 2255
// Difficult  : Easy
// Solve Date : 2023/01/08 21:09

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2255. Count Prefixes of a Given String|:
//
// You are given a string array |words| and a string |s|, where |words[i]| and
// |s| comprise only of lowercase English letters. Return the number of strings
// in |words| that are a prefix of |s|. A prefix of a string is a substring that
// occurs at the beginning of the string. A substring is a contiguous sequence
// of characters within a string.
//

LEETCODE_BEGIN_RESOLVING(2255, CountPrefixesOfAGivenString, Solution);

class Solution {
public:
  int countPrefixes(vector<string> &words, string s) {
    int res = 0;
    for (auto &w : words) {
      if (w == s.substr(0, w.size())) {
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
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length, s.length <= 10|
// * |words[i]| and |s| consist of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["a","b","c","ab","bc","abc"], s = "abc"
// Output: 3
//
// The strings in words which are a prefix of s = "abc" are:
// "a", "ab", and "abc".
// Thus the number of strings in words which are a prefix of s is 3.

LEETCODE_SOLUTION_UNITTEST(2255, CountPrefixesOfAGivenString, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "c", "ab", "bc", "abc"};
  string         s        = "abc";
  int            expect   = 3;
  int            actual   = solution->countPrefixes(words, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","a"], s = "aa"
// Output: 2
// Explanation:
// Both of the strings are a prefix of s.
// Note that the same string can occur multiple times in words, and it should be
// counted each time.
//

LEETCODE_SOLUTION_UNITTEST(2255, CountPrefixesOfAGivenString, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "a"};
  string         s        = "aa";
  int            expect   = 2;
  int            actual   = solution->countPrefixes(words, s);
  LCD_EXPECT_EQ(expect, actual);
}
