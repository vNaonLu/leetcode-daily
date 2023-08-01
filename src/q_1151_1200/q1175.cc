// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Prime Arrangements
//
// https://leetcode.com/problems/prime-arrangements/
//
// Question ID: 1175
// Difficult  : Easy
// Solve Date : 2023/08/01 20:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1175. Prime Arrangements|:
//
// Return the number of permutations of 1 to |n| so that prime numbers are at
// prime indices (1-indexed.) (Recall that an integer is prime if and only if it
// is greater than 1, and cannot be written as a product of two positive
// integers both smaller than it.) Since the answer may be large, return the
// answer modulo |10^9 + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1175, PrimeArrangements, Solution);

class Solution {
public:
  int numPrimeArrangements(int n) {
    if (n == 1) {
      return 1;
    }

    vector<bool> prime(n + 1, true);
    prime[0] = false;
    prime[1] = false;

    int cnt = 0;
    for (int i = 0; i <= n; ++i) {
      if (!prime[i]) {
        continue;
      }

      ++cnt;
      for (int j = 2 * i; j <= n; j += i) {
        prime[j] = false;
      }
    }

    int64_t res = 1;
    int     tmp = n - cnt;
    while (cnt > 0) {
      res = (res * (cnt-- % kMod)) % kMod;
    }

    int64_t fact = 1;
    while (tmp > 0) {
      fact = (fact * (tmp-- % kMod)) % kMod;
    }

    return (res * fact) % kMod;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 12
//
// For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not
// because the prime number 5 is at index 1.

LEETCODE_SOLUTION_UNITTEST(1175, PrimeArrangements, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 12;
  int  actual   = solution->numPrimeArrangements(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 100
// Output: 682289015
//

LEETCODE_SOLUTION_UNITTEST(1175, PrimeArrangements, example_2) {
  auto solution = MakeSolution();
  int  n        = 100;
  int  expect   = 682289015;
  int  actual   = solution->numPrimeArrangements(n);
  LCD_EXPECT_EQ(expect, actual);
}
