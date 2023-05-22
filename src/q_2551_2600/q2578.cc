// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Split With Minimum Sum
//
// https://leetcode.com/problems/split-with-minimum-sum/
//
// Question ID: 2578
// Difficult  : Easy
// Solve Date : 2023/05/22 17:39

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2578. Split With Minimum Sum|:
//
// Given a positive integer |num|, split it into two non-negative integers
// |num1| and |num2| such that:
//
//  • The concatenation of |num1| and |num2| is a permutation of |num|.
//
//
//    • In other words, the sum of the number of occurrences of each digit in
//    |num1| and |num2| is equal to the number of occurrences of that digit in
//    |num|.
//
//
//
//  • |num1| and |num2| can contain leading zeros.
// Return the minimum possible sum of |num1| and |num2|.
// Notes:
//
//  • It is guaranteed that |num| does not contain any leading zeros.
//
//  • The order of occurrence of the digits in |num1| and |num2| may differ from
//  the order of occurrence of |num|.
//
//

LEETCODE_BEGIN_RESOLVING(2578, SplitWithMinimumSum, Solution);

class Solution {
public:
  int splitNum(int num) {
    int         n1 = 0;
    int         n2 = 0;
    int         x  = 1;
    vector<int> v;
    while (num) {
      v.emplace_back(num % 10);
      num /= 10;
    }
    sort(v.begin(), v.end());
    for (auto i : v) {
      num = 10 * num + i;
    }
    while (num) {
      n1 += x * (num % 10);
      num /= 10;
      n2 += x * (num % 10);
      num /= 10;
      x *= 10;
    }
    return n1 + n2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |10 <= num <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 4325
// Output: 59
//
// We can split 4325 so that |num1 |is 24 and num2 | is |35, giving a sum of 59.
// We can prove that 59 is indeed the minimal possible sum.

LEETCODE_SOLUTION_UNITTEST(2578, SplitWithMinimumSum, example_1) {
  auto solution = MakeSolution();
  int  num      = 4325;
  int  expect   = 59;
  int  actual   = solution->splitNum(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 687
// Output: 75
//
// We can split 687 so that |num1| is 68 and |num2 |is 7, which would give an
// optimal sum of 75.

LEETCODE_SOLUTION_UNITTEST(2578, SplitWithMinimumSum, example_2) {
  auto solution = MakeSolution();
  int  num      = 687;
  int  expect   = 75;
  int  actual   = solution->splitNum(num);
  LCD_EXPECT_EQ(expect, actual);
}
