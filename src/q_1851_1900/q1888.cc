// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Number of Flips to Make the Binary String Alternating
//
// https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/
//
// Question ID: 1888
// Difficult  : Medium
// Solve Date : 2026/03/07 22:24

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1888. Minimum Number of Flips to Make the Binary String
// Alternating|:
//
// You are given a binary string |s|. You are allowed to perform two types of
// operations on the string in any sequence:
//
//  • Type-1: Remove the character at the start of the string |s| and append it
//  to the end of the string.
//
//  • Type-2: Pick any character in |s| and flip its value, i.e., if its value
//  is |'0'| it becomes |'1'| and vice-versa.
// Return the minimum number of type-2 operations you need to perform such that
// |s| becomes alternating. The string is called alternating if no two adjacent
// characters are equal.
//
//  • For example, the strings |"010"| and |"1010"| are alternating, while the
//  string |"0100"| is not.
//
//

LEETCODE_BEGIN_RESOLVING(1888,
                         MinimumNumberOfFlipsToMakeTheBinaryStringAlternating,
                         Solution);

class Solution {
public:
  int minFlips(string s) {
    int         n  = s.size();
    vector<int> op = {0, 0};
    for (int i = 0; i < n; ++i) {
      op[(s[i] ^ i) & 1]++;
    }

    int res = min(op[0], op[1]);
    for (int i = 0; i < n - 1; ++i) {
      op[(s[i] ^ i) & 1]--;
      op[(s[i] ^ (n + i)) & 1]++;
      res = min({res, op[0], op[1]});
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "111000"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1888,
                           MinimumNumberOfFlipsToMakeTheBinaryStringAlternating,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "111000";
  int    expect   = 2;
  int    actual   = solution->minFlips(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "010"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1888,
                           MinimumNumberOfFlipsToMakeTheBinaryStringAlternating,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "010";
  int    expect   = 0;
  int    actual   = solution->minFlips(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1110"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1888,
                           MinimumNumberOfFlipsToMakeTheBinaryStringAlternating,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "1110";
  int    expect   = 1;
  int    actual   = solution->minFlips(s);
  LCD_EXPECT_EQ(expect, actual);
}
