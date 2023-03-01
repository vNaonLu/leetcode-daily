// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Greatest Common Divisor of Strings
//
// https://leetcode.com/problems/greatest-common-divisor-of-strings/
//
// Question ID: 1071
// Difficult  : Easy
// Solve Date : 2022/11/07 18:48

#include <iosfwd>
#include <numeric>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1071. Greatest Common Divisor of Strings|:
//
// For two strings |s| and |t|, we say " |t| divides |s|" if and only if |s = t
// + ... + t| (i.e., |t| is concatenated with itself one or more times). Given
// two strings |str1| and |str2|, return the largest string |x| such that |x|
// divides both |str1| and |str2|.
//

LEETCODE_BEGIN_RESOLVING(1071, GreatestCommonDivisorOfStrings, Solution);

class Solution {
public:
  string gcdOfStrings(string str1, string str2) {
    return str1 + str2 == str2 + str1
               ? str1.substr(0, gcd(str1.size(), str2.size()))
               : "";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= str1.length, str2.length <= 1000|
// * |str1| and |str2| consist of English uppercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: str1 = "ABCABC", str2 = "ABC"
// Output: "ABC"
//

LEETCODE_SOLUTION_UNITTEST(1071, GreatestCommonDivisorOfStrings, example_1) {
  auto   solution = MakeSolution();
  string str1     = "ABCABC";
  string str2     = "ABC";
  string expect   = "ABC";
  string actual   = solution->gcdOfStrings(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: str1 = "ABABAB", str2 = "ABAB"
// Output: "AB"
//

LEETCODE_SOLUTION_UNITTEST(1071, GreatestCommonDivisorOfStrings, example_2) {
  auto   solution = MakeSolution();
  string str1     = "ABABAB";
  string str2     = "ABAB";
  string expect   = "AB";
  string actual   = solution->gcdOfStrings(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: str1 = "LEET", str2 = "CODE"
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(1071, GreatestCommonDivisorOfStrings, example_3) {
  auto   solution = MakeSolution();
  string str1     = "LEET";
  string str2     = "CODE";
  string expect   = "";
  string actual   = solution->gcdOfStrings(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}
