// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time to Type Word Using Special Typewriter
//
// https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/
//
// Question ID: 1974
// Difficult  : Easy
// Solve Date : 2023/09/18 20:05

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1974. Minimum Time to Type Word Using Special Typewriter|:
//
// There is a special typewriter with lowercase English letters |'a'| to |'z'|
// arranged in a circle with a pointer. A character can only be typed if the
// pointer is pointing to that character. The pointer is initially pointing to
// the character |'a'|.
// ![img](https://assets.leetcode.com/uploads/2021/07/31/chart.jpg)
// Each second, you may perform one of the following operations:
//
//  • Move the pointer one character counterclockwise or clockwise.
//
//  • Type the character the pointer is currently on.
// Given a string |word|, return the minimum number of seconds to type out the
// characters in |word|.
//
//

LEETCODE_BEGIN_RESOLVING(1974, MinimumTimeToTypeWordUsingSpecialTypewriter,
                         Solution);

class Solution {
public:
  int minTimeToType(string word) {
    int  res = word.size();
    char st  = 'a';
    for (auto c : word) {
      int clk  = 26 - abs(st - c);
      int aclk = abs(st - c);
      res += min(aclk, clk);
      st = c;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 100|
// * |word| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abc"
// Output: 5
// Explanation:
// The characters are printed as follows:
// - Type the character 'a' in 1 second since the pointer is initially on 'a'.
// - Move the pointer clockwise to 'b' in 1 second.
// - Type the character 'b' in 1 second.
// - Move the pointer clockwise to 'c' in 1 second.
// - Type the character 'c' in 1 second.
//

LEETCODE_SOLUTION_UNITTEST(1974, MinimumTimeToTypeWordUsingSpecialTypewriter,
                           example_1) {
  auto   solution = MakeSolution();
  string word     = "abc";
  int    expect   = 5;
  int    actual   = solution->minTimeToType(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "bza"
// Output: 7
// Explanation:
// The characters are printed as follows:
// - Move the pointer clockwise to 'b' in 1 second.
// - Type the character 'b' in 1 second.
// - Move the pointer counterclockwise to 'z' in 2 seconds.
// - Type the character 'z' in 1 second.
// - Move the pointer clockwise to 'a' in 1 second.
// - Type the character 'a' in 1 second.
//

LEETCODE_SOLUTION_UNITTEST(1974, MinimumTimeToTypeWordUsingSpecialTypewriter,
                           example_2) {
  auto   solution = MakeSolution();
  string word     = "bza";
  int    expect   = 7;
  int    actual   = solution->minTimeToType(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "zjpc"
// Output: 34
//
// The characters are printed as follows:
// - Move the pointer counterclockwise to 'z' in 1 second.
// - Type the character 'z' in 1 second.
// - Move the pointer clockwise to 'j' in 10 seconds.
// - Type the character 'j' in 1 second.
// - Move the pointer clockwise to 'p' in 6 seconds.
// - Type the character 'p' in 1 second.
// - Move the pointer counterclockwise to 'c' in 13 seconds.
// - Type the character 'c' in 1 second.

LEETCODE_SOLUTION_UNITTEST(1974, MinimumTimeToTypeWordUsingSpecialTypewriter,
                           example_3) {
  auto   solution = MakeSolution();
  string word     = "zjpc";
  int    expect   = 34;
  int    actual   = solution->minTimeToType(word);
  LCD_EXPECT_EQ(expect, actual);
}
