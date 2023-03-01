// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse String II
//
// https://leetcode.com/problems/reverse-string-ii/
//
// Question ID: 541
// Difficult  : Easy
// Solve Date : 2022/09/13 18:08

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |541. Reverse String II|:
//
// Given a string |s| and an integer |k|, reverse the first |k| characters for
// every |2k| characters counting from the start of the string. If there are
// fewer than |k| characters left, reverse all of them. If there are less than
// |2k| but greater than or equal to |k| characters, then reverse the first |k|
// characters and leave the other as original.
//

LEETCODE_BEGIN_RESOLVING(541, ReverseStringII, Solution);

class Solution {
public:
  string reverseStr(string s, int k) {
    auto beg = s.begin();
    while (distance(beg, s.end()) > k) {
      reverse(beg, beg + k);
      beg += min<int>(2 * k, distance(beg, s.end()));
    }
    reverse(beg, s.end());
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of only lowercase English letters.
// * |1 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcdefg", k = 2
// Output: "bacdfeg"
//

LEETCODE_SOLUTION_UNITTEST(541, ReverseStringII, example_1) {
  auto   solution = MakeSolution();
  string s        = "abcdefg";
  int    k        = 2;
  string expect   = "bacdfeg";
  string actual   = solution->reverseStr(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd", k = 2
// Output: "bacd"
//

LEETCODE_SOLUTION_UNITTEST(541, ReverseStringII, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  int    k        = 2;
  string expect   = "bacd";
  string actual   = solution->reverseStr(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
