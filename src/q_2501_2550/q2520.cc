// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count the Digits That Divide a Number
//
// https://leetcode.com/problems/count-the-digits-that-divide-a-number/
//
// Question ID: 2520
// Difficult  : Easy
// Solve Date : 2023/03/12 17:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2520. Count the Digits That Divide a Number|:
//
// Given an integer |num|, return the number of digits in |num| that divide
// |num|. An integer |val| divides |nums| if |nums % val == 0|.
//

LEETCODE_BEGIN_RESOLVING(2520, CountTheDigitsThatDivideANumber, Solution);

class Solution {
public:
  int countDigits(int num) {
    int res    = 0;
    int target = num;
    while (num > 0) {
      int curr = num % 10;
      if (curr != 0 && target % curr == 0) {
        ++res;
      }
      num /= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁹|
// * |num| does not contain |0| as one of its digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 7
// Output: 1
//
// 7 divides itself, hence the answer is 1.

LEETCODE_SOLUTION_UNITTEST(2520, CountTheDigitsThatDivideANumber, example_1) {
  auto solution = MakeSolution();
  int  num      = 7;
  int  expect   = 1;
  int  actual   = solution->countDigits(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 121
// Output: 2
//
// 121 is divisible by 1, but not 2. Since 1 occurs twice as a digit, we
// return 2.

LEETCODE_SOLUTION_UNITTEST(2520, CountTheDigitsThatDivideANumber, example_2) {
  auto solution = MakeSolution();
  int  num      = 121;
  int  expect   = 2;
  int  actual   = solution->countDigits(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 1248
// Output: 4
//
// 1248 is divisible by all of its digits, hence the answer is 4.

LEETCODE_SOLUTION_UNITTEST(2520, CountTheDigitsThatDivideANumber, example_3) {
  auto solution = MakeSolution();
  int  num      = 1248;
  int  expect   = 4;
  int  actual   = solution->countDigits(num);
  LCD_EXPECT_EQ(expect, actual);
}
