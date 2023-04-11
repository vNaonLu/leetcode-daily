// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Word Equals Summation of Two Words
//
// https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/
//
// Question ID: 1880
// Difficult  : Easy
// Solve Date : 2023/04/12 01:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1880. Check if Word Equals Summation of Two Words|:
//
// The letter value of a letter is its position in the alphabet starting from 0
// (i.e. |'a' -> 0|, |'b' -> 1|, |'c' -> 2|, etc.). The numerical value of some
// string of lowercase English letters |s| is the concatenation of the letter
// values of each letter in |s|, which is then converted into an integer.
//
//  • For example, if |s = "acb"|, we concatenate each letter's letter value,
//  resulting in |"021"|. After converting it, we get |21|.
// You are given three strings |firstWord|, |secondWord|, and |targetWord|, each
// consisting of lowercase English letters |'a'| through |'j'| inclusive. Return
// |true| if the summation of the numerical values of |firstWord| and
// |secondWord| equals the numerical value of |targetWord|, or |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1880, CheckIfWordEqualsSummationOfTwoWords, Solution);

class Solution {
private:
  template <typename It>
  int64_t toNumber(It beg, It end) {
    int64_t res = 0;
    while (beg != end) {
      res *= 10;
      res += *beg++ - 'a';
    }
    return res;
  }

public:
  bool isSumEqual(string firstWord, string secondWord, string targetWord) {
    auto num1   = toNumber(firstWord.begin(), firstWord.end());
    auto num2   = toNumber(secondWord.begin(), secondWord.end());
    auto target = toNumber(targetWord.begin(), targetWord.end());
    return num1 + num2 == target;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= firstWord.length, | |secondWord.length, | |targetWord.length <= 8|
// * |firstWord|, |secondWord|, and |targetWord| consist of lowercase English
// letters from |'a'| to |'j'| inclusive.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: firstWord = "acb", secondWord = "cba", targetWord = "cdb"
// Output: true
//
// The numerical value of firstWord is "acb" -> "021" -> 21.
// The numerical value of secondWord is "cba" -> "210" -> 210.
// The numerical value of targetWord is "cdb" -> "231" -> 231.
// We return true because 21 + 210 == 231.

LEETCODE_SOLUTION_UNITTEST(1880, CheckIfWordEqualsSummationOfTwoWords,
                           example_1) {
  auto   solution   = MakeSolution();
  string firstWord  = "acb";
  string secondWord = "cba";
  string targetWord = "cdb";
  bool   expect     = true;
  bool   actual     = solution->isSumEqual(firstWord, secondWord, targetWord);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: firstWord = "aaa", secondWord = "a", targetWord = "aab"
// Output: false
//
// The numerical value of firstWord is "aaa" -> "000" -> 0.
// The numerical value of secondWord is "a" -> "0" -> 0.
// The numerical value of targetWord is "aab" -> "001" -> 1.
// We return false because 0 + 0 != 1.

LEETCODE_SOLUTION_UNITTEST(1880, CheckIfWordEqualsSummationOfTwoWords,
                           example_2) {
  auto   solution   = MakeSolution();
  string firstWord  = "aaa";
  string secondWord = "a";
  string targetWord = "aab";
  bool   expect     = false;
  bool   actual     = solution->isSumEqual(firstWord, secondWord, targetWord);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: firstWord = "aaa", secondWord = "a", targetWord = "aaaa"
// Output: true
//
// The numerical value of firstWord is "aaa" -> "000" -> 0.
// The numerical value of secondWord is "a" -> "0" -> 0.
// The numerical value of targetWord is "aaaa" -> "0000" -> 0.
// We return true because 0 + 0 == 0.

LEETCODE_SOLUTION_UNITTEST(1880, CheckIfWordEqualsSummationOfTwoWords,
                           example_3) {
  auto   solution   = MakeSolution();
  string firstWord  = "aaa";
  string secondWord = "a";
  string targetWord = "aaaa";
  bool   expect     = true;
  bool   actual     = solution->isSumEqual(firstWord, secondWord, targetWord);
  LCD_EXPECT_EQ(expect, actual);
}
