// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Ideal Arrays
//
// https://leetcode.com/problems/count-the-number-of-ideal-arrays/
//
// Question ID: 2338
// Difficult  : Hard
// Solve Date : 2025/04/22 21:16

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2338. Count the Number of Ideal Arrays|:
//
// You are given two integers |n| and |maxValue|, which are used to describe an
// ideal array. A 0-indexed integer array |arr| of length |n| is considered
// ideal if the following conditions hold:
//
//  • Every |arr[i]| is a value from |1| to |maxValue|, for |0 <= i < n|.
//
//  • Every |arr[i]| is divisible by |arr[i - 1]|, for |0 < i < n|.
// Return the number of distinct ideal arrays of length |n|. Since the answer
// may be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(2338, CountTheNumberOfIdealArrays, Solution);

class Solution {
public:
  int idealArrays(int n, int maxValue) {
    if (comb[1][1] == 0) { // One-time precomputation
      // Precompute binomial coefficients: comb[s][r] = C(s, r)
      for (int s = 1; s <= 10000; ++s)
        for (int r = 0; r < 14; ++r)
          comb[s][r] = r == 0 ? 1 : (comb[s - 1][r - 1] + comb[s - 1][r]) % mod;

      // Modified Sieve: cnt[i][bars] = # of sequences ending in i with (bars+1)
      // terms
      for (int div = 1; div <= 10000; ++div) {
        ++cnt[div][0];
        for (int i = 2 * div; i <= 10000; i += div)
          for (int bars = 0; cnt[div][bars]; ++bars)
            cnt[i][bars + 1] += cnt[div][bars];
      }
    }

    int res = 0;
    // Count valid arrays using precomputed tables
    for (int i = 1; i <= maxValue; ++i)
      for (int bars = 0; bars < min(14, n) && cnt[i][bars]; ++bars)
        res = (1LL * cnt[i][bars] * comb[n - 1][bars] + res) % mod;

    return res;
  }

private:
  int comb[10001][14] = {1};
  int cnt[10001][14]  = {};
  int mod             = 1000000007;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁴|
// * |1 <= maxValue <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, maxValue = 5
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(2338, CountTheNumberOfIdealArrays, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  maxValue = 5;
  int  expect   = 10;
  int  actual   = solution->idealArrays(n, maxValue);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, maxValue = 3
// Output: 11
//

LEETCODE_SOLUTION_UNITTEST(2338, CountTheNumberOfIdealArrays, example_2) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  maxValue = 3;
  int  expect   = 11;
  int  actual   = solution->idealArrays(n, maxValue);
  LCD_EXPECT_EQ(expect, actual);
}
