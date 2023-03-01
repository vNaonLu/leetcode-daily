// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Index of the First Occurrence in a String
//
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
//
// Question ID: 28
// Difficult  : Medium
// Solve Date : 2021/11/20 14:36

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |28. Find the Index of the First Occurrence in a String|:
//
// Given two strings |needle| and |haystack|, return the index of the first
// occurrence of |needle| in |haystack|, or |-1| if |needle| is not part of
// |haystack|.  
//

LEETCODE_BEGIN_RESOLVING(28, FindTheIndexOfTheFirstOccurrenceInAString,
                         Solution);

class Solution {
public:
  int strStr(string haystack, string needle) {
    if (needle.empty())
      return 0;
    for (int i = 0; i <= (int)haystack.size() - (int)needle.size(); ++i) {
      if (haystack.substr(i, needle.size()) == needle)
        return i;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= haystack.length, needle.length <= 10⁴|
// * |haystack| and |needle| consist of only lowercase English characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: haystack = "sadbutsad", needle = "sad"
// Output: 0
//
// "sad" occurs at index 0 and 6.
// The first occurrence is at index 0, so we return 0.

LEETCODE_SOLUTION_UNITTEST(28, FindTheIndexOfTheFirstOccurrenceInAString,
                           example_1) {
  auto   solution = MakeSolution();
  string haystack = "sadbutsad";
  string needle   = "sad";
  int    expect   = 0;
  int    actual   = solution->strStr(haystack, needle);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: haystack = "leetcode", needle = "leeto"
// Output: -1
//
// "leeto" did not occur in "leetcode", so we return -1.

LEETCODE_SOLUTION_UNITTEST(28, FindTheIndexOfTheFirstOccurrenceInAString,
                           example_2) {
  auto   solution = MakeSolution();
  string haystack = "leetcode";
  string needle   = "leeto";
  int    expect   = -1;
  int    actual   = solution->strStr(haystack, needle);
  LCD_EXPECT_EQ(expect, actual);
}
