// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Sum of Array Product of Magical Sequences
//
// https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/
//
// Question ID: 3539
// Difficult  : Hard
// Solve Date : 2025/10/12 10:44

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3539. Find Sum of Array Product of Magical Sequences|:
//
// You are given two integers, |m| and |k|, and an integer array |nums|.
// A sequence of integers |seq| is called magical if:
//
//  • |seq| has a size of |m|.
//
//  • |0 <= seq[i] < nums.length|
//
//  • The binary representation of |2^{seq[0]} + 2^{seq[1]} + ... + 2^{seq[m -
//  1]}| has |k| set bits.
// The array product of this sequence is defined as |prod(seq) = (nums[seq[0]] *
// nums[seq[1]] * ... * nums[seq[m - 1]])|. Return the sum of the array products
// for all valid magical sequences. Since the answer may be large, return it
// modulo |10⁹ + 7|. A set bit refers to a bit in the binary representation of a
// number that has a value of 1.
//
//

LEETCODE_BEGIN_RESOLVING(3539, FindSumOfArrayProductOfMagicalSequences,
                         Solution);

class Solution {
public:
  int magicalSum(int m, int k, vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
      power[i][0] = 1;
      for (int j = 1; j < m + 1; j++) {
        power[i][j] = ((long long)a[i] * (power[i][j - 1])) % mod;
      }
    }
    for (int i = 0; i <= 30; i++) {
      ncr[i][0] = 1;
      for (int j = 1; j <= i; j++) {
        ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
      }
    }
    for (int i = 0; i < m + 1; i++)
      bits[i] = __builtin_popcount(i);
    auto reset = [&]() -> void {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
          for (int kk = 0; kk <= m; kk++) {
            for (int mm = 0; mm <= k; mm++) {
              dp[i][j][kk][mm] = -1;
            }
          }
        }
      }
    };
    reset();
    auto func = [&](int ind, int carry, int sz, int cnt, auto &&func) -> int {
      if (ind == n) {
        if (sz != m || cnt + bits[carry] != k)
          return 0;
        return 1;
      }
      if (cnt > k)
        return 0;
      if (dp[ind][carry][sz][cnt] != -1)
        return dp[ind][carry][sz][cnt];
      int ans = 0;
      for (int i = 0; i <= m - sz; i++) {
        int mul      = power[ind][i];
        int newcarry = carry + i;
        int x        = newcarry & 1;
        mul          = ((long long)mul *
               func(ind + 1, newcarry / 2, sz + i, cnt + x, func)) %
              mod;
        mul = ((long long)mul * ncr[m - sz][i]) % mod;
        ans = (ans + mul) % mod;
      }
      return dp[ind][carry][sz][cnt] = ans;
    };
    return func(0, 0, 0, 0, func);
  }

private:
  const int mod = 1e9 + 7;
  int       bits[31];
  int       power[51][31];
  int       ncr[31][31];
  int       dp[51][31][31][31];
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= m <= 30|
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
// Output: 991600007
//

LEETCODE_SOLUTION_UNITTEST(3539, FindSumOfArrayProductOfMagicalSequences,
                           example_1) {
  auto        solution = MakeSolution();
  int         m        = 5;
  int         k        = 5;
  vector<int> nums     = {1, 10, 100, 10000, 1000000};
  int         expect   = 991600007;
  int         actual   = solution->magicalSum(m, k, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 2, k = 2, nums = [5,4,3,2,1]
// Output: 170
//

LEETCODE_SOLUTION_UNITTEST(3539, FindSumOfArrayProductOfMagicalSequences,
                           example_2) {
  auto        solution = MakeSolution();
  int         m        = 2;
  int         k        = 2;
  vector<int> nums     = {5, 4, 3, 2, 1};
  int         expect   = 170;
  int         actual   = solution->magicalSum(m, k, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: m = 1, k = 1, nums = [28]
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(3539, FindSumOfArrayProductOfMagicalSequences,
                           example_3) {
  auto        solution = MakeSolution();
  int         m        = 1;
  int         k        = 1;
  vector<int> nums     = {28};
  int         expect   = 28;
  int         actual   = solution->magicalSum(m, k, nums);
  LCD_EXPECT_EQ(expect, actual);
}
