// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Prime Palindrome
//
// https://leetcode.com/problems/prime-palindrome/
//
// Question ID: 866
// Difficult  : Medium
// Solve Date : 2024/09/02 21:16

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |866. Prime Palindrome|:
//
// Given an integer n, return the smallest prime palindrome greater than or
// equal to |n|. An integer is prime if it has exactly two divisors: |1| and
// itself. Note that |1| is not a prime number.
//
//  • For example, |2|, |3|, |5|, |7|, |11|, and |13| are all primes.
// An integer is a palindrome if it reads the same from left to right as it does
// from right to left.
//
//  • For example, |101| and |12321| are palindromes.
// The test cases are generated so that the answer always exists and is in the
// range |[2, 2 * 10⁸]|.
//
//

LEETCODE_BEGIN_RESOLVING(866, PrimePalindrome, Solution);

class Solution {
public:
  int primePalindrome(int n) {
    if (8 <= n && n <= 11) {
      return 11;
    }

    for (int i = 1; i < 100000; ++i) {
      string s = to_string(i);
      string r(s.rbegin(), s.rend());
      int    y = stoi(s + r.substr(1));
      if (y >= n && isPrime(y)) {
        return y;
      }
    }
    return -1;
  }

private:
  bool isPrime(int x) {
    if (x < 2 || x % 2 == 0) {
      return x == 2;
    }

    for (int i = 3; i * i <= x; i += 2) {
      if (x % i == 0) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(866, PrimePalindrome, example_1) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  expect   = 7;
  int  actual   = solution->primePalindrome(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 8
// Output: 11
//

LEETCODE_SOLUTION_UNITTEST(866, PrimePalindrome, example_2) {
  auto solution = MakeSolution();
  int  n        = 8;
  int  expect   = 11;
  int  actual   = solution->primePalindrome(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 13
// Output: 101
//

LEETCODE_SOLUTION_UNITTEST(866, PrimePalindrome, example_3) {
  auto solution = MakeSolution();
  int  n        = 13;
  int  expect   = 101;
  int  actual   = solution->primePalindrome(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 9989900
// Output: 100030001
//

LEETCODE_SOLUTION_UNITTEST(866, PrimePalindrome, extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 9989900;
  int  expect   = 100030001;
  int  actual   = solution->primePalindrome(n);
  LCD_EXPECT_EQ(expect, actual);
}
