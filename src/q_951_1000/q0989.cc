// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add to Array-Form of Integer
//
// https://leetcode.com/problems/add-to-array-form-of-integer/
//
// Question ID: 989
// Difficult  : Easy
// Solve Date : 2022/04/30 10:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |989. Add to Array-Form of Integer|:
//
// The array-form of an integer |num| is an array representing its digits in
// left to right order.
//
//  • For example, for |num = 1321|, the array form is |[1,3,2,1]|.
// Given |num|, the array-form of an integer, and an integer |k|, return the
// array-form of the integer |num + k|.  
//

LEETCODE_BEGIN_RESOLVING(989, AddToArrayFormOfInteger, Solution);

class Solution {
public:
  vector<int> addToArrayForm(vector<int> &num, int k) {
    vector<int> res;
    int         carry = 0;
    auto        it    = num.rbegin();

    while (k > 0 && it != num.rend()) {
      res.emplace_back(k % 10 + *it + carry);
      carry = res.back() / 10;
      res.back() %= 10;

      k /= 10;
      ++it;
    }

    while (k > 0) {
      res.emplace_back(k % 10 + carry);
      carry = res.back() / 10;
      res.back() %= 10;

      k /= 10;
    }

    while (it != num.rend()) {
      res.emplace_back(*it + carry);
      carry = res.back() / 10;
      res.back() %= 10;

      ++it;
    }

    if (carry > 0) {
      res.emplace_back(carry);
    }

    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 10⁴|
// * |0 <= num[i] <= 9|
// * |num| does not contain any leading zeros except for the zero itself.
// * |1 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
//
// 1200 + 34 = 1234

LEETCODE_SOLUTION_UNITTEST(989, AddToArrayFormOfInteger, example_1) {
  auto        solution = MakeSolution();
  vector<int> num      = {1, 2, 0, 0};
  int         k        = 34;
  vector<int> expect   = {1, 2, 3, 4};
  vector<int> actual   = solution->addToArrayForm(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = [2,7,4], k = 181
// Output: [4,5,5]
//
// 274 + 181 = 455

LEETCODE_SOLUTION_UNITTEST(989, AddToArrayFormOfInteger, example_2) {
  auto        solution = MakeSolution();
  vector<int> num      = {2, 7, 4};
  int         k        = 181;
  vector<int> expect   = {4, 5, 5};
  vector<int> actual   = solution->addToArrayForm(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = [2,1,5], k = 806
// Output: [1,0,2,1]
//
// 215 + 806 = 1021

LEETCODE_SOLUTION_UNITTEST(989, AddToArrayFormOfInteger, example_3) {
  auto        solution = MakeSolution();
  vector<int> num      = {2, 1, 5};
  int         k        = 806;
  vector<int> expect   = {1, 0, 2, 1};
  vector<int> actual   = solution->addToArrayForm(num, k);
  LCD_EXPECT_EQ(expect, actual);
}
