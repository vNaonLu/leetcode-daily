// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Plus One
//
// https://leetcode.com/problems/plus-one/
//
// Question ID: 66
// Difficult  : Easy
// Solve Date : 2021/12/26 14:59

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |66. Plus One|:
//
// You are given a large integer represented as an integer array |digits|, where
// each |digits[i]| is the |iᵗʰ| digit of the integer. The digits are ordered
// from most significant to least significant in left-to-right order. The large
// integer does not contain any leading |0|'s. Increment the large integer by
// one and return the resulting array of digits.  
//

LEETCODE_BEGIN_RESOLVING(66, PlusOne, Solution);

class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    if (digits.empty())
      return vector<int>{};
    vector<int> res  = digits;
    int         plus = 1;
    for (int i = res.size() - 1; i >= 0 && plus != 0; i--) {
      res[i] += plus;
      plus = res[i] / 10;
      res[i] %= 10;
    }
    if (plus > 0)
      res.insert(res.begin(), plus);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= digits.length <= 100|
// * |0 <= digits[i] <= 9|
// * |digits| does not contain any leading |0|'s.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: digits = [1,2,3]
// Output: [1,2,4]
//
// The array represents the integer 123.
// Incrementing by one gives 123 + 1 = 124.
// Thus, the result should be [1,2,4].

LEETCODE_SOLUTION_UNITTEST(66, PlusOne, example_1) {
  auto        solution = MakeSolution();
  vector<int> digits   = {1, 2, 3};
  vector<int> expect   = {1, 2, 4};
  vector<int> actual   = solution->plusOne(digits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: digits = [4,3,2,1]
// Output: [4,3,2,2]
//
// The array represents the integer 4321.
// Incrementing by one gives 4321 + 1 = 4322.
// Thus, the result should be [4,3,2,2].

LEETCODE_SOLUTION_UNITTEST(66, PlusOne, example_2) {
  auto        solution = MakeSolution();
  vector<int> digits   = {4, 3, 2, 1};
  vector<int> expect   = {4, 3, 2, 2};
  vector<int> actual   = solution->plusOne(digits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: digits = [9]
// Output: [1,0]
//
// The array represents the integer 9.
// Incrementing by one gives 9 + 1 = 10.
// Thus, the result should be [1,0].

LEETCODE_SOLUTION_UNITTEST(66, PlusOne, example_3) {
  auto        solution = MakeSolution();
  vector<int> digits   = {9};
  vector<int> expect   = {1, 0};
  vector<int> actual   = solution->plusOne(digits);
  LCD_EXPECT_EQ(expect, actual);
}
