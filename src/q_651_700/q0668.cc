// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Smallest Number in Multiplication Table
//
// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
//
// Question ID: 668
// Difficult  : Hard
// Solve Date : 2021/11/16 18:13

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |668. Kth Smallest Number in Multiplication Table|:
//
// Nearly everyone has used the [Multiplication Table]. The multiplication table
// of size |m x n| is an integer matrix |mat| where |mat[i][j] == i * j|
// (1-indexed). Given three integers |m|, |n|, and |k|, return the |kᵗʰ|
// smallest element in the |m x n| multiplication table.  
//

LEETCODE_BEGIN_RESOLVING(668, KthSmallestNumberInMultiplicationTable, Solution);

class Solution {
private:
  bool helper(int x, int m, int n, int k) {
    int count = 0;
    for (int i = 1; i <= m; ++i) {
      count += min(n, x / i);
    }
    return count >= k;
  }

public:
  int findKthNumber(int m, int n, int k) {
    int L = 1, R = m * n;
    while (R > L) {
      int M = L + (R - L) / 2;
      if (helper(M, m, n, k))
        R = M;
      else
        L = M + 1;
    }
    return L;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 3 * 10⁴|
// * |1 <= k <= m * n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 3, n = 3, k = 5
// Output: 3
//
// The 5ᵗʰ smallest number is 3.

LEETCODE_SOLUTION_UNITTEST(668, KthSmallestNumberInMultiplicationTable,
                           example_1) {
  auto solution = MakeSolution();
  int  m        = 3;
  int  n        = 3;
  int  k        = 5;
  int  expect   = 3;
  int  actual   = solution->findKthNumber(m, n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 2, n = 3, k = 6
// Output: 6
//
// The 6ᵗʰ smallest number is 6.

LEETCODE_SOLUTION_UNITTEST(668, KthSmallestNumberInMultiplicationTable,
                           example_2) {
  auto solution = MakeSolution();
  int  m        = 2;
  int  n        = 3;
  int  k        = 6;
  int  expect   = 6;
  int  actual   = solution->findKthNumber(m, n, k);
  LCD_EXPECT_EQ(expect, actual);
}
