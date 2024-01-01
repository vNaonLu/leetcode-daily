// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Split Strings by Separator
//
// https://leetcode.com/problems/split-strings-by-separator/
//
// Question ID: 2788
// Difficult  : Easy
// Solve Date : 2024/01/01 14:09

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2788. Split Strings by Separator|:
//
// Given an array of strings |words| and a character |separator|, split each
// string in |words| by |separator|. Return an array of strings containing the
// new strings formed after the splits, excluding empty strings. Notes
//
//  • |separator| is used to determine where the split should occur, but it is
//  not included as part of the resulting strings.
//
//  • A split may result in more than two strings.
//
//  • The resulting strings must maintain the same order as they were initially
//  given.
//
//

LEETCODE_BEGIN_RESOLVING(2788, SplitStringsBySeparator, Solution);

class Solution {
public:
  vector<string> splitWordsBySeparator(vector<string> &words, char separator) {
    vector<string> res;
    for (auto &s : words) {
      auto beg = s.begin();
      auto it  = beg;
      while (it != s.end()) {
        if (*it == separator) {
          if (it != beg) {
            res.emplace_back(beg, it);
          }
          beg = ++it;
        } else {
          ++it;
        }
      }
      if (it != beg) {
        res.emplace_back(beg, it);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 20|
// * characters in |words[i]| are either lowercase English letters or characters
// from the string |".,|$#@"| (excluding the quotes)
// * |separator| is a character from the string |".,|$#@"| (excluding the
// quotes)
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["one.two.three","four.five","six"], separator = "."
// Output: ["one","two","three","four","five","six"]
//
// In this example we split as follows:
// "one.two.three" splits into "one", "two", "three"
// "four.five" splits into "four", "five"
// "six" splits into "six"
// Hence, the resulting array is ["one","two","three","four","five","six"].

LEETCODE_SOLUTION_UNITTEST(2788, SplitStringsBySeparator, example_1) {
  auto           solution  = MakeSolution();
  vector<string> words     = {"one.two.three", "four.five", "six"};
  char           separator = '.';
  vector<string> expect    = {"one", "two", "three", "four", "five", "six"};
  vector<string> actual    = solution->splitWordsBySeparator(words, separator);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["$easy$","$problem$"], separator = "$"
// Output: ["easy","problem"]
//
// In this example we split as follows:
// "$easy$" splits into "easy" (excluding empty strings)
// "$problem$" splits into "problem" (excluding empty strings)
// Hence, the resulting array is ["easy","problem"].

LEETCODE_SOLUTION_UNITTEST(2788, SplitStringsBySeparator, example_2) {
  auto           solution  = MakeSolution();
  vector<string> words     = {"$easy$", "$problem$"};
  char           separator = '$';
  vector<string> expect    = {"easy", "problem"};
  vector<string> actual    = solution->splitWordsBySeparator(words, separator);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["|||"], separator = "|"
// Output: []
//
// In this example the resulting split of "|||" will contain only empty strings,
// so we return an empty array [].

LEETCODE_SOLUTION_UNITTEST(2788, SplitStringsBySeparator, example_3) {
  auto           solution  = MakeSolution();
  vector<string> words     = {"|||"};
  char           separator = '|';
  vector<string> expect    = {};
  vector<string> actual    = solution->splitWordsBySeparator(words, separator);
  LCD_EXPECT_EQ(expect, actual);
}
