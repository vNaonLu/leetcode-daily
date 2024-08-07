// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Integer to English Words
//
// https://leetcode.com/problems/integer-to-english-words/
//
// Question ID: 273
// Difficult  : Hard
// Solve Date : 2024/08/07 21:27

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |273. Integer to English Words|:
//
// Convert a non-negative integer |num| to its English words representation.
//
//

LEETCODE_BEGIN_RESOLVING(273, IntegerToEnglishWords, Solution);

class Solution {
public:
  string numberToWords(int num) {
    if (num == 0)
      return "Zero";

    unordered_map<int, string> units = {
        { 1,       "One"},
        { 2,       "Two"},
        { 3,     "Three"},
        { 4,      "Four"},
        { 5,      "Five"},
        { 6,       "Six"},
        { 7,     "Seven"},
        { 8,     "Eight"},
        { 9,      "Nine"},
        {10,       "Ten"},
        {11,    "Eleven"},
        {12,    "Twelve"},
        {13,  "Thirteen"},
        {14,  "Fourteen"},
        {15,   "Fifteen"},
        {16,   "Sixteen"},
        {17, "Seventeen"},
        {18,  "Eighteen"},
        {19,  "Nineteen"}
    };

    unordered_map<int, string> tens = {
        {2,  "Twenty"},
        {3,  "Thirty"},
        {4,   "Forty"},
        {5,   "Fifty"},
        {6,   "Sixty"},
        {7, "Seventy"},
        {8,  "Eighty"},
        {9,  "Ninety"}
    };

    auto getHundred = [&](int num) {
      string str = "";
      if (num >= 100) {
        int n = num / 100;
        str += " " + units[n] + " Hundred";
        num %= 100;
      }

      if (num >= 20) {
        int n = num / 10;
        str += " " + tens[n];
        num %= 10;
      }

      if (num > 0) {
        str += " " + units[num];
      }

      return str;
    };

    string answer = "";
    if (num >= 1e9) {
      int n = num / 1e9;
      answer += getHundred(n) + " Billion";
      num %= int(1e9);
    }

    if (num >= 1e6) {
      int n = num / 1e6;
      answer += getHundred(n) + " Million";
      num %= int(1e6);
    }

    if (num >= 1e3) {
      int n = num / 1e3;
      answer += getHundred(n) + " Thousand";
      num %= int(1e3);
    }

    answer += getHundred(num);

    return answer.substr(1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= num <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 123
// Output: "One Hundred Twenty Three"
//

LEETCODE_SOLUTION_UNITTEST(273, IntegerToEnglishWords, example_1) {
  auto   solution = MakeSolution();
  int    num      = 123;
  string expect   = "One Hundred Twenty Three";
  string actual   = solution->numberToWords(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 12345
// Output: "Twelve Thousand Three Hundred Forty Five"
//

LEETCODE_SOLUTION_UNITTEST(273, IntegerToEnglishWords, example_2) {
  auto   solution = MakeSolution();
  int    num      = 12345;
  string expect   = "Twelve Thousand Three Hundred Forty Five";
  string actual   = solution->numberToWords(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 1234567
// Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
// Seven"
//

LEETCODE_SOLUTION_UNITTEST(273, IntegerToEnglishWords, example_3) {
  auto   solution = MakeSolution();
  int    num      = 1234567;
  string expect =
      "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven";
  string actual = solution->numberToWords(num);
  LCD_EXPECT_EQ(expect, actual);
}
