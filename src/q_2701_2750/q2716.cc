// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimize String Length
//
// https://leetcode.com/problems/minimize-string-length/
//
// Question ID: 2716
// Difficult  : Easy
// Solve Date : 2023/12/16 12:48

#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2716. Minimize String Length|:
//
// Given a 0-indexed string |s|, repeatedly perform the following operation any
// number of times:
//
//  • Choose an index |i| in the string, and let |c| be the character in
//  position |i|. Delete the closest occurrence of |c| to the left of |i| (if
//  any) and the closest occurrence of |c| to the right of |i| (if any).
// Your task is to minimize the length of |s| by performing the above operation
// any number of times. Return an integer denoting the length of the minimized
// string.
//
//

LEETCODE_BEGIN_RESOLVING(2716, MinimizeStringLength, Solution);

class Solution {
public:
  int minimizedStringLength(string s) {
    set<int> res(s.begin(), s.end());
    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| contains only lowercase English letters
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaabc"
// Output: 3
//
// In this example, s is "aaabc". We can start by selecting the character 'a' at
// index 1. We then remove the closest 'a' to the left of index 1, which is at
// index 0, and the closest 'a' to the right of index 1, which is at index 2.
// After this operation, the string becomes "abc". Any further operation we
// perform on the string will leave it unchanged. Therefore, the length of the
// minimized string is 3.

LEETCODE_SOLUTION_UNITTEST(2716, MinimizeStringLength, example_1) {
  auto   solution = MakeSolution();
  string s        = "aaabc";
  int    expect   = 3;
  int    actual   = solution->minimizedStringLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cbbd"
// Output: 3
//
// For this we can start with character 'b' at index 1. There is no occurrence
// of 'b' to the left of index 1, but there is one to the right at index 2, so
// we delete the 'b' at index 2. The string becomes "cbd" and further operations
// will leave it unchanged. Hence, the minimized length is 3.

LEETCODE_SOLUTION_UNITTEST(2716, MinimizeStringLength, example_2) {
  auto   solution = MakeSolution();
  string s        = "cbbd";
  int    expect   = 3;
  int    actual   = solution->minimizedStringLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "dddaaa"
// Output: 2
//
// For this, we can start with the character 'd' at index 1. The closest
// occurrence of a 'd' to its left is at index 0, and the closest occurrence of
// a 'd' to its right is at index 2. We delete both index 0 and 2, so the string
// becomes "daaa". In the new string, we can select the character 'a' at
// index 2. The closest occurrence of an 'a' to its left is at index 1, and the
// closest occurrence of an 'a' to its right is at index 3. We delete both of
// them, and the string becomes "da". We cannot minimize this further, so the
// minimized length is 2.

LEETCODE_SOLUTION_UNITTEST(2716, MinimizeStringLength, example_3) {
  auto   solution = MakeSolution();
  string s        = "dddaaa";
  int    expect   = 2;
  int    actual   = solution->minimizedStringLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "ipi"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2716, MinimizeStringLength, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "ipi";
  int    expect   = 2;
  int    actual   = solution->minimizedStringLength(s);
  LCD_EXPECT_EQ(expect, actual);
}
