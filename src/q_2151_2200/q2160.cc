// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Sum of Four Digit Number After Splitting Digits
//
// https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/
//
// Question ID: 2160
// Difficult  : Easy
// Solve Date : 2023/04/26 18:49

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2160. Minimum Sum of Four Digit Number After Splitting
// Digits|:
//
// You are given a positive integer |num| consisting of exactly four digits.
// Split |num| into two new integers |new1| and |new2| by using the digits found
// in |num|. Leading zeros are allowed in |new1| and |new2|, and all the digits
// found in |num| must be used.
//
//  • For example, given |num = 2932|, you have the following digits: two |2|'s,
//  one |9| and one |3|. Some of the possible pairs |[new1, new2]| are |[22,
//  93]|, |[23, 92]|, |[223, 9]| and |[2, 329]|.
// Return the minimum possible sum of |new1| and |new2|.
//
//

LEETCODE_BEGIN_RESOLVING(2160, MinimumSumOfFourDigitNumberAfterSplittingDigits,
                         Solution);

class Solution {
public:
  int minimumSum(int num) {
    vector<int> x;
    while (num != 0) {
      x.emplace_back(num % 10);
      num /= 10;
    }

    sort(x.begin(), x.end());
    return max(x[0] * 10 + x[2] + x[1] * 10 + x[3],
               x[0] * 10 + x[3] + x[1] * 10 + x[2]);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1000 <= num <= 9999|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 2932
// Output: 52
//
// Some possible pairs [new1, new2] are [29, 23], [223, 9], etc.
// The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.

LEETCODE_SOLUTION_UNITTEST(2160,
                           MinimumSumOfFourDigitNumberAfterSplittingDigits,
                           example_1) {
  auto solution = MakeSolution();
  int  num      = 2932;
  int  expect   = 52;
  int  actual   = solution->minimumSum(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 4009
// Output: 13
//
// Some possible pairs [new1, new2] are [0, 49], [490, 0], etc.
// The minimum sum can be obtained by the pair [4, 9]: 4 + 9 = 13.

LEETCODE_SOLUTION_UNITTEST(2160,
                           MinimumSumOfFourDigitNumberAfterSplittingDigits,
                           example_2) {
  auto solution = MakeSolution();
  int  num      = 4009;
  int  expect   = 13;
  int  actual   = solution->minimumSum(num);
  LCD_EXPECT_EQ(expect, actual);
}
