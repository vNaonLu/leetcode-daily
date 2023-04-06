// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Finding 3-Digit Even Numbers
//
// https://leetcode.com/problems/finding-3-digit-even-numbers/
//
// Question ID: 2094
// Difficult  : Easy
// Solve Date : 2023/04/06 15:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2094. Finding 3-Digit Even Numbers|:
//
// You are given an integer array |digits|, where each element is a digit. The
// array may contain duplicates. You need to find all the unique integers that
// follow the given requirements:
//
//  • The integer consists of the concatenation of three elements from |digits|
//  in any arbitrary order.
//
//  • The integer does not have leading zeros.
//
//  • The integer is even.
// For example, if the given |digits| were |[1, 2, 3]|, integers |132| and |312|
// follow the requirements. Return a sorted array of the unique integers.
//
//

LEETCODE_BEGIN_RESOLVING(2094, Finding3DigitEvenNumbers, Solution);

class Solution {
public:
  vector<int> findEvenNumbers(vector<int> &digits) {
    vector<int> res;
    vector<int> cnt(10, 0);
    for (auto x : digits) {
      ++cnt[x];
    }
    for (int i = 100; i < 1000; i += 2) {
      int d1 = i / 100;
      int d2 = (i / 10) % 10;
      int d3 = i % 10;
      --cnt[d1];
      --cnt[d2];
      --cnt[d3];
      if (cnt[d1] >= 0 && cnt[d2] >= 0 && cnt[d3] >= 0) {
        res.emplace_back(i);
      }
      ++cnt[d1];
      ++cnt[d2];
      ++cnt[d3];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= digits.length <= 100|
// * |0 <= digits[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
//
// All the possible integers that follow the requirements are in the output
// array. Notice that there are no odd integers or integers with leading zeros.

LEETCODE_SOLUTION_UNITTEST(2094, Finding3DigitEvenNumbers, example_1) {
  auto        solution = MakeSolution();
  vector<int> digits   = {2, 1, 3, 0};
  vector<int> expect   = {102, 120, 130, 132, 210, 230, 302, 310, 312, 320};
  vector<int> actual   = solution->findEvenNumbers(digits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: digits = [2,2,8,8,2]
// Output: [222,228,282,288,822,828,882]
//
// The same digit can be used as many times as it appears in digits.
// In this example, the digit 8 is used twice each time in 288, 828, and 882.

LEETCODE_SOLUTION_UNITTEST(2094, Finding3DigitEvenNumbers, example_2) {
  auto        solution = MakeSolution();
  vector<int> digits   = {2, 2, 8, 8, 2};
  vector<int> expect   = {222, 228, 282, 288, 822, 828, 882};
  vector<int> actual   = solution->findEvenNumbers(digits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: digits = [3,7,5]
// Output: []
//
// No even integers can be formed using the given digits.

LEETCODE_SOLUTION_UNITTEST(2094, Finding3DigitEvenNumbers, example_3) {
  auto        solution = MakeSolution();
  vector<int> digits   = {3, 7, 5};
  vector<int> expect   = {};
  vector<int> actual   = solution->findEvenNumbers(digits);
  LCD_EXPECT_EQ(expect, actual);
}
