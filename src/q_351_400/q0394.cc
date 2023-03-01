// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decode String
//
// https://leetcode.com/problems/decode-string/
//
// Question ID: 394
// Difficult  : Medium
// Solve Date : 2021/12/19 17:38

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |394. Decode String|:
//
// Given an encoded string, return its decoded string.
// The encoding rule is: |k[encoded_string]|, where the |encoded_string| inside
// the square brackets is being repeated exactly |k| times. Note that |k| is
// guaranteed to be a positive integer. You may assume that the input string is
// always valid; there are no extra white spaces, square brackets are
// well-formed, etc. Furthermore, you may assume that the original data does not
// contain any digits and that digits are only for those repeat numbers, |k|.
// For example, there will not be input like |3a| or |2[4]|. The test cases are
// generated so that the length of the output will never exceed |10⁵|.  
//

LEETCODE_BEGIN_RESOLVING(394, DecodeString, Solution);

class Solution {
private:
  template <typename Iterator>
  int toInteger(Iterator beg, Iterator end) {
    auto res = 0;
    while (beg != end) {
      res = res * 10 + (*beg++ - '0');
    }
    return res;
  }

  template <typename Iterator>
  Iterator findDigit(Iterator beg, Iterator end) {
    while (beg != end) {
      if (!isdigit(*beg)) {
        return beg;
      }
      ++beg;
    }
    return end;
  }

  template <typename Iterator>
  Iterator findPair(Iterator beg, Iterator end) {
    /// the first must be '['
    assert(*beg == '[');
    auto cnt = (int)1;
    while (++beg != end) {
      if (*beg == '[') {
        ++cnt;
      } else if (*beg == ']') {
        if (--cnt == 0) {
          return beg;
        }
      }
    }
    return end;
  }

  template <typename Iterator>
  string solve(Iterator beg, Iterator end) {
    auto res   = string("");
    auto it    = beg;
    auto times = (int)1;
    while (it != end) {
      if (*it == '[') {
        auto next = findPair(it, end);
        auto sub  = solve(++it, next);
        auto cnt  = (int)0;
        while (++cnt <= times) {
          res += sub;
        }
        times = (int)1;
        it    = ++next; /// *next == ']'
      } else if (isdigit(*it)) {
        auto next = findDigit(it, end);
        times     = toInteger(it, next);
        it        = next;
      } else {
        res += *it++;
      }
    }
    return res;
  }

public:
  string decodeString(string s) { return solve(s.begin(), s.end()); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 30|
// * |s| consists of lowercase English letters, digits, and square brackets
// |'[]'|.
// * |s| is guaranteed to be a valid input.
// * All the integers in |s| are in the range |[1, 300]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "3[a]2[bc]"
// Output: "aaabcbc"
//

LEETCODE_SOLUTION_UNITTEST(394, DecodeString, example_1) {
  auto   solution = MakeSolution();
  string s        = "3[a]2[bc]";
  string expect   = "aaabcbc";
  string actual   = solution->decodeString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "3[a2[c]]"
// Output: "accaccacc"
//

LEETCODE_SOLUTION_UNITTEST(394, DecodeString, example_2) {
  auto   solution = MakeSolution();
  string s        = "3[a2[c]]";
  string expect   = "accaccacc";
  string actual   = solution->decodeString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "2[abc]3[cd]ef"
// Output: "abcabccdcdcdef"
//

LEETCODE_SOLUTION_UNITTEST(394, DecodeString, example_3) {
  auto   solution = MakeSolution();
  string s        = "2[abc]3[cd]ef";
  string expect   = "abcabccdcdcdef";
  string actual   = solution->decodeString(s);
  LCD_EXPECT_EQ(expect, actual);
}
