// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Good Numbers
//
// https://leetcode.com/problems/count-good-numbers/
//
// Question ID: 1922
// Difficult  : Medium
// Solve Date : 2025/04/13 12:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1922. Count Good Numbers|:
//
// A digit string is good if the digits (0-indexed) at even indices are even and
// the digits at odd indices are prime ( |2|, |3|, |5|, or |7|).
//
//  • For example, |"2582"| is good because the digits ( |2| and |8|) at even
//  positions are even and the digits ( |5| and |2|) at odd positions are prime.
//  However, |"3245"| is not good because |3| is at an even index but is not
//  even.
// Given an integer |n|, return the total number of good digit strings of length
// |n|. Since the answer may be large, return it modulo |10⁹ + 7|. A digit
// string is a string consisting of digits |0| through |9| that may contain
// leading zeros.
//
//

LEETCODE_BEGIN_RESOLVING(1922, CountGoodNumbers, Solution);

class Solution {
public:
  int countGoodNumbers(long long n) {
    int64_t e = (n + 1) / 2;
    int64_t o = n / 2;
    return (power(5, e) * power(4, o)) % kMod;
  }

private:
  int64_t power(int64_t base, int64_t exp) {
    int64_t res = 1;
    while (exp > 0) {
      if (exp % 2 == 1) {
        res = (res * base) % kMod;
      }
      base = (base * base) % kMod;
      exp >>= 1;
    }
    return res;
  }

  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10¹⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1922, CountGoodNumbers, example_1) {
  auto      solution = MakeSolution();
  long long n        = 1;
  int       expect   = 5;
  int       actual   = solution->countGoodNumbers(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4
// Output: 400
//

LEETCODE_SOLUTION_UNITTEST(1922, CountGoodNumbers, example_2) {
  auto      solution = MakeSolution();
  long long n        = 4;
  int       expect   = 400;
  int       actual   = solution->countGoodNumbers(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 50
// Output: 564908303
//

LEETCODE_SOLUTION_UNITTEST(1922, CountGoodNumbers, example_3) {
  auto      solution = MakeSolution();
  long long n        = 50;
  int       expect   = 564908303;
  int       actual   = solution->countGoodNumbers(n);
  LCD_EXPECT_EQ(expect, actual);
}
