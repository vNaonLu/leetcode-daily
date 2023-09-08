// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Changes To Make Alternating Binary String
//
// https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/
//
// Question ID: 1758
// Difficult  : Easy
// Solve Date : 2023/09/08 16:48

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1758. Minimum Changes To Make Alternating Binary String|:
//
// You are given a string |s| consisting only of the characters |'0'| and |'1'|.
// In one operation, you can change any |'0'| to |'1'| or vice versa. The string
// is called alternating if no two adjacent characters are equal. For example,
// the string |"010"| is alternating, while the string |"0100"| is not. Return
// the minimum number of operations needed to make |s| alternating.
//
//

LEETCODE_BEGIN_RESOLVING(1758, MinimumChangesToMakeAlternatingBinaryString,
                         Solution);

class Solution {
public:
  int minOperations(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      res += (s[i] - '0') != (i & 1);
    }
    return min<int>(res, s.size() - res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "0100"
// Output: 1
//
// If you change the last character to '1', s will be "0101", which is
// alternating.

LEETCODE_SOLUTION_UNITTEST(1758, MinimumChangesToMakeAlternatingBinaryString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "0100";
  int    expect   = 1;
  int    actual   = solution->minOperations(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "10"
// Output: 0
//
// s is already alternating.

LEETCODE_SOLUTION_UNITTEST(1758, MinimumChangesToMakeAlternatingBinaryString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "10";
  int    expect   = 0;
  int    actual   = solution->minOperations(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1111"
// Output: 2
//
// You need two operations to reach "0101" or "1010".

LEETCODE_SOLUTION_UNITTEST(1758, MinimumChangesToMakeAlternatingBinaryString,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "1111";
  int    expect   = 2;
  int    actual   = solution->minOperations(s);
  LCD_EXPECT_EQ(expect, actual);
}
