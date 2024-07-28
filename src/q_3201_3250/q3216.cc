// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Lexicographically Smallest String After a Swap
//
// https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/
//
// Question ID: 3216
// Difficult  : Easy
// Solve Date : 2024/07/22 20:24

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3216. Lexicographically Smallest String After a Swap|:
//
// Given a string |s| containing only digits, return the lexicographically
// smallest string that can be obtained after swapping adjacent digits in |s|
// with the same parity at most once. Digits have the same parity if both are
// odd or both are even. For example, 5 and 9, as well as 2 and 4, have the same
// parity, while 6 and 9 do not.
//
//

LEETCODE_BEGIN_RESOLVING(3216, LexicographicallySmallestStringAfterASwap,
                         Solution);

class Solution {
public:
  string getSmallestString(string s) {
    for (int i = 0; i < s.size() - 1; ++i) {
      if ((s[i] % 2 == s[i + 1] % 2) && s[i] > s[i + 1]) {
        swap(s[i], s[i + 1]);
        break;
      }
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s| consists only of digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "45320"
// Output: "43520"
//

LEETCODE_SOLUTION_UNITTEST(3216, LexicographicallySmallestStringAfterASwap,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "45320";
  string expect   = "43520";
  string actual   = solution->getSmallestString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "001"
// Output: "001"
//

LEETCODE_SOLUTION_UNITTEST(3216, LexicographicallySmallestStringAfterASwap,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "001";
  string expect   = "001";
  string actual   = solution->getSmallestString(s);
  LCD_EXPECT_EQ(expect, actual);
}
