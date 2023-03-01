// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Percentage of Letter in String
//
// https://leetcode.com/problems/percentage-of-letter-in-string/
//
// Question ID: 2278
// Difficult  : Easy
// Solve Date : 2023/02/21 00:22

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2278. Percentage of Letter in String|:
//
// Given a string |s| and a character |letter|, return the percentage of
// characters in |s| that equal |letter| rounded down to the nearest whole
// percent.
//

LEETCODE_BEGIN_RESOLVING(2278, PercentageOfLetterInString, Solution);

class Solution {
public:
  int percentageLetter(string s, char letter) {
    unordered_map<char, int> freq;
    for (auto c : s) {
      ++freq[c];
    }
    return static_cast<int>(static_cast<double>(freq[letter]) * 100.0 /
                            s.size());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of lowercase English letters.
// * |letter| is a lowercase English letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "foobar", letter = "o"
// Output: 33
//
// The percentage of characters in s that equal the letter 'o' is 2 / 6 * 100% =
// 33% when rounded down, so we return 33.

LEETCODE_SOLUTION_UNITTEST(2278, PercentageOfLetterInString, example_1) {
  auto   solution = MakeSolution();
  string s        = "foobar";
  char   letter   = 'o';
  int    expect   = 33;
  int    actual   = solution->percentageLetter(s, letter);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "jjjj", letter = "k"
// Output: 0
//
// The percentage of characters in s that equal the letter 'k' is 0%, so we
// return 0.

LEETCODE_SOLUTION_UNITTEST(2278, PercentageOfLetterInString, example_2) {
  auto   solution = MakeSolution();
  string s        = "jjjj";
  char   letter   = 'k';
  int    expect   = 0;
  int    actual   = solution->percentageLetter(s, letter);
  LCD_EXPECT_EQ(expect, actual);
}
