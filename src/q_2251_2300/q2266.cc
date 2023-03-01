// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Number of Texts
//
// https://leetcode.com/problems/count-number-of-texts/
//
// Question ID: 2266
// Difficult  : Medium
// Solve Date : 2022/06/01 18:04

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2266. Count Number of Texts|:
//
// Alice is texting Bob using her phone. The mapping of digits to letters is
// shown in the figure below.
// ![img](https://assets.leetcode.com/uploads/2022/03/15/1200px-telephone-keypad2svg.png)
// In order to add a letter, Alice has to press the key of the corresponding
// digit |i| times, where |i| is the position of the letter in the key.
//
//  • For example, to add the letter |'s'|, Alice has to press |'7'| four times.
//  Similarly, to add the letter |'k'|, Alice has to press |'5'| twice.
//
//  • Note that the digits |'0'| and |'1'| do not map to any letters, so Alice
//  does not use them.
// However, due to an error in transmission, Bob did not receive Alice's text
// message but received a string of pressed keys instead.
//
//  • For example, when Alice sent the message |"bob"|, Bob received the string
//  |"2266622"|.
// Given a string |pressedKeys| representing the string received by Bob, return
// the total number of possible text messages Alice could have sent. Since the
// answer may be very large, return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(2266, CountNumberOfTexts, Solution);

class Solution {
private:
  constexpr static int kMod = 1e9 + 7;

  int helper(int i, string_view s, vector<int> &dp) {
    if (i == 0) {
      return 1;
    }

    if (dp[i] != -1) {
      return dp[i];
    }

    int res = helper(i - 1, s, dp) % kMod;

    if (i - 2 >= 0 && s[i - 1] == s[i - 2]) {
      res += helper(i - 2, s, dp);
      res %= kMod;

      if (i - 3 >= 0 && s[i - 2] == s[i - 3]) {
        res += helper(i - 3, s, dp);
        res %= kMod;

        if (i - 4 >= 0 && s[i - 3] == s[i - 4] &&
            (s[i - 3] == '7' || s[i - 3] == '9')) {
          res += helper(i - 4, s, dp);
          res %= kMod;
        }
      }
    }

    return dp[i] = res;
  }

public:
  int countTexts(string pressedKeys) {
    vector<int> dp(pressedKeys.size() + 1, -1);

    return helper(pressedKeys.size(), pressedKeys, dp);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= pressedKeys.length <= 10⁵|
// * |pressedKeys| only consists of digits from |'2'| - |'9'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pressedKeys = "22233"
// Output: 8
//
// The possible text messages Alice could have sent are:
// "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae", and "ce".
// Since there are 8 possible messages, we return 8.

LEETCODE_SOLUTION_UNITTEST(2266, CountNumberOfTexts, example_1) {
  auto   solution    = MakeSolution();
  string pressedKeys = "22233";
  int    expect      = 8;
  int    actual      = solution->countTexts(pressedKeys);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pressedKeys = "222222222222222222222222222222222222"
// Output: 82876089
//
// There are 2082876103 possible text messages Alice could have sent.
// Since we need to return the answer modulo 10⁹ + 7, we return 2082876103 %
// (10⁹ + 7) = 82876089.

LEETCODE_SOLUTION_UNITTEST(2266, CountNumberOfTexts, example_2) {
  auto   solution    = MakeSolution();
  string pressedKeys = "222222222222222222222222222222222222";
  int    expect      = 82876089;
  int    actual      = solution->countTexts(pressedKeys);
  LCD_EXPECT_EQ(expect, actual);
}
