// Copyright 2024 Naon Lu
//
// This file describes the solution of
// K-th Smallest in Lexicographical Order
//
// https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/
//
// Question ID: 440
// Difficult  : Hard
// Solve Date : 2024/09/22 14:51

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |440. K-th Smallest in Lexicographical Order|:
//
// Given two integers |n| and |k|, return the |kᵗʰ| lexicographically smallest
// integer in the range |[1, n]|.
//
//

LEETCODE_BEGIN_RESOLVING(440, KThSmallestInLexicographicalOrder, Solution);

class Solution {
public:
  int findKthNumber(int n, int k) {
    int res = 1;
    for (int i = 1; i < k;) {
      auto req = helper(res, res + 1, n);
      if (req + i <= k) {
        i += req;
        ++res;
      } else {
        ++i;
        res *= 10;
      }
    }
    return res;
  }

private:
  int64_t helper(int64_t a, int64_t b, int n) {
    int64_t gap = 0;
    while (a <= n) {
      gap += min<int64_t>(n + 1, b) - a;
      a *= 10;
      b *= 10;
    }
    return gap;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 13, k = 2
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(440, KThSmallestInLexicographicalOrder, example_1) {
  auto solution = MakeSolution();
  int  n        = 13;
  int  k        = 2;
  int  expect   = 10;
  int  actual   = solution->findKthNumber(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(440, KThSmallestInLexicographicalOrder, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  k        = 1;
  int  expect   = 1;
  int  actual   = solution->findKthNumber(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 681692778
// 351251360
// Output: 416126219
//

LEETCODE_SOLUTION_UNITTEST(440, KThSmallestInLexicographicalOrder,
                           extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 681692778;
  int  k        = 351251360;
  int  expect   = 416126219;
  int  actual   = solution->findKthNumber(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
