// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Numbers With Same Consecutive Differences
//
// https://leetcode.com/problems/numbers-with-same-consecutive-differences/
//
// Question ID: 967
// Difficult  : Medium
// Solve Date : 2022/09/03 13:20

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |967. Numbers With Same Consecutive Differences|:
//
// Given two integers n and k, return an array of all the integers of length |n|
// where the difference between every two consecutive digits is |k|. You may
// return the answer in any order. Note that the integers should not have
// leading zeros. Integers as |02| and |043| are not allowed.
//

LEETCODE_BEGIN_RESOLVING(967, NumbersWithSameConsecutiveDifferences, Solution);

class Solution {
public:
  vector<int> numsSameConsecDiff(int n, int k) {
    if (n == 1) {
      return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    }
    auto queue = vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int lvl = 1; lvl < n; ++lvl) {
      auto next_q = vector<int>();
      for (auto x : queue) {
        auto digit      = x % 10;
        auto next_digit = vector<int>();
        next_digit.emplace_back(digit + k);
        if (k != 0) {
          next_digit.emplace_back(digit - k);
        }
        for (auto y : next_digit) {
          if (y >= 0 && y < 10) {
            next_q.emplace_back(x * 10 + y);
          }
        }
      }
      queue = move(next_q);
    }
    return queue;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 9|
// * |0 <= k <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 7
// Output: [181,292,707,818,929]
//
// Note that 070 is not a valid number, because it has leading zeroes.

LEETCODE_SOLUTION_UNITTEST(967, NumbersWithSameConsecutiveDifferences,
                           example_1) {
  auto        solution = MakeSolution();
  int         n        = 3;
  int         k        = 7;
  vector<int> expect   = {181, 292, 707, 818, 929};
  vector<int> actual   = solution->numsSameConsecDiff(n, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, k = 1
// Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
//

LEETCODE_SOLUTION_UNITTEST(967, NumbersWithSameConsecutiveDifferences,
                           example_2) {
  auto        solution = MakeSolution();
  int         n        = 2;
  int         k        = 1;
  vector<int> expect   = {10, 12, 21, 23, 32, 34, 43, 45, 54,
                          56, 65, 67, 76, 78, 87, 89, 98};
  vector<int> actual   = solution->numsSameConsecDiff(n, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}
