// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Three Divisors
//
// https://leetcode.com/problems/three-divisors/
//
// Question ID: 1952
// Difficult  : Easy
// Solve Date : 2022/12/24 14:41

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1952. Three Divisors|:
//
// Given an integer |n|, return |true| if |n| has exactly three positive
// divisors. Otherwise, return |false|. An integer |m| is a divisor of |n| if
// there exists an integer |k| such that |n = k * m|.
//

LEETCODE_BEGIN_RESOLVING(1952, ThreeDivisors, Solution);

class Solution {
public:
  bool isThree(int n) {
    auto res = (int)2;
    for (int i = 2; i <= sqrt(n); ++i) {
      if (n % i == 0) {
        ++res;
        if (i != n / i) {
          ++res;
        }
      }
      if (res > 3) {
        break;
      }
    }
    return res == 3;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: false
// Explantion: 2 has only two divisors: 1 and 2.
//

LEETCODE_SOLUTION_UNITTEST(1952, ThreeDivisors, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  bool expect   = false;
  bool actual   = solution->isThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4
// Output: true
// Explantion: 4 has three divisors: 1, 2, and 4.
//

LEETCODE_SOLUTION_UNITTEST(1952, ThreeDivisors, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  bool expect   = true;
  bool actual   = solution->isThree(n);
  LCD_EXPECT_EQ(expect, actual);
}
