// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Words in a String III
//
// https://leetcode.com/problems/reverse-words-in-a-string-iii/
//
// Question ID: 557
// Difficult  : Easy
// Solve Date : 2021/09/08 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |557. Reverse Words in a String III|:
//
// Given a string |s|, reverse the order of characters in each word within a
// sentence while still preserving whitespace and initial word order.  
//

LEETCODE_BEGIN_RESOLVING(557, ReverseWordsinaStringIII, Solution);

class Solution {
public:
  string reverseWords(string s) {
    auto beg = s.begin();
    auto it  = s.begin();
    while (it != s.end()) {
      while (it != s.end() && *it == ' ') {
        ++it;
      }
      beg = it;
      while (it != s.end() && *it != ' ') {
        ++it;
      }
      reverse(beg, it);
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁴|
// * |s| contains printable ASCII characters.
// * |s| does not contain any leading or trailing spaces.
// * There is at least one word in |s|.
// * All the words in |s| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "Let's take LeetCode contest"
// Output: "s'teL ekat edoCteeL tsetnoc"
//

LEETCODE_SOLUTION_UNITTEST(557, ReverseWordsinaStringIII, example_1) {
  auto   solution = MakeSolution();
  string s        = "Let's take LeetCode contest";
  string expect   = "s'teL ekat edoCteeL tsetnoc";
  string actual   = solution->reverseWords(s);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "God Ding"
// Output: "doG gniD"
//

LEETCODE_SOLUTION_UNITTEST(557, ReverseWordsinaStringIII, example_2) {
  auto   solution = MakeSolution();
  string s        = "God Ding";
  string expect   = "doG gniD";
  string actual   = solution->reverseWords(s);
  EXPECT_EQ(expect, actual);
}
