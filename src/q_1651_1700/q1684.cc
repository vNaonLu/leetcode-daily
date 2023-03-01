// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count the Number of Consistent Strings
//
// https://leetcode.com/problems/count-the-number-of-consistent-strings/
//
// Question ID: 1684
// Difficult  : Easy
// Solve Date : 2022/12/21 20:29

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1684. Count the Number of Consistent Strings|:
//
// You are given a string |allowed| consisting of distinct characters and an
// array of strings |words|. A string is consistent if all characters in the
// string appear in the string |allowed|. Return the number of consistent
// strings in the array |words|.
//

LEETCODE_BEGIN_RESOLVING(1684, CountTheNumberOfConsistentStrings, Solution);

class Solution {
private:
  template <typename It>
  bool isAllow(vector<bool> &memo, It beg, It end) {
    while (beg != end && memo[*beg - 'a']) {
      ++beg;
    }
    return beg == end;
  }

public:
  int countConsistentStrings(string allowed, vector<string> &words) {
    auto memo = vector<bool>(26, false);
    auto res  = (int)0;
    for (auto c : allowed) {
      memo[c - 'a'] = true;
    }
    for (auto &s : words) {
      if (isAllow(memo, s.begin(), s.end())) {
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
// * |1 <= words.length <= 10⁴|
// * |1 <= allowed.length <=^{ }26|
// * |1 <= words[i].length <= 10|
// * The characters in |allowed| are distinct.
// * |words[i]| and |allowed| contain only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
// Output: 2
//
// Strings "aaab" and "baa" are consistent since they only contain characters
// 'a' and 'b'.

LEETCODE_SOLUTION_UNITTEST(1684, CountTheNumberOfConsistentStrings, example_1) {
  auto           solution = MakeSolution();
  string         allowed  = "ab";
  vector<string> words    = {"ad", "bd", "aaab", "baa", "badab"};
  int            expect   = 2;
  int            actual   = solution->countConsistentStrings(allowed, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
// Output: 7
//
// All strings are consistent.

LEETCODE_SOLUTION_UNITTEST(1684, CountTheNumberOfConsistentStrings, example_2) {
  auto           solution = MakeSolution();
  string         allowed  = "abc";
  vector<string> words    = {"a", "b", "c", "ab", "ac", "bc", "abc"};
  int            expect   = 7;
  int            actual   = solution->countConsistentStrings(allowed, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
// Output: 4
//
// Strings "cc", "acd", "ac", and "d" are consistent.

LEETCODE_SOLUTION_UNITTEST(1684, CountTheNumberOfConsistentStrings, example_3) {
  auto           solution = MakeSolution();
  string         allowed  = "cad";
  vector<string> words    = {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"};
  int            expect   = 4;
  int            actual   = solution->countConsistentStrings(allowed, words);
  LCD_EXPECT_EQ(expect, actual);
}
