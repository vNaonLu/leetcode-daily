// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the K-Beauty of a Number
//
// https://leetcode.com/problems/find-the-k-beauty-of-a-number/
//
// Question ID: 2269
// Difficult  : Easy
// Solve Date : 2023/03/12 14:57

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2269. Find the K-Beauty of a Number|:
//
// The k-beauty of an integer |num| is defined as the number of substrings of
// |num| when it is read as a string that meet the following conditions:
//
//  • It has a length of |k|.
//
//  • It is a divisor of |num|.
// Given integers |num| and |k|, return the k-beauty of |num|.
// Note:
//
//  • Leading zeros are allowed.
//
//  • |0| is not a divisor of any value.
// A substring is a contiguous sequence of characters in a string.
//

LEETCODE_BEGIN_RESOLVING(2269, FindTheKBeautyOfANumber, Solution);

class Solution {
public:
  int divisorSubstrings(int num, int k) {
    int64_t target = num;
    int64_t scale  = pow(10, k);
    int     res    = 0;
    while (num >= scale / 10) {
      int64_t cur = num % scale;
      if (cur != 0 && target % cur == 0) {
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
// * |1 <= k <= num.length| (taking |num| as a string)
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 240, k = 2
// Output: 2
//
// The following are the substrings of num of length k:
// - "24" from "240": 24 is a divisor of 240.
// - "40" from "240": 40 is a divisor of 240.
// Therefore, the k-beauty is 2.

LEETCODE_SOLUTION_UNITTEST(2269, FindTheKBeautyOfANumber, example_1) {
  auto solution = MakeSolution();
  int  num      = 240;
  int  k        = 2;
  int  expect   = 2;
  int  actual   = solution->divisorSubstrings(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 430043, k = 2
// Output: 2
//
// The following are the substrings of num of length k:
// - "43" from "430043": 43 is a divisor of 430043.
// - "30" from "430043": 30 is not a divisor of 430043.
// - "00" from "430043": 0 is not a divisor of 430043.
// - "04" from "430043": 4 is not a divisor of 430043.
// - "43" from "430043": 43 is a divisor of 430043.
// Therefore, the k-beauty is 2.

LEETCODE_SOLUTION_UNITTEST(2269, FindTheKBeautyOfANumber, example_2) {
  auto solution = MakeSolution();
  int  num      = 430043;
  int  k        = 2;
  int  expect   = 2;
  int  actual   = solution->divisorSubstrings(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 680
// 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2269, FindTheKBeautyOfANumber, extra_testcase_1) {
  auto solution = MakeSolution();
  int  num      = 680;
  int  k        = 2;
  int  expect   = 1;
  int  actual   = solution->divisorSubstrings(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: 1000000000
// 10
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2269, FindTheKBeautyOfANumber, extra_testcase_2) {
  auto solution = MakeSolution();
  int  num      = 1000000000;
  int  k        = 10;
  int  expect   = 1;
  int  actual   = solution->divisorSubstrings(num, k);
  LCD_EXPECT_EQ(expect, actual);
}
