// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decode Ways
//
// https://leetcode.com/problems/decode-ways/
//
// Question ID: 91
// Difficult  : Medium
// Solve Date : 2021/10/03 11:33

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |91. Decode Ways|:
//
// A message containing letters from |A-Z| can be encoded into numbers using the
// following mapping: 'A' -> "1" 'B' -> "2"
// ...
// 'Z' -> "26"
// To decode an encoded message, all the digits must be grouped then mapped back
// into letters using the reverse of the mapping above (there may be multiple
// ways). For example, |"11106"| can be mapped into:
//
//  • |"AAJF"| with the grouping |(1 1 10 6)|
//
//  • |"KJF"| with the grouping |(11 10 6)|
// Note that the grouping |(1 11 06)| is invalid because |"06"| cannot be mapped
// into |'F'| since |"6"| is different from |"06"|. Given a string |s|
// containing only digits, return the number of ways to decode it. The test
// cases are generated so that the answer fits in a 32-bit integer.  
//

LEETCODE_BEGIN_RESOLVING(91, DecodeWays, Solution);

class Solution {
public:
  int numDecodings(string s) {
    vector<int> dp(s.size() + 1, 0);
    dp[0] = 1;
    dp[1] = s[0] == '0' ? 0 : 1;
    for (int i = 2; i <= s.size(); ++i) {
      dp[i] = s[i - 1] == '0' ? 0 : dp[i - 1];
      if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))
        dp[i] += dp[i - 2];
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| contains only digits and may contain leading zero(s).
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "12"
// Output: 2
//
// "12" could be decoded as "AB" (1 2) or "L" (12).

LEETCODE_SOLUTION_UNITTEST(91, DecodeWays, example_1) {
  auto   solution = MakeSolution();
  string s        = "12";
  int    expect   = 2;
  int    actual   = solution->numDecodings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "226"
// Output: 3
//
// "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

LEETCODE_SOLUTION_UNITTEST(91, DecodeWays, example_2) {
  auto   solution = MakeSolution();
  string s        = "226";
  int    expect   = 3;
  int    actual   = solution->numDecodings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "06"
// Output: 0
//
// "06" cannot be mapped to "F" because of the leading zero ("6" is different
// from "06").

LEETCODE_SOLUTION_UNITTEST(91, DecodeWays, example_3) {
  auto   solution = MakeSolution();
  string s        = "06";
  int    expect   = 0;
  int    actual   = solution->numDecodings(s);
  LCD_EXPECT_EQ(expect, actual);
}
