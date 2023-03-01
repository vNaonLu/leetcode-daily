// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If String Is a Prefix of Array
//
// https://leetcode.com/problems/check-if-string-is-a-prefix-of-array/
//
// Question ID: 1961
// Difficult  : Easy
// Solve Date : 2022/12/30 18:14

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1961. Check If String Is a Prefix of Array|:
//
// Given a string |s| and an array of strings |words|, determine whether |s| is
// a prefix string of |words|. A string |s| is a prefix string of |words| if |s|
// can be made by concatenating the first |k| strings in |words| for some
// positive |k| no larger than |words.length|. Return |true| if |s| is a prefix
// string of |words|, or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1961, CheckIfStringIsAPrefixOfArray, Solution);

class Solution {
public:
  bool isPrefixString(string s, vector<string> &words) {
    string tmp = "";
    for (auto &w : words) {
      tmp += w;
      if (tmp.size() >= s.size()) {
        break;
      }
    }
    return tmp == s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 20|
// * |1 <= s.length <= 1000|
// * |words[i]| and |s| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
// Output: true
//
// s can be made by concatenating "i", "love", and "leetcode" together.

LEETCODE_SOLUTION_UNITTEST(1961, CheckIfStringIsAPrefixOfArray, example_1) {
  auto           solution = MakeSolution();
  string         s        = "iloveleetcode";
  vector<string> words    = {"i", "love", "leetcode", "apples"};
  bool           expect   = true;
  bool           actual   = solution->isPrefixString(s, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "iloveleetcode", words = ["apples","i","love","leetcode"]
// Output: false
//
// It is impossible to make s using a prefix of arr.

LEETCODE_SOLUTION_UNITTEST(1961, CheckIfStringIsAPrefixOfArray, example_2) {
  auto           solution = MakeSolution();
  string         s        = "iloveleetcode";
  vector<string> words    = {"apples", "i", "love", "leetcode"};
  bool           expect   = false;
  bool           actual   = solution->isPrefixString(s, words);
  LCD_EXPECT_EQ(expect, actual);
}
