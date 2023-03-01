// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Nth Magical Number
//
// https://leetcode.com/problems/nth-magical-number/
//
// Question ID: 878
// Difficult  : Hard
// Solve Date : 2021/12/11 14:28

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |878. Nth Magical Number|:
//
// A positive integer is magical if it is divisible by either |a| or |b|.
// Given the three integers |n|, |a|, and |b|, return the |nᵗʰ| magical number.
// Since the answer may be very large, return it modulo |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(878, NthMagicalNumber, Solution);

class Solution {
private:
  constexpr static uint32_t _module = 1e9 + 7;
  int                       gcd(int a, int b) {
    if (a == 0)
      return b;
    return gcd(b % a, a);
  }

public:
  int nthMagicalNumber(int n, int a, int b) {
    int  L  = a / gcd(a, b) * b;
    long lo = 0, hi = (long)n * min(a, b);
    while (lo < hi) {
      long m = lo + (hi - lo) / 2;
      if (m / a + m / b - m / L < n)
        lo = m + 1;
      else
        hi = m;
    }
    return static_cast<int>(lo % _module);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
// * |2 <= a, b <= 4 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, a = 2, b = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(878, NthMagicalNumber, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  a        = 2;
  int  b        = 3;
  int  expect   = 2;
  int  actual   = solution->nthMagicalNumber(n, a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, a = 2, b = 3
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(878, NthMagicalNumber, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  a        = 2;
  int  b        = 3;
  int  expect   = 6;
  int  actual   = solution->nthMagicalNumber(n, a, b);
  LCD_EXPECT_EQ(expect, actual);
}
