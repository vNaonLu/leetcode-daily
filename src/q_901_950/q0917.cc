// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Only Letters
//
// https://leetcode.com/problems/reverse-only-letters/
//
// Question ID: 917
// Difficult  : Easy
// Solve Date : 2021/09/14 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |917. Reverse Only Letters|:
//
// Given a string |s|, reverse the string according to the following rules:
//
//  • All the characters that are not English letters remain in the same
//  position.
//
//  • All the English letters (lowercase or uppercase) should be reversed.
// Return |s| after reversing it.
//  
//

LEETCODE_BEGIN_RESOLVING(917, ReverseOnlyLetters, Solution);

class Solution {
private:
  bool isValidLetter(const char &c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

public:
  string reverseOnlyLetters(string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
      if (!isValidLetter(s[l])) {
        ++l;
        continue;
      }
      if (!isValidLetter(s[r])) {
        --r;
        continue;
      }
      char t = s[l];
      s[l++] = s[r];
      s[r--] = t;
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of characters with ASCII values in the range |[33, 122]|.
// * |s| does not contain |'\"'| or |'\\'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ab-cd"
// Output: "dc-ba"
//

LEETCODE_SOLUTION_UNITTEST(917, ReverseOnlyLetters, example_1) {
  auto   solution = MakeSolution();
  string s        = "ab-cd";
  string expect   = "dc-ba";
  string actual   = solution->reverseOnlyLetters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a-bC-dEf-ghIj"
// Output: "j-Ih-gfE-dCba"
//

LEETCODE_SOLUTION_UNITTEST(917, ReverseOnlyLetters, example_2) {
  auto   solution = MakeSolution();
  string s        = "a-bC-dEf-ghIj";
  string expect   = "j-Ih-gfE-dCba";
  string actual   = solution->reverseOnlyLetters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "Test1ng-Leet=code-Q!"
// Output: "Qedo1ct-eeLg=ntse-T!"
//

LEETCODE_SOLUTION_UNITTEST(917, ReverseOnlyLetters, example_3) {
  auto   solution = MakeSolution();
  string s        = "Test1ng-Leet=code-Q!";
  string expect   = "Qedo1ct-eeLg=ntse-T!";
  string actual   = solution->reverseOnlyLetters(s);
  LCD_EXPECT_EQ(expect, actual);
}
