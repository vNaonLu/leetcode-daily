// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Integer to Roman
//
// https://leetcode.com/problems/integer-to-roman/
//
// Question ID: 12
// Difficult  : Medium
// Solve Date : 2021/10/11 17:31

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |12. Integer to Roman|:
//
// Roman numerals are represented by seven different symbols:  |I|, |V|, |X|,
// |L|, |C|, |D| and |M|. Symbol       Value I             1 V             5 X
// 10 L             50 C             100 D             500 M             1000
// For example,  |2| is written as |II| in Roman numeral, just two one's added
// together. |12| is written as  |XII|, which is simply |X + II|. The number
// |27| is written as |XXVII|, which is |XX + V + II|. Roman numerals are
// usually written largest to smallest from left to right. However, the numeral
// for four is not |IIII|. Instead, the number four is written as |IV|. Because
// the one is before the five we subtract it making four. The same principle
// applies to the number nine, which is written as |IX|. There are six instances
// where subtraction is used:
//
//  • |I| can be placed before |V| (5) and |X| (10) to make 4 and 9. 
//
//  • |X| can be placed before |L| (50) and |C| (100) to make 40 and 90. 
//
//  • |C| can be placed before |D| (500) and |M| (1000) to make 400 and 900.
// Given an integer, convert it to a roman numeral.
//  
//

LEETCODE_BEGIN_RESOLVING(12, IntegerToRoman, Solution);

class Solution {
private:
  vector<char> decimal = {'I', 'X', 'C', 'M'};
  vector<char> quintet = {'V', 'L', 'D'};

public:
  string intToRoman(int num) {
    string res = "";
    int    idx = 0;
    while (num > 0) {
      int last = num % 10;
      num /= 10;
      switch (last) {
      case 1:
      case 2:
      case 3:
        while (last--)
          res += decimal[idx];
        break;
      case 4:
        res += quintet[idx];
        res += decimal[idx];
        break;
      case 5:
      case 6:
      case 7:
      case 8:
        while (last-- > 5)
          res += decimal[idx];
        res += quintet[idx];
        break;
      case 9:
        res += decimal[idx + 1];
        res += decimal[idx];
        break;
      }
      ++idx;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 3999|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 3
// Output: "III"
//
// 3 is represented as 3 ones.

LEETCODE_SOLUTION_UNITTEST(12, IntegerToRoman, example_1) {
  auto   solution = MakeSolution();
  int    num      = 3;
  string expect   = "III";
  string actual   = solution->intToRoman(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 58
// Output: "LVIII"
//
// L = 50, V = 5, III = 3.

LEETCODE_SOLUTION_UNITTEST(12, IntegerToRoman, example_2) {
  auto   solution = MakeSolution();
  int    num      = 58;
  string expect   = "LVIII";
  string actual   = solution->intToRoman(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 1994
// Output: "MCMXCIV"
//
// M = 1000, CM = 900, XC = 90 and IV = 4.

LEETCODE_SOLUTION_UNITTEST(12, IntegerToRoman, example_3) {
  auto   solution = MakeSolution();
  int    num      = 1994;
  string expect   = "MCMXCIV";
  string actual   = solution->intToRoman(num);
  LCD_EXPECT_EQ(expect, actual);
}
