// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Arrays with K Matching Adjacent Elements
//
// https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/
//
// Question ID: 3405
// Difficult  : Hard
// Solve Date : 2025/06/17 20:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3405. Count the Number of Arrays with K Matching Adjacent
// Elements|:
//
// You are given three integers |n|, |m|, |k|. A good array |arr| of size |n| is
// defined as follows:
//
//  • Each element in |arr| is in the inclusive range |[1, m]|.
//
//  • Exactly |k| indices |i| (where |1 <= i < n|) satisfy the condition |arr[i
//  - 1] == arr[i]|.
// Return the number of good arrays that can be formed.
// Since the answer may be very large, return it modulo |10^{9 }+ 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3405,
                         CountTheNumberOfArraysWithKMatchingAdjacentElements,
                         Solution);

class Solution {
public:
  int countGoodArrays(int n, int m, int k) {
    int formula = (m * 1ll * bin_expo(m - 1, n - (k + 1))) % MOD;

    int updated_formula = (formula * 1ll * nCr(n - 1, k)) % MOD;

    return updated_formula;
  }

private:
  long long modInverse(long long a, long long mod) {
    long long res   = 1;
    long long power = mod - 2;

    while (power) {
      if (power & 1)
        res = res * a % mod;
      a = a * a % mod;
      power >>= 1;
    }

    return res;
  }

  int nCr(int n, int r) {
    if (r > n)
      return 0;
    if (r == 0 || r == n)
      return 1;

    long long res = 1;

    for (int i = 1; i <= r; i++) {
      res = res * (n - r + i) % MOD;
      res = res * modInverse(i, MOD) % MOD;
    }

    return (int)res;
  }

  long long bin_expo(long long a, long long b) {
    long long result = 1;
    while (b) {
      if (b & 1)
        result = (result * a) % MOD;
      a = (a * a) % MOD;
      b >>= 1;
    }
    return result;
  }
  const int MOD = 1e9 + 7;
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |1 <= m <= 10⁵|
// * |0 <= k <= n - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, m = 2, k = 1
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3405,
                           CountTheNumberOfArraysWithKMatchingAdjacentElements,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  m        = 2;
  int  k        = 1;
  int  expect   = 4;
  int  actual   = solution->countGoodArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, m = 2, k = 2
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3405,
                           CountTheNumberOfArraysWithKMatchingAdjacentElements,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  m        = 2;
  int  k        = 2;
  int  expect   = 6;
  int  actual   = solution->countGoodArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, m = 2, k = 0
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3405,
                           CountTheNumberOfArraysWithKMatchingAdjacentElements,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  m        = 2;
  int  k        = 0;
  int  expect   = 2;
  int  actual   = solution->countGoodArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}
