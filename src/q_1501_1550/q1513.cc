// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of Substrings With Only 1s
//
// https://leetcode.com/problems/number-of-substrings-with-only-1s/
//
// Question ID: 1513
// Difficult  : Medium
// Solve Date : 2025/11/16 10:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1513. Number of Substrings With Only 1s|:
//
// Given a binary string |s|, return the number of substrings with all
// characters |1|'s. Since the answer may be too large, return it modulo |10⁹ +
// 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1513, NumberOfSubstringsWithOnly1s, Solution);

class Solution {
public:
  int numSub(string s) {
    int64_t res = 0;
    int64_t cnt = 0;
    for (auto c : s) {
      if (c == '0') {
        cnt = 0;
      } else {
        res += ++cnt;
      }
    }
    return res % (int64_t)(1e9 + 7);
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
//  Input: s = "0110111"
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(1513, NumberOfSubstringsWithOnly1s, example_1) {
  auto   solution = MakeSolution();
  string s        = "0110111";
  int    expect   = 9;
  int    actual   = solution->numSub(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "101"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1513, NumberOfSubstringsWithOnly1s, example_2) {
  auto   solution = MakeSolution();
  string s        = "101";
  int    expect   = 2;
  int    actual   = solution->numSub(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "111111"
// Output: 21
//

LEETCODE_SOLUTION_UNITTEST(1513, NumberOfSubstringsWithOnly1s, example_3) {
  auto   solution = MakeSolution();
  string s        = "111111";
  int    expect   = 21;
  int    actual   = solution->numSub(s);
  LCD_EXPECT_EQ(expect, actual);
}
