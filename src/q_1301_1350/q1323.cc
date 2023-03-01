// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum 69 Number
//
// https://leetcode.com/problems/maximum-69-number/
//
// Question ID: 1323
// Difficult  : Easy
// Solve Date : 2022/02/17 22:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1323. Maximum 69 Number|:
//
// You are given a positive integer |num| consisting only of digits |6| and |9|.
// Return the maximum number you can get by changing at most one digit ( |6|
// becomes |9|, and |9| becomes |6|).  
//

LEETCODE_BEGIN_RESOLVING(1323, Maximum69Number, Solution);

class Solution {
public:
  int maximum69Number(int num) {
    int temp = 1;
    while (temp <= num) {
      temp *= 10;
    }
    temp /= 10;
    int  res     = 0;
    bool changed = false;
    while (num != 0) {
      if (changed == false && num / temp == 6) {
        changed = true;
        res += 9 * temp;
      } else {
        res += (num / temp) * temp;
      }
      num -= (num / temp) * temp;
      temp /= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁴|
// * |num| consists of only |6| and |9| digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 9669
// Output: 9969
//
// Changing the first digit results in 6669.
// Changing the second digit results in 9969.
// Changing the third digit results in 9699.
// Changing the fourth digit results in 9666.
// The maximum number is 9969.

LEETCODE_SOLUTION_UNITTEST(1323, Maximum69Number, example_1) {
  auto solution = MakeSolution();
  int  num      = 9669;
  int  expect   = 9969;
  int  actual   = solution->maximum69Number(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 9996
// Output: 9999
//
// Changing the last digit 6 to 9 results in the maximum number.

LEETCODE_SOLUTION_UNITTEST(1323, Maximum69Number, example_2) {
  auto solution = MakeSolution();
  int  num      = 9996;
  int  expect   = 9999;
  int  actual   = solution->maximum69Number(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 9999
// Output: 9999
//
// It is better not to apply any change.

LEETCODE_SOLUTION_UNITTEST(1323, Maximum69Number, example_3) {
  auto solution = MakeSolution();
  int  num      = 9999;
  int  expect   = 9999;
  int  actual   = solution->maximum69Number(num);
  LCD_EXPECT_EQ(expect, actual);
}
