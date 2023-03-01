// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Asterisks
//
// https://leetcode.com/problems/count-asterisks/
//
// Question ID: 2315
// Difficult  : Easy
// Solve Date : 2023/02/13 18:33

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2315. Count Asterisks|:
//
// You are given a string |s|, where every two consecutive vertical bars |'|'|
// are grouped into a pair. In other words, the 1ˢᵗ and 2ⁿᵈ |'|'| make a pair,
// the 3ʳᵈ and 4ᵗʰ |'|'| make a pair, and so forth. Return the number of |'*'|
// in |s|, excluding the |'*'| between each pair of |'|'|. Note that each |'|'|
// will belong to exactly one pair.
//

LEETCODE_BEGIN_RESOLVING(2315, CountAsterisks, Solution);

class Solution {
public:
  int countAsterisks(string s) {
    int  res      = 0;
    bool in_block = false;
    for (auto c : s) {
      if (c == '|') {
        in_block ^= true;
      }
      if (!in_block && c == '*') {
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
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase English letters, vertical bars |'|'|, and
// asterisks |'*'|.
// * |s| contains an even number of vertical bars |'|'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "l|*e*et|c**o|*de|"
// Output: 2
//
// The considered characters are underlined: "l|*e*et|c**o|*de|".
// The characters between the first and second '|' are excluded from the answer.
// Also, the characters between the third and fourth '|' are excluded from the
// answer. There are 2 asterisks considered. Therefore, we return 2.

LEETCODE_SOLUTION_UNITTEST(2315, CountAsterisks, example_1) {
  auto   solution = MakeSolution();
  string s        = "l|*e*et|c**o|*de|";
  int    expect   = 2;
  int    actual   = solution->countAsterisks(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "iamprogrammer"
// Output: 0
//
// In this example, there are no asterisks in s. Therefore, we return 0.

LEETCODE_SOLUTION_UNITTEST(2315, CountAsterisks, example_2) {
  auto   solution = MakeSolution();
  string s        = "iamprogrammer";
  int    expect   = 0;
  int    actual   = solution->countAsterisks(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "yo|uar|e**|b|e***au|tifu|l"
// Output: 5
//
// The considered characters are underlined: "yo|uar|e**|b|e***au|tifu|l". There
// are 5 asterisks considered. Therefore, we return 5.

LEETCODE_SOLUTION_UNITTEST(2315, CountAsterisks, example_3) {
  auto   solution = MakeSolution();
  string s        = "yo|uar|e**|b|e***au|tifu|l";
  int    expect   = 5;
  int    actual   = solution->countAsterisks(s);
  LCD_EXPECT_EQ(expect, actual);
}
