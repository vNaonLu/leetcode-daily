// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Digits of String After Convert
//
// https://leetcode.com/problems/sum-of-digits-of-string-after-convert/
//
// Question ID: 1945
// Difficult  : Easy
// Solve Date : 2023/05/18 12:21

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1945. Sum of Digits of String After Convert|:
//
// You are given a string |s| consisting of lowercase English letters, and an
// integer |k|. First, convert |s| into an integer by replacing each letter with
// its position in the alphabet (i.e., replace |'a'| with |1|, |'b'| with |2|,
// ..., |'z'| with |26|). Then, transform the integer by replacing it with the
// sum of its digits. Repeat the transform operation |k| times in total. For
// example, if |s = "zbax"| and |k = 2|, then the resulting integer would be |8|
// by the following operations:
//
//  • Convert: |"zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124|
//
//  • Transform #1: |262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17|
//
//  • Transform #2: |17 ➝ 1 + 7 ➝ 8|
// Return the resulting integer after performing the operations described above.
//
//

LEETCODE_BEGIN_RESOLVING(1945, SumOfDigitsOfStringAfterConvert, Solution);

class Solution {
public:
  int getLucky(string s, int k) {
    string res;
    for (auto c : s) {
      auto x = c - 'a' + 1;
      res += to_string(x);
    }

    while (k--) {
      auto x = 0;
      for (auto c : res) {
        x += c - '0';
      }
      res = to_string(x);
    }
    return stoi(res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |1 <= k <= 10|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "iiii", k = 1
// Output: 36
//
// The operations are as follows:
// - Convert: "iiii" ➝ "(9)(9)(9)(9)" ➝ "9999" ➝ 9999
// - Transform #1: 9999 ➝ 9 + 9 + 9 + 9 ➝ 36
// Thus the resulting integer is 36.

LEETCODE_SOLUTION_UNITTEST(1945, SumOfDigitsOfStringAfterConvert, example_1) {
  auto   solution = MakeSolution();
  string s        = "iiii";
  int    k        = 1;
  int    expect   = 36;
  int    actual   = solution->getLucky(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcode", k = 2
// Output: 6
//
// The operations are as follows:
// - Convert: "leetcode" ➝ "(12)(5)(5)(20)(3)(15)(4)(5)" ➝ "12552031545" ➝
// 12552031545
// - Transform #1: 12552031545 ➝ 1 + 2 + 5 + 5 + 2 + 0 + 3 + 1 + 5 + 4 + 5 ➝ 33
// - Transform #2: 33 ➝ 3 + 3 ➝ 6
// Thus the resulting integer is 6.

LEETCODE_SOLUTION_UNITTEST(1945, SumOfDigitsOfStringAfterConvert, example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    k        = 2;
  int    expect   = 6;
  int    actual   = solution->getLucky(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "zbax", k = 2
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1945, SumOfDigitsOfStringAfterConvert, example_3) {
  auto   solution = MakeSolution();
  string s        = "zbax";
  int    k        = 2;
  int    expect   = 8;
  int    actual   = solution->getLucky(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
