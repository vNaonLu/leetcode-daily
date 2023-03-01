// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ugly Number III
//
// https://leetcode.com/problems/ugly-number-iii/
//
// Question ID: 1201
// Difficult  : Medium
// Solve Date : 2022/08/02 18:21

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1201. Ugly Number III|:
//
// An ugly number is a positive integer that is divisible by |a|, |b|, or |c|.
// Given four integers |n|, |a|, |b|, and |c|, return the |nᵗʰ| ugly number.
//

LEETCODE_BEGIN_RESOLVING(1201, UglyNumberIII, Solution);

class Solution {
private:
  template <typename type>
  type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
  }

public:
  int nthUglyNumber(int n, int a, int b, int c) {
    int64_t lo = 0, hi = min<int64_t>({a, b, c}) * n;
    int64_t mid = 0, res = -1;
    int64_t lcm_abc = ((int64_t)a * b * c) * gcd(c, gcd(a, b)) /
                      (gcd(a, b) * gcd(b, c) * gcd(a, c));
    int64_t lcm_ab = ((int64_t)a * b) / gcd(a, b);
    int64_t lcm_bc = ((int64_t)b * c) / gcd(b, c);
    int64_t lcm_ac = ((int64_t)a * c) / gcd(a, c);

    while (lo <= hi) {
      mid = lo + (hi - lo) / 2;

      auto curr = mid / a + mid / b + mid / c - mid / lcm_ab - mid / lcm_bc -
                  mid / lcm_ac + mid / lcm_abc;

      if (curr < n) {
        lo = mid + 1;
      } else {
        res = mid;
        hi  = mid - 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n, a, b, c <= 10⁹|
// * |1 <= a * b * c <= 10¹⁸|
// * It is guaranteed that the result will be in range |[1, 2 * 10⁹]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, a = 2, b = 3, c = 5
// Output: 4
//
// The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3ʳᵈ is 4.

LEETCODE_SOLUTION_UNITTEST(1201, UglyNumberIII, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  a        = 2;
  int  b        = 3;
  int  c        = 5;
  int  expect   = 4;
  int  actual   = solution->nthUglyNumber(n, a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, a = 2, b = 3, c = 4
// Output: 6
//
// The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4ᵗʰ is 6.

LEETCODE_SOLUTION_UNITTEST(1201, UglyNumberIII, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  a        = 2;
  int  b        = 3;
  int  c        = 4;
  int  expect   = 6;
  int  actual   = solution->nthUglyNumber(n, a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, a = 2, b = 11, c = 13
// Output: 10
//
// The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5ᵗʰ is 10.

LEETCODE_SOLUTION_UNITTEST(1201, UglyNumberIII, example_3) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  a        = 2;
  int  b        = 11;
  int  c        = 13;
  int  expect   = 10;
  int  actual   = solution->nthUglyNumber(n, a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}
