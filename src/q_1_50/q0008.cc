// Copyright 2023 Naon Lu
//
// This file describes the solution of
// String to Integer (atoi)
//
// https://leetcode.com/problems/string-to-integer-atoi/
//
// Question ID: 8
// Difficult  : Medium
// Solve Date : 2021/10/09 17:09

#include <iosfwd>
#include <limits>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |8. String to Integer (atoi)|:
//
// Implement the |myAtoi(string s)| function, which converts a string to a
// 32-bit signed integer (similar to C/C++'s |atoi| function). The algorithm for
// |myAtoi(string s)| is as follows:
//
//  1. Read in and ignore any leading whitespace.
//
//  2. Check if the next character (if not already at the end of the string) is
//  |'-'| or |'+'|. Read this character in if it is either. This determines if
//  the final result is negative or positive respectively. Assume the result is
//  positive if neither is present.
//
//  3. Read in next the characters until the next non-digit character or the end
//  of the input is reached. The rest of the string is ignored.
//
//  4. Convert these digits into an integer (i.e. |"123" -> 123|, |"0032" ->
//  32|). If no digits were read, then the integer is |0|. Change the sign as
//  necessary (from step 2).
//
//  5. If the integer is out of the 32-bit signed integer range |[-2³¹, 2³¹ -
//  1]|, then clamp the integer so that it remains in the range. Specifically,
//  integers less than |-2³¹| should be clamped to |-2³¹|, and integers greater
//  than |2³¹ - 1| should be clamped to |2³¹ - 1|.
//
//  6. Return the integer as the final result.
// Note:
//
//  • Only the space character |' '| is considered a whitespace character.
//
//  • Do not ignore any characters other than the leading whitespace or the rest
//  of the string after the digits.
//  
//

LEETCODE_BEGIN_RESOLVING(8, StringToIntegerAtoi, Solution);

class Solution {
public:
  int myAtoi(string s) {
    int         sign = 1;
    int         res  = 0;
    const char *c    = s.c_str();
    while (*c == ' ')
      ++c;
    if (*c == '-')
      sign = -1, ++c;
    else if (*c == '+')
      sign = 1, ++c;
    while (*c >= '0' && *c <= '9') {
      int num = *c - '0';
      if (numeric_limits<int>::max() / 10 < res ||
          (numeric_limits<int>::max() / 10 == res && num > 7))
        return sign == 1 ? numeric_limits<int>::max()
                         : numeric_limits<int>::min();
      res *= 10;
      res += num;
      ++c;
    }
    return res * sign;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 200|
// * |s| consists of English letters (lower-case and upper-case), digits (
// |0-9|), |' '|, |'+'|, |'-'|, and |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "42"
// Output: 42
//
// The underlined characters are what is read in, the caret is the current
// reader position. Step 1: "42" (no characters read because there is no leading
// whitespace)
//  ^
// Step 2: "42" (no characters read because there is neither a '-' nor '+')
//  ^
// Step 3: "42" ("42" is read in)
//  ^
// The parsed integer is 42.
// Since 42 is in the range [-2³¹, 2³¹ - 1], the final result is 42.

LEETCODE_SOLUTION_UNITTEST(8, StringToIntegerAtoi, example_1) {
  auto   solution = MakeSolution();
  string s        = "42";
  int    expect   = 42;
  int    actual   = solution->myAtoi(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = " -42"
// Output: -42
//
// Step 1: "   -42" (leading whitespace is read and ignored)
//  ^
// Step 2: " -42" ('-' is read, so the result should be negative)
//  ^
// Step 3: " -42" ("42" is read in)
//  ^
// The parsed integer is -42.
// Since -42 is in the range [-2³¹, 2³¹ - 1], the final result is -42.

LEETCODE_SOLUTION_UNITTEST(8, StringToIntegerAtoi, example_2) {
  auto   solution = MakeSolution();
  string s        = " -42";
  int    expect   = -42;
  int    actual   = solution->myAtoi(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "4193 with words"
// Output: 4193
//
// Step 1: "4193 with words" (no characters read because there is no leading
// whitespace)
//  ^
// Step 2: "4193 with words" (no characters read because there is neither a '-'
// nor '+')
//  ^
// Step 3: "4193 with words" ("4193" is read in; reading stops because the next
// character is a non-digit)
//  ^
// The parsed integer is 4193.
// Since 4193 is in the range [-2³¹, 2³¹ - 1], the final result is 4193.

LEETCODE_SOLUTION_UNITTEST(8, StringToIntegerAtoi, example_3) {
  auto   solution = MakeSolution();
  string s        = "4193 with words";
  int    expect   = 4193;
  int    actual   = solution->myAtoi(s);
  LCD_EXPECT_EQ(expect, actual);
}
