// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Operations to Move Ones to the End
//
// https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/
//
// Question ID: 3228
// Difficult  : Medium
// Solve Date : 2025/11/13 19:16

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3228. Maximum Number of Operations to Move Ones to the End|:
//
// You are given a binary string |s|.
// You can perform the following operation on the string any number of times:
//
//  • Choose any index |i| from the string where |i + 1 < s.length| such that
//  |s[i] == '1'| and |s[i + 1] == '0'|.
//
//  • Move the character |s[i]| to the right until it reaches the end of the
//  string or another |'1'|. For example, for |s = "010010"|, if we choose |i =
//  1|, the resulting string will be |s = "000110"|.
// Return the maximum number of operations that you can perform.
//
//

LEETCODE_BEGIN_RESOLVING(3228, MaximumNumberOfOperationsToMoveOnesToTheEnd,
                         Solution);

class Solution {
public:
  int maxOperations(string s) {
    int res = 0;
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '1') {
        ++cnt;
      } else if ((i > 0) && s[i - 1] == '1') {
        res += cnt;
      }
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
//  Input: s = "1001101"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3228, MaximumNumberOfOperationsToMoveOnesToTheEnd,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1001101";
  int    expect   = 4;
  int    actual   = solution->maxOperations(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "00111"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3228, MaximumNumberOfOperationsToMoveOnesToTheEnd,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "00111";
  int    expect   = 0;
  int    actual   = solution->maxOperations(s);
  LCD_EXPECT_EQ(expect, actual);
}
