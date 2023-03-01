// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Palindrome Number
//
// https://leetcode.com/problems/palindrome-number/
//
// Question ID: 9
// Difficult  : Easy
// Solve Date : 2021/10/10 13:56

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |9. Palindrome Number|:
//
// Given an integer |x|, return |true| if |x| is a palindrome, and |false|
// otherwise.  
//

LEETCODE_BEGIN_RESOLVING(9, PalindromeNumber, Solution);

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;
    double tmp     = x;
    double reverse = 0;
    while (x > 0) {
      reverse = reverse * 10 + x % 10;
      x /= 10;
    }
    return reverse == tmp;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= x <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 121
// Output: true
//
// 121 reads as 121 from left to right and from right to left.

LEETCODE_SOLUTION_UNITTEST(9, PalindromeNumber, example_1) {
  auto solution = MakeSolution();
  int  x        = 121;
  bool expect   = true;
  bool actual   = solution->isPalindrome(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = -121
// Output: false
//
// From left to right, it reads -121. From right to left, it becomes 121-.
// Therefore it is not a palindrome.

LEETCODE_SOLUTION_UNITTEST(9, PalindromeNumber, example_2) {
  auto solution = MakeSolution();
  int  x        = -121;
  bool expect   = false;
  bool actual   = solution->isPalindrome(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: x = 10
// Output: false
//
// Reads 01 from right to left. Therefore it is not a palindrome.

LEETCODE_SOLUTION_UNITTEST(9, PalindromeNumber, example_3) {
  auto solution = MakeSolution();
  int  x        = 10;
  bool expect   = false;
  bool actual   = solution->isPalindrome(x);
  LCD_EXPECT_EQ(expect, actual);
}
