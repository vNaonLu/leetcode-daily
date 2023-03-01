// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subtract the Product and Sum of Digits of an Integer
//
// https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/
//
// Question ID: 1281
// Difficult  : Easy
// Solve Date : 2022/04/15 19:38

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1281. Subtract the Product and Sum of Digits of an Integer|:
//
// Given an integer number |n|, return the difference between the product of its
// digits and the sum of its digits.  
//

LEETCODE_BEGIN_RESOLVING(1281, SubtractTheProductAndSumOfDigitsOfAnInteger,
                         Solution);

class Solution {
public:
  int subtractProductAndSum(int n) {
    long long prod = 1, sum = 0;
    while (n != 0) {
      prod *= n % 10;
      sum += n % 10;

      n /= 10;
    }

    return prod - sum;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10^5|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 234
// Output: 15
// Explanation:
// Product of digits = 2 * 3 * 4 = 24
// Sum of digits = 2 + 3 + 4 = 9
// Result = 24 - 9 = 15
//

LEETCODE_SOLUTION_UNITTEST(1281, SubtractTheProductAndSumOfDigitsOfAnInteger,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 234;
  int  expect   = 15;
  int  actual   = solution->subtractProductAndSum(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4421
// Output: 21
// Explanation:
// Product of digits = 4 * 4 * 2 * 1 = 32
// Sum of digits = 4 + 4 + 2 + 1 = 11
// Result = 32 - 11 = 21
//

LEETCODE_SOLUTION_UNITTEST(1281, SubtractTheProductAndSumOfDigitsOfAnInteger,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 4421;
  int  expect   = 21;
  int  actual   = solution->subtractProductAndSum(n);
  LCD_EXPECT_EQ(expect, actual);
}
