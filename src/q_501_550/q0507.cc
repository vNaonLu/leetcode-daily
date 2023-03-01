// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Perfect Number
//
// https://leetcode.com/problems/perfect-number/
//
// Question ID: 507
// Difficult  : Easy
// Solve Date : 2021/12/22 21:58

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |507. Perfect Number|:
//
// A perfect number is a positive integer that is equal to the sum of its
// positive divisors, excluding the number itself. A divisor of an integer |x|
// is an integer that can divide |x| evenly. Given an integer |n|, return |true|
// if |n| is a perfect number, otherwise return |false|.  
//

LEETCODE_BEGIN_RESOLVING(507, PerfectNumber, Solution);

class Solution {
public:
  bool checkPerfectNumber(int num) {
    if (num == 1)
      return false;
    int sum = 1;
    for (int i = 2; i * i <= num; i++)
      if (num % i == 0)
        sum += i + num / i;
    return sum == num;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 28
// Output: true
//
// 28 = 1 + 2 + 4 + 7 + 14
// 1, 2, 4, 7, and 14 are all divisors of 28.

LEETCODE_SOLUTION_UNITTEST(507, PerfectNumber, example_1) {
  auto solution = MakeSolution();
  int  num      = 28;
  bool expect   = true;
  bool actual   = solution->checkPerfectNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 7
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(507, PerfectNumber, example_2) {
  auto solution = MakeSolution();
  int  num      = 7;
  bool expect   = false;
  bool actual   = solution->checkPerfectNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}
