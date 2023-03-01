// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Gray Code
//
// https://leetcode.com/problems/gray-code/
//
// Question ID: 89
// Difficult  : Medium
// Solve Date : 2022/08/21 23:46

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |89. Gray Code|:
//
// An n-bit gray code sequence is a sequence of |2ⁿ| integers where:
//
//  • Every integer is in the inclusive range |[0, 2ⁿ - 1]|,
//
//  • The first integer is |0|,
//
//  • An integer appears no more than once in the sequence,
//
//  • The binary representation of every pair of adjacent integers differs by
//  exactly one bit, and
//
//  • The binary representation of the first and last integers differs by
//  exactly one bit.
// Given an integer |n|, return any valid n-bit gray code sequence.
//

LEETCODE_BEGIN_RESOLVING(89, GrayCode, Solution);

class Solution {
private:
  void solve(vector<int> &res, int n, int &x, int p) {
    if (n == 0) {
      res.emplace_back(x);
    } else {
      auto mask = 1 << p;
      solve(res, n - 1, x, p + 1);
      x ^= mask;
      solve(res, n - 1, x, p + 1);
    }
  }

public:
  vector<int> grayCode(int n) {
    auto res = vector<int>();
    auto x   = 0;

    solve(res, n, x, 0);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 16|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: [0,1,3,2]
//
// The binary representation of [0,1,3,2] is [00,01,11,10].
// - 00 and 01 differ by one bit
// - 01 and 11 differ by one bit
// - 11 and 10 differ by one bit
// - 10 and 00 differ by one bit
// [0,2,3,1] is also a valid gray code sequence, whose binary representation is
// [00,10,11,01].
// - 00 and 10 differ by one bit
// - 10 and 11 differ by one bit
// - 11 and 01 differ by one bit
// - 01 and 00 differ by one bit

LEETCODE_SOLUTION_UNITTEST(89, GrayCode, example_1) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> expect   = {0, 2, 3, 1};
  vector<int> actual   = solution->grayCode(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: [0,1]
//

LEETCODE_SOLUTION_UNITTEST(89, GrayCode, example_2) {
  auto        solution = MakeSolution();
  int         n        = 1;
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->grayCode(n);
  LCD_EXPECT_EQ(expect, actual);
}
