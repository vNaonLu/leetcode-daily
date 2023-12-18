// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum String Length After Removing Substrings
//
// https://leetcode.com/problems/minimum-string-length-after-removing-substrings/
//
// Question ID: 2696
// Difficult  : Easy
// Solve Date : 2023/12/12 20:02

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2696. Minimum String Length After Removing Substrings|:
//
// You are given a string |s| consisting only of uppercase English letters.
// You can apply some operations to this string where, in one operation, you can
// remove any occurrence of one of the substrings |"AB"| or |"CD"| from |s|.
// Return the minimum possible length of the resulting string that you can
// obtain. Note that the string concatenates after removing the substring and
// could produce new |"AB"| or |"CD"| substrings.
//
//

LEETCODE_BEGIN_RESOLVING(2696, MinimumStringLengthAfterRemovingSubstrings,
                         Solution);

class Solution {
public:
  int minLength(string s) {
    stack<char> stk;
    for (auto c : s) {
      if (stk.empty() ||
          ((c != 'B' || stk.top() != 'A') && (c != 'D' || stk.top() != 'C'))) {
        stk.emplace(c);
      } else {
        stk.pop();
      }
    }
    return stk.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists only of uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ABFCACDB"
// Output: 2
//
// We can do the following operations:
// - Remove the substring "ABFCACDB", so s = "FCACDB".
// - Remove the substring "FCACDB", so s = "FCAB".
// - Remove the substring "FCAB", so s = "FC".
// So the resulting length of the string is 2.
// It can be shown that it is the minimum length that we can obtain.

LEETCODE_SOLUTION_UNITTEST(2696, MinimumStringLengthAfterRemovingSubstrings,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "ABFCACDB";
  int    expect   = 2;
  int    actual   = solution->minLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ACBBD"
// Output: 5
//
// We cannot do any operations on the string so the length remains the same.

LEETCODE_SOLUTION_UNITTEST(2696, MinimumStringLengthAfterRemovingSubstrings,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "ACBBD";
  int    expect   = 5;
  int    actual   = solution->minLength(s);
  LCD_EXPECT_EQ(expect, actual);
}
