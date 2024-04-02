// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Harshad Number
//
// https://leetcode.com/problems/harshad-number/
//
// Question ID: 3099
// Difficult  : Easy
// Solve Date : 2024/03/31 15:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3099. Harshad Number|:
//
// An integer divisible by the sum of its digits is said to be a Harshad number.
// You are given an integer |x|. Return the sum of the digits of |x| if |x| is a
// Harshad number, otherwise, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(3099, HarshadNumber, Solution);

class Solution {
public:
  int sumOfTheDigitsOfHarshadNumber(int x) {
    int sum = getSum(x);
    return (x % sum) == 0 ? sum : -1;
  }

private:
  int getSum(int x) {
    int res = 0;
    while (x) {
      res += x % 10;
      x /= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= x <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 18
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3099, HarshadNumber, example_1) {
  auto solution = MakeSolution();
  int  x        = 18;
  int  expect   = 9;
  int  actual   = solution->sumOfTheDigitsOfHarshadNumber(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 23
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3099, HarshadNumber, example_2) {
  auto solution = MakeSolution();
  int  x        = 23;
  int  expect   = -1;
  int  actual   = solution->sumOfTheDigitsOfHarshadNumber(x);
  LCD_EXPECT_EQ(expect, actual);
}
