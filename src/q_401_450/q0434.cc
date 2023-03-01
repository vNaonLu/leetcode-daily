// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Segments in a String
//
// https://leetcode.com/problems/number-of-segments-in-a-string/
//
// Question ID: 434
// Difficult  : Easy
// Solve Date : 2022/08/30 18:15

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |434. Number of Segments in a String|:
//
// Given a string |s|, return the number of segments in the string.
// A segment is defined to be a contiguous sequence of non-space characters.
//

LEETCODE_BEGIN_RESOLVING(434, NumberOfSegmentsInAString, Solution);

class Solution {
public:
  int countSegments(string s) {
    auto beg = s.begin();
    auto it  = s.begin();
    auto res = (int)0;
    while (it != s.end()) {
      if (*it == ' ') {
        res += it == beg ? 0 : 1;
        beg = it + 1;
      }
      ++it;
    }
    return res + (it != beg ? 1 : 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 300|
// * |s| consists of lowercase and uppercase English letters, digits, or one of
// the following characters |"!@#$%^&*()_+-=',.:"|.
// * The only space character in |s| is |' '|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "Hello, my name is John"
// Output: 5
//
// The five segments are ["Hello,", "my", "name", "is", "John"]

LEETCODE_SOLUTION_UNITTEST(434, NumberOfSegmentsInAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "Hello, my name is John";
  int    expect   = 5;
  int    actual   = solution->countSegments(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "Hello"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(434, NumberOfSegmentsInAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "Hello";
  int    expect   = 1;
  int    actual   = solution->countSegments(s);
  LCD_EXPECT_EQ(expect, actual);
}
