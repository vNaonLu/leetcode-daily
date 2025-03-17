// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Closest Prime Numbers in Range
//
// https://leetcode.com/problems/closest-prime-numbers-in-range/
//
// Question ID: 2523
// Difficult  : Medium
// Solve Date : 2025/03/07 19:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2523. Closest Prime Numbers in Range|:
//
// Given two positive integers |left| and |right|, find the two integers |num1|
// and |num2| such that:
//
//  • |left <= num1 < num2 <= right |.
//
//  • Both |num1| and |num2| are prime numbers.
//
//  • |num2 - num1| is the minimum amongst all other pairs satisfying the above
//  conditions.
// Return the positive integer array |ans = [num1, num2]|. If there are multiple
// pairs satisfying these conditions, return the one with the smallest |num1|
// value. If no such numbers exist, return |[-1, -1]|.
//
//

LEETCODE_BEGIN_RESOLVING(2523, ClosestPrimeNumbersInRange, Solution);

class Solution {
public:
  vector<int> closestPrimes(int left, int right) {
    auto is_prime = [](int n) {
      if (n <= 1)
        return false;
      if (n <= 3)
        return true;
      if (n % 2 == 0 || n % 3 == 0)
        return false;
      for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
          return false;
      }
      return true;
    };

    vector<int> primes;
    for (int num = max(2, left); num <= right; ++num) {
      if (is_prime(num)) {
        primes.push_back(num);
      }
    }

    if (primes.size() < 2) {
      return {-1, -1};
    }

    int         min_gap = numeric_limits<int>::max();
    vector<int> result  = {-1, -1};

    for (int i = 1; i < primes.size(); ++i) {
      int gap = primes[i] - primes[i - 1];
      if (gap < min_gap) {
        min_gap = gap;
        result  = {primes[i - 1], primes[i]};
      }
    }

    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= left <= right <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: left = 10, right = 19
// Output: [11,13]
//

LEETCODE_SOLUTION_UNITTEST(2523, ClosestPrimeNumbersInRange, example_1) {
  auto        solution = MakeSolution();
  int         left     = 10;
  int         right    = 19;
  vector<int> expect   = {11, 13};
  vector<int> actual   = solution->closestPrimes(left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: left = 4, right = 6
// Output: [-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(2523, ClosestPrimeNumbersInRange, example_2) {
  auto        solution = MakeSolution();
  int         left     = 4;
  int         right    = 6;
  vector<int> expect   = {-1, -1};
  vector<int> actual   = solution->closestPrimes(left, right);
  LCD_EXPECT_EQ(expect, actual);
}
