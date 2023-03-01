// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Roman to Integer
//
// https://leetcode.com/problems/roman-to-integer/
//
// Question ID: 13
// Difficult  : Easy
// Solve Date : 2021/11/07 15:18

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |13. Roman to Integer|:
//
// Roman numerals are represented by seven different symbols:  |I|, |V|, |X|,
// |L|, |C|, |D| and |M|. Symbol       Value I             1 V             5 X
// 10 L             50 C             100 D             500 M             1000
// For example,  |2| is written as |II| in Roman numeral, just two ones added
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
// Given a roman numeral, convert it to an integer.
//  
//

LEETCODE_BEGIN_RESOLVING(13, RomanToInteger, Solution);

class Solution {
private:
  unordered_map<char, int> symbol = {
      {'I',    1},
      {'V',    5},
      {'X',   10},
      {'L',   50},
      {'C',  100},
      {'D',  500},
      {'M', 1000}
  };

public:
  int romanToInt(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      res += symbol[s[i]];
      if (i > 0 && symbol[s[i]] > symbol[s[i - 1]]) {
        res -= 2 * symbol[s[i - 1]];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 15|
// * |s| contains only the characters |('I', 'V', 'X', 'L', 'C', 'D', 'M')|.
// * It is guaranteed that |s| is a valid roman numeral in the range |[1,
// 3999]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "III"
// Output: 3
//
// III = 3.

LEETCODE_SOLUTION_UNITTEST(13, RomanToInteger, example_1) {
  auto   solution = MakeSolution();
  string s        = "III";
  int    expect   = 3;
  int    actual   = solution->romanToInt(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "LVIII"
// Output: 58
//
// L = 50, V= 5, III = 3.

LEETCODE_SOLUTION_UNITTEST(13, RomanToInteger, example_2) {
  auto   solution = MakeSolution();
  string s        = "LVIII";
  int    expect   = 58;
  int    actual   = solution->romanToInt(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "MCMXCIV"
// Output: 1994
//
// M = 1000, CM = 900, XC = 90 and IV = 4.

LEETCODE_SOLUTION_UNITTEST(13, RomanToInteger, example_3) {
  auto   solution = MakeSolution();
  string s        = "MCMXCIV";
  int    expect   = 1994;
  int    actual   = solution->romanToInt(s);
  LCD_EXPECT_EQ(expect, actual);
}
