// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bulls and Cows
//
// https://leetcode.com/problems/bulls-and-cows/
//
// Question ID: 299
// Difficult  : Medium
// Solve Date : 2022/09/05 17:32

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |299. Bulls and Cows|:
//
// You are playing the [Bulls and Cows] game with your friend.
// You write down a secret number and ask your friend to guess what the number
// is. When your friend makes a guess, you provide a hint with the following
// info:
//
//  • The number of "bulls", which are digits in the guess that are in the
//  correct position.
//
//  • The number of "cows", which are digits in the guess that are in your
//  secret number but are located in the wrong position. Specifically, the
//  non-bull digits in the guess that could be rearranged such that they become
//  bulls.
// Given the secret number |secret| and your friend's guess |guess|, return the
// hint for your friend's guess. The hint should be formatted as |"xAyB"|, where
// |x| is the number of bulls and |y| is the number of cows. Note that both
// |secret| and |guess| may contain duplicate digits.
//

LEETCODE_BEGIN_RESOLVING(299, BullsAndCows, Solution);

class Solution {
public:
  string getHint(string secret, string guess) {
    auto a    = (int)0;
    auto b    = (int)0;
    auto memo = unordered_map<char, int>();
    for (auto c : secret) {
      ++memo[c];
    }
    for (auto c : guess) {
      auto find = memo.find(c);
      if (find != memo.end() && find->second-- > 0) {
        ++b;
      }
    }
    auto s_beg = secret.begin();
    auto g_beg = guess.begin();
    while (s_beg != secret.end()) {
      if (*s_beg++ == *g_beg++) {
        ++a;
        --b;
      }
    }
    return to_string(a) + "A" + to_string(b) + "B";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= secret.length, guess.length <= 1000|
// * |secret.length == guess.length|
// * |secret| and |guess| consist of digits only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: secret = "1807", guess = "7810"
// Output: "1A3B"
//
// Bulls are connected with a '|' and cows are underlined:
// "1807"
//  |
// "7810"

LEETCODE_SOLUTION_UNITTEST(299, BullsAndCows, example_1) {
  auto   solution = MakeSolution();
  string secret   = "1807";
  string guess    = "7810";
  string expect   = "1A3B";
  string actual   = solution->getHint(secret, guess);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: secret = "1123", guess = "0111"
// Output: "1A1B"
//
// Bulls are connected with a '|' and cows are underlined:
// "1123" "1123"
//  | or |
// "0111" "0111"
// Note that only one of the two unmatched 1s is counted as a cow since the
// non-bull digits can only be rearranged to allow one 1 to be a bull.

LEETCODE_SOLUTION_UNITTEST(299, BullsAndCows, example_2) {
  auto   solution = MakeSolution();
  string secret   = "1123";
  string guess    = "0111";
  string expect   = "1A1B";
  string actual   = solution->getHint(secret, guess);
  LCD_EXPECT_EQ(expect, actual);
}
