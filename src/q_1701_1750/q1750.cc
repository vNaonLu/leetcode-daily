// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Length of String After Deleting Similar Ends
//
// https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/
//
// Question ID: 1750
// Difficult  : Medium
// Solve Date : 2024/03/05 23:53

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1750. Minimum Length of String After Deleting Similar Ends|:
//
// Given a string |s| consisting only of characters |'a'|, |'b'|, and |'c'|. You
// are asked to apply the following algorithm on the string any number of times:
//
//  1. Pick a non-empty prefix from the string |s| where all the characters in
//  the prefix are equal.
//
//  2. Pick a non-empty suffix from the string |s| where all the characters in
//  this suffix are equal.
//
//  3. The prefix and the suffix should not intersect at any index.
//
//  4. The characters from the prefix and suffix must be the same.
//
//  5. Delete both the prefix and the suffix.
// Return the minimum length of |s| after performing the above operation any
// number of times (possibly zero times).
//
//

LEETCODE_BEGIN_RESOLVING(1750, MinimumLengthOfStringAfterDeletingSimilarEnds,
                         Solution);

class Solution {
public:
  int minimumLength(string s) {
    int beg = 0;
    int end = s.size() - 1;
    while (beg < end) {
      if (s[beg] == s[end]) {
        while (s[beg] == s[beg + 1] && beg < end) {
          ++beg;
        }
        while (s[end] == s[end - 1] && beg < end) {
          --end;
        }
        ++beg;
        --end;
      } else {
        break;
      }
    }
    int res = end - beg + 1;
    return res < 0 ? 0 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| only consists of characters |'a'|, |'b'|, and |'c'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ca"
// Output: 2
//
// You can't remove any characters, so the string stays as is.

LEETCODE_SOLUTION_UNITTEST(1750, MinimumLengthOfStringAfterDeletingSimilarEnds,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "ca";
  int    expect   = 2;
  int    actual   = solution->minimumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cabaabac"
// Output: 0
//
// An optimal sequence of operations is:
// - Take prefix = "c" and suffix = "c" and remove them, s = "abaaba".
// - Take prefix = "a" and suffix = "a" and remove them, s = "baab".
// - Take prefix = "b" and suffix = "b" and remove them, s = "aa".
// - Take prefix = "a" and suffix = "a" and remove them, s = "".

LEETCODE_SOLUTION_UNITTEST(1750, MinimumLengthOfStringAfterDeletingSimilarEnds,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "cabaabac";
  int    expect   = 0;
  int    actual   = solution->minimumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aabccabba"
// Output: 3
//
// An optimal sequence of operations is:
// - Take prefix = "aa" and suffix = "a" and remove them, s = "bccabb".
// - Take prefix = "b" and suffix = "bb" and remove them, s = "cca".

LEETCODE_SOLUTION_UNITTEST(1750, MinimumLengthOfStringAfterDeletingSimilarEnds,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "aabccabba";
  int    expect   = 3;
  int    actual   = solution->minimumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}
