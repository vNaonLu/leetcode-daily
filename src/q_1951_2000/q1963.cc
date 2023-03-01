// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Swaps to Make the String Balanced
//
// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/
//
// Question ID: 1963
// Difficult  : Medium
// Solve Date : 2022/02/21 18:42

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1963. Minimum Number of Swaps to Make the String Balanced|:
//
// You are given a 0-indexed string |s| of even length |n|. The string consists
// of exactly |n / 2| opening brackets |'['| and |n / 2| closing brackets |']'|.
// A string is called balanced if and only if:
//
//  • It is the empty string, or
//
//  • It can be written as |AB|, where both |A| and |B| are balanced strings, or
//
//  • It can be written as |[C]|, where |C| is a balanced string.
// You may swap the brackets at any two indices any number of times.
// Return the minimum number of swaps to make |s| balanced.
//  
//

LEETCODE_BEGIN_RESOLVING(1963, MinimumNumberOfSwapsToMakeTheStringBalanced,
                         Solution);

class Solution {
public:
  int minSwaps(string s) {
    int res = 0, left = 0, right = s.size() - 1, cnt = 0;
    while (left < right) {
      cnt += s[left++] == '[' ? 1 : -1;
      if (cnt < 0) {
        while (s[right] == ']') {
          --right;
        }
        cnt = 1;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == s.length|
// * |2 <= n <= 10⁶|
// * |n| is even.
// * |s[i]| is either |'[' |or |']'|.
// * The number of opening brackets |'['| equals |n / 2|, and the number of
// closing brackets |']'| equals |n / 2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "][]["
// Output: 1
//
// You can make the string balanced by swapping index 0 with index 3.
// The resulting string is "[[]]".

LEETCODE_SOLUTION_UNITTEST(1963, MinimumNumberOfSwapsToMakeTheStringBalanced,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "][][";
  int    expect   = 1;
  int    actual   = solution->minSwaps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "]]][[["
// Output: 2
//
// You can do the following to make the string balanced:
// - Swap index 0 with index 4. s = "[]][][".
// - Swap index 1 with index 5. s = "[[][]]".
// The resulting string is "[[][]]".

LEETCODE_SOLUTION_UNITTEST(1963, MinimumNumberOfSwapsToMakeTheStringBalanced,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "]]][[[";
  int    expect   = 2;
  int    actual   = solution->minSwaps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "[]"
// Output: 0
//
// The string is already balanced.

LEETCODE_SOLUTION_UNITTEST(1963, MinimumNumberOfSwapsToMakeTheStringBalanced,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "[]";
  int    expect   = 0;
  int    actual   = solution->minSwaps(s);
  LCD_EXPECT_EQ(expect, actual);
}
