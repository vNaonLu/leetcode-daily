// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Special Binary String
//
// https://leetcode.com/problems/special-binary-string/
//
// Question ID: 761
// Difficult  : Hard
// Solve Date : 2026/02/20 11:32

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |761. Special Binary String|:
//
// Special binary strings are binary strings with the following two properties:
//
//  • The number of |0|'s is equal to the number of |1|'s.
//
//  • Every prefix of the binary string has at least as many |1|'s as |0|'s.
// You are given a special binary string |s|.
// A move consists of choosing two consecutive, non-empty, special substrings of
// |s|, and swapping them. Two strings are consecutive if the last character of
// the first string is exactly one index before the first character of the
// second string. Return the lexicographically largest resulting string possible
// after applying the mentioned operations on the string.
//
//

LEETCODE_BEGIN_RESOLVING(761, SpecialBinaryString, Solution);

class Solution {
public:
  string makeLargestSpecial(string s) {
    if (s.empty()) {
      return s;
    }
    vector<string> res;
    int            cnt = 0;
    for (int i = 0, j = 0; i < s.size(); ++i) {
      cnt += s[i] == '1' ? 1 : -1;
      if (cnt == 0) {
        res.emplace_back("1" + makeLargestSpecial(s.substr(j + 1, i - j - 1)) +
                         "0");
        j = i + 1;
      }
    }
    sort(res.begin(), res.end(), greater<string>{});
    return accumulate(res.begin(), res.end(), ""s);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 50|
// * |s[i]| is either |'0'| or |'1'|.
// * |s| is a special binary string.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "11011000"
// Output: "11100100"
//

LEETCODE_SOLUTION_UNITTEST(761, SpecialBinaryString, example_1) {
  auto   solution = MakeSolution();
  string s        = "11011000";
  string expect   = "11100100";
  string actual   = solution->makeLargestSpecial(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "10"
// Output: "10"
//

LEETCODE_SOLUTION_UNITTEST(761, SpecialBinaryString, example_2) {
  auto   solution = MakeSolution();
  string s        = "10";
  string expect   = "10";
  string actual   = solution->makeLargestSpecial(s);
  LCD_EXPECT_EQ(expect, actual);
}
